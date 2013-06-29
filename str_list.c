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
#include "str_list.h"

/**
 * Creates a new wb_str_list element.
 *
 * @param str - the string data
 * @param next - the next element in the list
 * @return a pointer to the new element. IMPORTANT: the returned
 *   element must be freed with free().
 */
struct wb_str_list *
wb_list_new_elem(char *str, struct wb_str_list *next) {
	struct wb_str_list *new;

	new = (struct wb_str_list *) malloc(sizeof(struct wb_str_list));
	new->str = str;
	new->next = next;

	return new;
}

/**
 * Frees all elements in the list
 *
 * @param list - pointer to the first element in the list
 */
void
wb_list_free(struct wb_str_list *list) {
	struct wb_str_list *elem = list;
	struct wb_str_list *prev;

	while (elem != NULL) {
		prev = elem;
		elem = elem->next;
		free(prev->str);
		free(prev);
	}
}

/**
 * Appends a string to the end of the list.
 * The string is copied so it can be freed after appending.
 * Much slower that wb_list_prepend(), because every time
 * it must go through all the elements in the list.
 *
 * @param list - pointer to the first element of the list
 * @param str - the string to be appended
 * @return pointer to the first element of the list with the
 *   new string appended.
 */
struct wb_str_list *
wb_list_append(struct wb_str_list *list, const char *str) {
	struct wb_str_list *last = list;
	struct wb_str_list *new;

	new = wb_list_new_elem(strdup(str), NULL);

	if (last != NULL) {
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = new;
		return list;
	} else {
		return new;
	}
}

/**
 * Prepends a string to the start of the list.
 * The string is copied so it can be freed after prepending.
 *
 * @param list - pointer to the first element of the list
 * @param str - the string to be prepended
 * @return pointer to the first element of the list with the
 *   new string prepended.
 */
struct wb_str_list *
wb_list_prepend(struct wb_str_list *list, const char *str) {
	struct wb_str_list *new;

	new = wb_list_new_elem(strdup(str), list);

	return new;
}
