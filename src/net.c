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

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "types.h"
#include "net.h"

/**
 * Initialize the wb net system.
 */
void net_init() {
	curl_global_init(CURL_GLOBAL_ALL);
}

/**
 * Cleanup the wb net system.
 */
void net_cleanup() {
	curl_global_cleanup();
}

/**
 * Writes CURL response to a curl_response structure.
 *
 * @param ptr - CURL response data pointer.
 * @param size - size of the data to write in units of nmemb.
 * @param nmemb - multiplier of size.
 * @param data - the structure to write data to.
 * @return the size of data written in bytes.
 */
size_t
write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data) {
	size_t index = data->size;
	size_t n = (size * nmemb);
	char* tmp;

	data->size += (size * nmemb);

	tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

	if(tmp) {
		data->data = tmp;
	} else {
		if(data->data) {
			free(data->data);
		}
		fprintf(stderr, "Failed to allocate memory.\n");
		return 0;
	}

	memcpy((data->data + index), ptr, n);
	data->data[data->size] = '\0';

	return size * nmemb;
}

/**
 * Gets cookies as a wb_str_list from a CURL struct.
 *
 * @param curl - the CURL struct
 * @return a wb_str_list containing cookies on success, NULL
 *   otherwise. IMPORTANT: this list must be freed with
 *   wb_list_free().
 */
struct wb_str_list *
curl_get_cookies(CURL *curl) {
	CURLcode res;
	struct wb_str_list *cookies;

	res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
	if (res != CURLE_OK) {
		if (cookies != NULL) {
			wb_list_free(cookies);
		}

		return NULL;
	}

	return cookies;
}

/**
 * Adds all cookies from a wb_str_list to a CURL structure.
 *
 * @param curl - the CURL structure to add cookies to.
 * @param cookies - a wb_str_list containing the cookies to
 *   be added.
 */
void
curl_add_cookies(CURL *curl, struct wb_str_list *cookies) {
	struct wb_str_list *cookie = cookies;
	while (cookie != NULL) {
		curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie->str);
		cookie = cookie->next;
	}
}

/**
 * Connects to URL with a GET or POST request and returns
 * the response.
 *
 * @param url - the URL to connect to.
 * @param post_data (optional) - the post data as a string.
 *   If specified, a POST request is made. If post is not
 *   needed, pass NULL here and a GET request will be made.
 * @param cookies (optional) - the cookies to use for this
 *   request.
 * @param update_cookies - 1 if you need the cookies to be
 *   updated, 0 to leave the cookies as they were.
 * @return the response as a string on success, NULL otherwise.
 *   IMPORTANT: the returned string should be freed with free().
 */
char *
net_get_response(const char *url, const char *post_data,
	struct wb_str_list **cookies, int update_cookies) {

	CURL *curl;
	CURLcode res;

	/* Set up struct for CURL response */
	struct curl_response response;
	response.size = 0;
	response.data = malloc(4096);
	if (response.data == NULL) {
		return NULL;
	}
	response.data[0] = '\0';

	/* Set up CURL */
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	if (update_cookies) {
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	}

	if (post_data != NULL) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
	}

	if (cookies != NULL) {
		curl_add_cookies(curl, *cookies);
	}

	/* Perform CURL transaction */
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		curl_easy_cleanup(curl);
		return NULL;
	}

	/* Update cookies if needed */
	if (update_cookies) {
		if (cookies != NULL) {
			wb_list_free(*cookies);
		}

		*cookies = curl_get_cookies(curl);
		if (*cookies == NULL) {
			curl_easy_cleanup(curl);
			return NULL;
		}
	}

	/* Cleanup */
	curl_easy_cleanup(curl);
	return response.data;
}

/**
 * A wrapper for net_get_response(). Should be used when the
 * response is not needed.
 *
 * @return 0 on success, -1 otherwise.
 *
 * @see net_get_response()
 */
int
net_connect(const char *url, const char *post_data,
	struct wb_str_list **cookies, int update_cookies) {

	char *response;

	response = net_get_response(url, post_data, cookies, update_cookies);
	if (response == NULL) {
		return -1;
	}

	free(response);
	return 0;
}
