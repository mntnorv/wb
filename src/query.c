/*
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
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "query.h"

static const char *URL_BASE = "http://wallbase.cc";
static const char *URL_ENDPOINT_SUFFIX = "/index/%d?section=wallpapers";

static const char *URL_ENDPOINT_SEARCH      = "/search";
static const char *URL_ENDPOINT_TOPLIST     = "/toplist";
static const char *URL_ENDPOINT_RANDOM      = "/random";
/*static const char *URL_ENDPOINT_COLLECTIONS = "/collection";*/

/**
 * Try to detect the query type from options.
 *
 * @param options - the option struct
 * @return an integer specifying the detected query type.
 *   Possible query types are defined in types.h as "WB_TYPE_*".
 */
int
get_query_type(struct options *options) {
	int query_type = WB_TYPE_SEARCH;

	/* Detect toplist search */
	if (options->toplist != WB_TOPLIST_NONE) {
		query_type = WB_TYPE_TOPLIST;
	}

	/* Detect random search */
	if ((options->flags & WB_FLAG_RANDOM) > 0) {
		query_type = WB_TYPE_RANDOM;
	}

	return query_type;
}

/**
 * Get the resolution option string wallbase.cc accepts from
 * an option structure.
 *
 * @param options - the option structure
 * @return the resolution option.
 */
char *
get_res_opt_string(struct options *options) {
	char *str;

	switch(options->res_opt) {
		case WB_RES_EXACTLY:
			str = "eqeq";
			break;
		case WB_RES_AT_LEAST:
			str = "gteq";
			break;
	}

	return str;
}

/**
 * Get the sort by string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the sort by string.
 */
char *
get_sort_by_string(struct options *options) {
	char *str;

	switch(options->sort_by) {
		case WB_SORT_RELEVANCE:
			str = "relevance";
			break;
		case WB_SORT_VIEWS:
			str = "views";
			break;
		case WB_SORT_DATE:
			str = "date";
			break;
		case WB_SORT_FAVORITES:
			str = "favs";
			break;
	}

	return str;
}

/**
 * Get the sort order string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the sort order string.
 */
char *
get_sort_order_string(struct options *options) {
	char *str;

	switch(options->sort_order) {
		case WB_SORT_ASCENDING:
			str = "asc";
			break;
		case WB_SORT_DESCENDING:
			str = "desc";
			break;
	}

	return str;
}

/**
 * Get the toplist interval by string wallbase.cc accepts from
 * an option structure.
 *
 * @param options - the option structure
 * @return the toplist interval string.
 */
char *
get_toplist_interval_string(struct options *options) {
	char *str;

	switch(options->toplist) {
		case WB_TOPLIST_1D:
			str = "1d";
			break;
		case WB_TOPLIST_3D:
			str = "3d";
			break;
		case WB_TOPLIST_1W:
			str = "1w";
			break;
		case WB_TOPLIST_2W:
			str = "2w";
			break;
		case WB_TOPLIST_1M:
			str = "1m";
			break;
		case WB_TOPLIST_2M:
			str = "2m";
			break;
		case WB_TOPLIST_3M:
			str = "3m";
			break;
		case WB_TOPLIST_ALL_TIME:
			str = "1";
			break;
	}

	return str;
}

/**
 * Get the resolution string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the resolution string. IMPORTANT: the returned string
 *   must be freed using free().
 */
char *
get_resolution_string(struct options *options) {
	char *str;

	str = (char *) malloc(16);
	snprintf(str, 16, "%dx%d", options->res_x, options->res_y);

	return str;
}

/**
 * Get the aspect ratio string wallbase.cc accepts from an
 * option structure.
 *
 * @param options - the option structure
 * @return the aspect ratio string. IMPORTANT: the returned
 *   string must be freed using free().
 */
char *
get_aspect_ratio_string(struct options *options) {
	char *str;

	str = (char *) malloc(5);
	snprintf(str, 5, "%.2f", options->aspect_ratio);

	return str;
}

/**
 * Get the color string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the color string. IMPORTANT: the returned string
 *   must be freed using free().
 */
char *
get_color_string(struct options *options) {
	char *str;

	str = (char *) malloc(7);
	snprintf(str, 7, "%x", options->color);

	return str;
}

/**
 * Get the thumbs per page string wallbase.cc accepts from an
 * option structure.
 *
 * @param options - the option structure
 * @return the resolution string. IMPORTANT: the returned string
 *   must be freed using free().
 */
char *
get_thpp_string(struct options *options) {
	char *str;

	str = (char *) malloc(8);
	snprintf(str, 8, "%d", options->images_per_page);

	return str;
}

/**
 * Get the purity string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the purity string. IMPORTANT: the returned string
 *   must be freed using free().
 */
char *
get_purity_string(struct options *options) {
	char *str;
	int pos;

	str = (char *) malloc(4);
	str[3] = '\0';

	pos = 0;
	if ((options->purity & WB_PURITY_SFW) > 0) {
		str[pos] = '1';
	} else {
		str[pos] = '0';
	}

	pos++;
	if ((options->purity & WB_PURITY_SKETCHY) > 0) {
		str[pos] = '1';
	} else {
		str[pos] = '0';
	}

	pos++;
	if ((options->purity & WB_PURITY_NSFW) > 0) {
		str[pos] = '1';
	} else {
		str[pos] = '0';
	}

	return str;
}

/**
 * Get the boards string wallbase.cc accepts from an option
 * structure.
 *
 * @param options - the option structure
 * @return the boards string. IMPORTANT: the returned string
 *   must be freed using free().
 */
