/*
 * wb - A wallbase.cc image downloader
 *
 * Copyright (C) 2013 Mantas Norvaiša
 *
 * This file is part of wb.
 * 
 * wb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wb.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "wb.h"
#include "types.h"
#include "args.h"
#include "base64.h"
#include "net.h"
#include "url_enc.h"
#include "xml.h"
#include "xpath.h"

/**************************************************
 * General global constants
 **************************************************/

static const char *URL_LOGIN_PAGE = "http://wallbase.cc/user/login";
static const char *URL_LOGIN_POST = "http://wallbase.cc/user/do_login";
static const char *URL_TOPLIST = "http://wallbase.cc/toplist";

static const char *FORMAT_LOGIN = "csrf=%s&ref=aHR0cDovL3dhbGxiYXNlLmNjLw%%3D%%3D&password=%s&username=%s";

static const char *XPATH_CSRF_TOKEN = "//input[@name='csrf']/@value";
static const char *XPATH_IMAGE_PAGE_URL = "//div[contains(@class,'thumb')]/div[@class='wrapper']/a[@target='_blank']/@href";
static const char *XPATH_IMAGE_URL = "//img[contains(@class,'wall')]/@src";

/**************************************************
 * Main
 **************************************************/

int
main(int argc, char* argv[]) {
	/* Variables */
	struct wb_str_list *cookies = NULL;
	struct wb_str_list *image_urls = NULL;
	struct wb_str_list *img_url;
	struct options options;

	/* Set default options */
	options.username = "";
	options.password = "";
	options.dir = ".";
	options.images = 20;
	options.images_per_page = 20;

	options.query = NULL;
	options.color = -1;
	options.toplist = WB_TOPLIST_NONE;

	options.res_x = 0;
	options.res_y = 0;
	options.res_opt = WB_RES_AT_LEAST;
	options.aspect_ratio = 0;

	options.flags = 0;
	options.purity = 0;
	options.boards = 0;

	options.sort_by = WB_SORT_RELEVANCE;
	options.sort_order = WB_SORT_DESCENDING;

	/* Parse arguments */
	wb_parse_args(argc, argv, &options);

	/* Init */
	net_init();
	xpath_init();

	/* Main operation */
	cookies = wb_login(options.username, options.password);
	if (cookies == NULL) {
		net_cleanup();
		xpath_cleanup();
		return 1;
	}

	image_urls = wb_get_image_urls(URL_TOPLIST, NULL, cookies);
	if (image_urls == NULL) {
		wb_list_free(cookies);
		net_cleanup();
		xpath_cleanup();
		return 1;
	}

	img_url = image_urls;
	while (img_url != NULL) {
		printf("%s\n", img_url->str);
		img_url = img_url->next;
	}

	/* Cleanup nd return */
	wb_list_free(cookies);
	wb_list_free(image_urls);
	net_cleanup();
	xpath_cleanup();
	return 0;
}

/**************************************************
 * Function implementations
 **************************************************/

/**
 * wb_login:
 * @username - wallbase.cc username
 * @password - wallbase.cc password
 *
 * Login to wallbase.cc, by setting your specified cookies.
 * IMPORTANT: The resulting list of cookies must be freed with
 * wb_list_free().
 *
 * Returns a wb_str_list of cookies with the login session info.
 */
struct wb_str_list *
wb_login(const char *username, const char *password) {
	char *enc_username;
	char *enc_password;
	char post_data[256];
	char *login_response;
	char *csrf_token;

	struct wb_str_list *cookies = NULL;

	/* Get a new CSRF token */
	csrf_token = wb_get_login_csrf_token(&cookies);

	/* URL-encode username and password and insert into POST data */
	enc_username = url_encode(username);
	enc_password = url_encode(password);
	sprintf(post_data, FORMAT_LOGIN, csrf_token, enc_password, enc_username);
	free(enc_username);
	free(enc_password);
	free(csrf_token);

	/* Login */
	login_response = net_get_response(URL_LOGIN_POST, post_data, &cookies, 1);
	if (login_response == NULL) {
		fprintf(stderr, "Error: net_get_response() failed\n");
		return NULL;
	}

	if (strlen(login_response) > 0) {
		fprintf(stderr, "Error: unable to login to wallbase.cc\n");
		free(login_response);
		wb_list_free(cookies);
		return NULL;
	}

	free(login_response);

	return cookies;
}

