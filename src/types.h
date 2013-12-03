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

#ifndef INCLUDED_WB_TYPES_H
#define INCLUDED_WB_TYPES_H

#include "str_list.h"

/**************************************************
 * Defines
 **************************************************/

/* Size of a static array */
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* Search types */
#define WB_TYPE_SEARCH         0
#define WB_TYPE_TOPLIST        1
#define WB_TYPE_RANDOM         2
#define WB_TYPE_COLLECTION     3

/* Sort types */
#define WB_SORT_RELEVANCE      1
#define WB_SORT_VIEWS          2
#define WB_SORT_DATE           3
#define WB_SORT_FAVORITES      4
#define WB_SORT_RANDOM         5

/* Sort orders */
#define WB_SORT_ASCENDING      0
#define WB_SORT_DESCENDING     1

/* Toplist intervals */
#define WB_TOPLIST_NONE        0
#define WB_TOPLIST_1D          1
#define WB_TOPLIST_3D          2
#define WB_TOPLIST_1W          3
#define WB_TOPLIST_2W          4
#define WB_TOPLIST_1M          5
#define WB_TOPLIST_2M          6
#define WB_TOPLIST_3M          7
#define WB_TOPLIST_ALL_TIME    8

/* Resolution options */
#define WB_RES_EXACTLY         0
#define WB_RES_AT_LEAST        1

/* Flags */
#define WB_FLAG_RANDOM      0x01
#define WB_FLAG_PROGRESS    0x02

/* wallbase.cc purities */
#define WB_PURITY_SFW       0x01
#define WB_PURITY_SKETCHY   0x02
#define WB_PURITY_NSFW      0x04
#define WB_PURITY_ALL       (WB_PURITY_SFW | WB_PURITY_SKETCHY | WB_PURITY_NSFW)

/* wallbase.cc wallpaper boards */
#define WB_BOARD_GENERAL    0x01
#define WB_BOARD_ANIME      0x02
#define WB_BOARD_HIGHRES    0x04
#define WB_BOARD_ALL        (WB_BOARD_GENERAL | WB_BOARD_ANIME | WB_BOARD_HIGHRES)

/* getopt() option keys */
#define WB_KEY_USAGE         300
#define WB_KEY_RANDOM        301

/**************************************************
 * Structs
 **************************************************/

struct curl_response {
	size_t size;
	char *data;
};

struct options {
	char *username, *password;
	char *query;
	unsigned char toplist;
	int collection_id;
	int color;
	int images, images_per_page;
	unsigned char flags, purity, boards;
	int res_x, res_y;
	unsigned char res_opt;
	float aspect_ratio;
	unsigned char sort_by, sort_order;
};

#endif