char *
get_boards_string(struct options *options) {
	char *str;
	int pos;

	str = (char *) malloc(4);
	pos = 0;

	if ((options->boards & WB_BOARD_ANIME) > 0) {
		str[pos] = '1';
		pos++;
	}

	if ((options->boards & WB_BOARD_GENERAL) > 0) {
		str[pos] = '2';
		pos++;
	}

	if ((options->boards & WB_BOARD_HIGHRES) > 0) {
		str[pos] = '3';
		pos++;
	}

	str[pos] = '\0';

	return str;
}

/**
 * Adds a parameter to a URL. Always adds a '&' character.
 *
 * @param url - the URL to add a parameter to
 * @param name - the name of the new parameter
 * @param value - the value of the new parameter
 * @return a URL with the added parameter. IMPORTANT: the returned
 *   string must be freed with free().
 */
char *
add_url_param(char *url, char *name, char *value) {
	int new_length;
	char *new_url;

	new_length = strlen(url) + strlen(name) + strlen(value) + 3;
	new_url = (char *) malloc(new_length);

	snprintf(new_url, new_length, "%s&%s=%s", url, name, value);

	return new_url;
}

/**
 * Add URL parameters from an options structure.
 *
 * @param url - the URL to add parameters to
 * @param query_type - the wallbase.cc query type
 * @param options - the option structure
 * @return the parametrized URL. IMPORTANT: the returned URL should
 *   be freed with free().
 */
char *
add_url_params_from_options(char *url, int query_type, struct options *options) {
	char *new_url, *temp_url, *temp_value;

	new_url = (char *) malloc(strlen(url) + 1);
	strcpy(new_url, url);

	/* Add string query */
	if (options->query != NULL) {
		temp_url = add_url_param(new_url, "q", options->query);
		free(new_url);
		new_url = temp_url;
	}

	/* Add color */
	if (options->color != -1) {
		temp_value = get_color_string(options);
		temp_url = add_url_param(new_url, "color", temp_value);
		free(new_url);
		free(temp_value);
		new_url = temp_url;
	}

	/* Add res option */
	temp_value = get_res_opt_string(options);
	temp_url = add_url_param(new_url, "res_opt", temp_value);
	free(new_url);
	new_url = temp_url;

	/* Add resolution */
	temp_value = get_resolution_string(options);
	temp_url = add_url_param(new_url, "res", temp_value);
	free(new_url);
	free(temp_value);
	new_url = temp_url;

	/* Add sort by and sort order */
	if (query_type == WB_TYPE_SEARCH) {
		/* Add sort order */
		temp_value = get_sort_order_string(options);
		temp_url = add_url_param(new_url, "order_mode", temp_value);
		free(new_url);
		new_url = temp_url;

		/* Add sort by */
		temp_value = get_sort_by_string(options);
		temp_url = add_url_param(new_url, "order", temp_value);
		free(new_url);
		new_url = temp_url;
	}

	/* Add thumbnails per page*/
	temp_value = get_thpp_string(options);
	temp_url = add_url_param(new_url, "thpp", temp_value);
	free(new_url);
	free(temp_value);
	new_url = temp_url;

	/* Add purity */
	temp_value = get_purity_string(options);
	temp_url = add_url_param(new_url, "purity", temp_value);
	free(new_url);
	free(temp_value);
	new_url = temp_url;

	/* Add boards */
	temp_value = get_boards_string(options);
	temp_url = add_url_param(new_url, "board", temp_value);
	free(new_url);
	free(temp_value);
	new_url = temp_url;

	/* Add aspect ratio */
	temp_value = get_aspect_ratio_string(options);
	temp_url = add_url_param(new_url, "aspect", temp_value);
	free(new_url);
	free(temp_value);
	new_url = temp_url;

	/* Add toplist interval */
	if (query_type == WB_TYPE_TOPLIST) {
		temp_value = get_toplist_interval_string(options);
		temp_url = add_url_param(new_url, "ts", temp_value);
		free(new_url);
		new_url = temp_url;
	}

	return new_url;
}

/**
 * Get a query URL and the corresponding POST data according
 * to the options structure.
 *
 * @param options - the option structure
 * @return a wb_query structure containing a URL and POST data.
 *   IMPORTANT: the returned structure must be freed using
 *   wb_query_free().
 */
struct wb_query *
wb_generate_query(struct options *options) {
	struct wb_query *query;
	int query_type;
	char *url, *temp;
	const char *endpoint;

	query = (struct wb_query *) malloc(sizeof(struct wb_query));
	url = (char *) malloc(128);

	/* Determine the endpoint ot be used */
	query_type = get_query_type(options);

	switch (query_type) {
		case WB_TYPE_SEARCH:
			endpoint = URL_ENDPOINT_SEARCH;
			break;
		case WB_TYPE_TOPLIST:
			endpoint = URL_ENDPOINT_TOPLIST;
			break;
		case WB_TYPE_RANDOM:
			endpoint = URL_ENDPOINT_RANDOM;
			break;
	}

	/* Generate the endpoint URL */
	snprintf(url, 128, "%s%s%s", URL_BASE, endpoint, URL_ENDPOINT_SUFFIX);

	/* Add parameters from the option structure */
	temp = add_url_params_from_options(url, query_type, options);
	free(url);
	url = temp;

	/* Copy data to the final query structure */
	query->url = url;
	query->post_data = NULL;

	return query;
}

/**
 * Free a wb_query structure
 *
 * @param query - the structure to be freed
 */
void
wb_query_free(struct wb_query *query) {
	free(query->url);
	free(query->post_data);
	free(query);
}
