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

#include "unity.h"
#include "str_list.h"
#include "str_list.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_wbListAppend() {
	struct wb_str_list *list = NULL;
	struct wb_str_list *list_element = NULL;
	int n = 0;
	char *generated_str = (char *) malloc(strlen("teststr0") + 1);

	list = wb_list_append(list, "teststr1");
	list = wb_list_append(list, "teststr2");
	list = wb_list_append(list, "teststr3");

	list_element = list;
	while(list_element != NULL) {
		n++;
		sprintf(generated_str, "%s%d", "teststr", n);
		TEST_ASSERT_EQUAL_STRING(generated_str, list_element->str);
		list_element = list_element->next;
	}

	TEST_ASSERT_EQUAL_INT(3, n);

	free(generated_str);
	wb_list_free(list);
}

void test_wbListPrepend() {
	struct wb_str_list *list = NULL;
	struct wb_str_list *list_element = NULL;
	int n = 3;
	char *generated_str = (char *) malloc(strlen("teststr0") + 1);

	list = wb_list_prepend(list, "teststr1");
	list = wb_list_prepend(list, "teststr2");
	list = wb_list_prepend(list, "teststr3");

	list_element = list;
	while(list_element != NULL) {
		sprintf(generated_str, "%s%d", "teststr", n);
		TEST_ASSERT_EQUAL_STRING(generated_str, list_element->str);
		list_element = list_element->next;
		n--;
	}

	TEST_ASSERT_EQUAL_INT(0, n);

	free(generated_str);
	wb_list_free(list);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_wbListAppend, __LINE__);
	RUN_TEST(test_wbListPrepend, __LINE__);
	return UnityEnd();
}
