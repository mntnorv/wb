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

#ifndef INCLUDED_WB_STR_LIST_H
#define INCLUDED_WB_STR_LIST_H

struct wb_str_list {
	char *str;
	struct wb_str_list *next;
};

void wb_list_free(struct wb_str_list *list);
struct wb_str_list *wb_list_append(struct wb_str_list *list, const char *str);
struct wb_str_list *wb_list_append_all(struct wb_str_list *dest, struct wb_str_list *src);
struct wb_str_list *wb_list_prepend(struct wb_str_list *list, const char *str);

#endif
