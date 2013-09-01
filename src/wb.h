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

#ifndef INCLUDED_WB_H
#define INCLUDED_WB_H

#include "types.h"

struct options *
wb_get_default_options();

struct wb_str_list *
wb_login(const char *username, const char *password);

char *
wb_get_login_csrf_token(struct wb_str_list **cookies);

struct wb_str_list *
wb_get_image_page_urls(const char *url, const char *post_data, struct wb_str_list *cookies);

struct wb_str_list *
wb_get_image_urls(const char *url, const char *post_data, struct wb_str_list *cookies, struct options *options);

char *
wb_get_image_url(const char *url, struct wb_str_list *cookies);

#endif
