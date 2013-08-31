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

#include "unity.h"
#include "query.c"

struct options options;

/* Functions that return to a known state */
void resetOptions() {
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
}

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_wbGenerateQuery() {
	/*int res;

	res = dir_exists(".");
	TEST_ASSERT_EQUAL_INT(1, res);

	res = dir_exists("unity");
	TEST_ASSERT_EQUAL_INT(1, res);*/
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_wbGenerateQuery, __LINE__);
	return UnityEnd();
}
