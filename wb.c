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

static const char *URL_LOGIN = "http://wallbase.cc/user/login";
static const char *URL_TOPLIST = "http://wallbase.cc/toplist";

static const char *FORMAT_LOGIN = "usrname=%s&pass=%s&nopass_email=Type+in+your+e-mail+and+press+enter&nopass=0&1=1";

static const char *XHTML_PREFIX = "xhtml";
static const char *XHTML_HREF = "http://www.w3.org/1999/xhtml";
static const char *XPATH_IMAGE_PAGE_URL = "//xhtml:div[contains(@class,'thumb')]/xhtml:a[@class='thdraggable thlink']/@href";
static const char *XPATH_IMAGE_URL = "//xhtml:div[@id='bigwall']/xhtml:script";

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
	options.flags = 0;
	options.purity = WB_PURITY_ALL;
	options.boards = WB_BOARD_ALL;
	options.res_x = 0;
	options.res_y = 0;
	options.res_opt = WB_RES_AT_LEAST;
	options.aspect_ratio = 0;
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
	char *response;

	struct wb_str_list *cookies = NULL;

	/* URL-encode username and password and insert into POST data */
	enc_username = url_encode(username);
	enc_password = url_encode(password);
	sprintf(post_data, FORMAT_LOGIN, enc_username, enc_password);
	free(enc_username);
	free(enc_password);

	/* Login */
	response = net_get_response(URL_LOGIN, post_data, &cookies, 1);
	if (response == NULL) {
		fprintf(stderr, "Error: net_get_response() failed\n");
		return NULL;
	}

	if (strlen(response) > 0) {
		fprintf(stderr, "Error: unable to login to wallbase.cc\n");
		free(response);
		wb_list_free(cookies);
		return NULL;
	}

	free(response);

	return cookies;
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
	struct wb_str_list *namespaces = NULL;
	char *xml_data;

	/* Add namespaces required for XPath */
	namespaces = wb_list_append(namespaces, XHTML_PREFIX);
	namespaces = wb_list_append(namespaces, XHTML_HREF);

	/* Get response as XML */
	xml_data = net_get_response_as_xml(url, post_data, &cookies, 0);
	if (xml_data == NULL) {
		return NULL;
	}

	/* Get urls from the XML */
	urls = xpath_eval_expr(xml_data, XPATH_IMAGE_PAGE_URL, namespaces);
	free(xml_data);
	wb_list_free(namespaces);

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
	char *img_url = NULL, *encoded_url = NULL, *result_str;
	char *xml_data;
	struct wb_str_list *xpath_results;
	struct wb_str_list *namespaces = NULL;

	int encoded_length = 0;
	char *encoded_start, *encoded_end;

	/* Add namespaces required for XPath */
	namespaces = wb_list_append(namespaces, XHTML_PREFIX);
	namespaces = wb_list_append(namespaces, XHTML_HREF);

	/* Get response as XML */
	xml_data = net_get_response_as_xml(url, NULL, &cookies, 0);
	if (xml_data == NULL) {
		return NULL;
	}

	/* Get the script node (that contains the encoded url) data */
	xpath_results = xpath_eval_expr(xml_data, XPATH_IMAGE_URL, namespaces);
	free(xml_data);
	wb_list_free(namespaces);

	if (xpath_results == NULL) {
		return NULL;
	} else if (xpath_results->next != NULL) {
		return NULL;
	}

	result_str = strdup(xpath_results->str);
	wb_list_free(xpath_results);
	
	/* Extract encoded URL from the result node */
	encoded_url = (char *)malloc(256);
	encoded_start = strstr(result_str, "B('") + 3;
	encoded_end = strstr(result_str, "')");
	encoded_length = encoded_end - encoded_start;
	strncpy(encoded_url, encoded_start, encoded_length);
	encoded_url[encoded_length] = '\0';
	free(result_str);

	/* Decode URL*/
	img_url = b64_decode(encoded_url);
	free(encoded_url);

	return img_url;
}