/**
 * Connects to the wallbase.cc login page and fetches a CSRF
 * token.
 *
 * @return a CSRF token for the login form on success, NULL
 *   otherwise. IMPORTANT: the returned string must be freed
 *   using free().
 */
char *
wb_get_login_csrf_token(struct wb_str_list **cookies) {
	char *login_page_xml_data;
	char *csrf_token;

	struct wb_str_list *xpath_results;

	/* Get the login page as XML */
	login_page_xml_data = net_get_response_as_xml(URL_LOGIN_PAGE, NULL, cookies, 1);
	if (login_page_xml_data == NULL) {
		return NULL;
	}

	/* Get the CSRF token from XML */
	xpath_results = xpath_eval_expr(login_page_xml_data, XPATH_CSRF_TOKEN, NULL);
	free(login_page_xml_data);

	if (xpath_results == NULL) {
		return NULL;
	} else if (xpath_results->next != NULL) {
		wb_list_free(xpath_results);
		return NULL;
	}

	csrf_token = strdup(xpath_results->str);
	wb_list_free(xpath_results);

	return csrf_token;
}

/**
 * Connects to wallbase.cc with the specified post data and
 * cookies and retrieves image page urls.
 *
 * @param url - wallbase.cc url to get images from.
 * @param post_data - post data required for search parameters.
 * @param cookies - cookies with login session information.
 * @return a wb_str_list of image page urls on success, NULL
 *   otherwise. IMPORTANT: the returned list must be freed with
 *   wb_list_free().
 */
struct wb_str_list *
wb_get_image_page_urls(const char *url, const char *post_data,
	struct wb_str_list *cookies) {

	struct wb_str_list *urls = NULL;
	char *xml_data;

	/* Get response as XML */
	xml_data = net_get_response_as_xml(url, post_data, &cookies, 0);
	if (xml_data == NULL) {
		return NULL;
	}

	/* Get urls from the XML */
	urls = xpath_eval_expr(xml_data, XPATH_IMAGE_PAGE_URL, NULL);
	free(xml_data);

	return urls;
}

/**
 * Connects to wallbase.cc with the specified post data and
 * cookies and retrieves image urls.
 *
 * @param url - wallbase.cc url to get images from.
 * @param post_data - post data required for search parameters.
 * @param cookies - cookies with login session information.
 * @return a wb_str_list of image urls on success, NULL
 *   otherwise. IMPORTANT: the returned list must be freed with
 *   wb_list_free().
 */
struct wb_str_list *
wb_get_image_urls(const char *url, const char *post_data,
	struct wb_str_list *cookies) {

	struct wb_str_list *img_urls = NULL;
	struct wb_str_list *img_page_urls;
	struct wb_str_list *img_page_url;
	char *img_url;

	/* Get image page URLs */
	img_page_urls = wb_get_image_page_urls(url, post_data, cookies);

	/* Get an image URL from every image page URL */
	img_page_url = img_page_urls;
	while (img_page_url != NULL) {
		img_url = wb_get_image_url(img_page_url->str, cookies);
		if (img_url != NULL) {
			img_urls = wb_list_append(img_urls, img_url);
			free(img_url);
		}

		img_page_url = img_page_url->next;
	}

	/* Cleanup */
	wb_list_free(img_page_urls);

	return img_urls;
}

/**
 * Get the full image url from a wallbase.cc image page url.
 *
 * @param url - wallbase.cc image page url.
 * @param cookies - cookie list needed for NSFW images.
 * @return the URL of the image on success, NULL otherwise.
 *   IMPORTANT: the resulting string must be freed eith free().
 */
char *
wb_get_image_url(const char *url, struct wb_str_list *cookies) {
	char *img_url = NULL;
	char *xml_data;
	struct wb_str_list *xpath_results;

	/* Get response as XML */
	xml_data = net_get_response_as_xml(url, NULL, &cookies, 0);
	if (xml_data == NULL) {
		return NULL;
	}

	/* Get the script node (that contains the encoded url) data */
	xpath_results = xpath_eval_expr(xml_data, XPATH_IMAGE_URL, NULL);
	free(xml_data);

	if (xpath_results == NULL) {
		return NULL;
	} else if (xpath_results->next != NULL) {
		wb_list_free(xpath_results);
		return NULL;
	}

	img_url = strdup(xpath_results->str);
	wb_list_free(xpath_results);

	return img_url;
}
