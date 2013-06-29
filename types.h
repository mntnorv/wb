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

#ifndef INCLUDED_WB_TYPES_H
#define INCLUDED_WB_TYPES_H

#include "str_list.h"

/**************************************************
 * Defines
 **************************************************/

/* Search types */
#define WB_TYPE_SEARCH         1
#define WB_TYPE_TOPLIST        2
#define WB_TYPE_COLOR          3
#define WB_TYPE_RANDOM         4

/* Sort types */
#define WB_SORT_RELEVANCE      1
#define WB_SORT_VIEWS          2
#define WB_SORT_DATE           3
#define WB_SORT_FAVORITES      4

/* Sort orders */
#define WB_SORT_ASCENDING      0
#define WB_SORT_DESCENDING     1

/* Resolution options */
#define WB_RES_EXACTLY         0
#define WB_RES_AT_LEAST        1

/* Flags */
#define WB_FLAG_PRINT_ONLY  0x01

/* wallbase.cc purities */
#define WB_PURITY_SFW       0x01
#define WB_PURITY_SKETCHY   0x02
#define WB_PURITY_NSFW      0x04
#define WB_PURITY_ALL       0x07

/* wallbase.cc wallpaper boards */
#define WB_BOARD_GENERAL    0x01
#define WB_BOARD_ANIME      0x02
#define WB_BOARD_HIGHRES    0x04
#define WB_BOARD_ALL        0x07

/* ARGP option keys */
#define WB_KEY_PRINT_ONLY    300
#define WB_KEY_MANGA         301

/**************************************************
 * Structs
 **************************************************/

struct curl_response {
	size_t size;
	char *data;
};

struct options {
	char *username, *password;
	unsigned char search_type;
	char *dir;
	char *query;
	char *toplist_interval;
	int color;
	int images, images_per_page;
	unsigned char flags, purity, boards;
	int res_x, res_y;
	unsigned char res_opt;
	float aspect_ratio;
	unsigned char sort_by, sort_order;
};

#endif
