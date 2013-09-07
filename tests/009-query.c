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

#include "unity.h"
#include "types.h"
#include "query.h"
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
	options.res_opt = WB_RES_EXACTLY;
	options.aspect_ratio = 0;

	options.flags = 0;
	options.purity = WB_PURITY_ALL;
	options.boards = WB_BOARD_ALL;

	options.sort_by = WB_SORT_RELEVANCE;
	options.sort_order = WB_SORT_DESCENDING;
}

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_wbGenerateQuery_search() {
	struct wb_query *query;

	resetOptions();
	options.query = "testquery";
	options.res_x = 1920;
	options.res_y = 1080;
	options.res_opt = WB_RES_AT_LEAST;
	options.purity = WB_PURITY_SFW | WB_PURITY_SKETCHY;
	options.boards = WB_BOARD_GENERAL;

	query = wb_generate_query(&options);

	TEST_ASSERT_NOT_NULL(query);

	if (query != NULL) {
		TEST_ASSERT_EQUAL_STRING("http://wallbase.cc/search/index/%d?section=wallpapers&q=testquery&res_opt=gteq&res=1920x1080&order_mode=desc&order=relevance&thpp=20&purity=110&board=2&aspect=0.00", query->url);
		TEST_ASSERT_NULL(query->post_data);

		wb_query_free(query);
	}

	resetOptions();
	options.color = 0x123456;
	options.res_opt = WB_RES_EXACTLY;
	options.purity = WB_PURITY_NSFW;
	options.boards = WB_BOARD_ALL;
	options.aspect_ratio = 16/9.0;
	options.sort_by = WB_SORT_DATE;
	options.sort_order = WB_SORT_DESCENDING;

	query = wb_generate_query(&options);

	TEST_ASSERT_NOT_NULL(query);

	if (query != NULL) {
		TEST_ASSERT_EQUAL_STRING("http://wallbase.cc/search/index/%d?section=wallpapers&color=123456&res_opt=eqeq&res=0x0&order_mode=desc&order=date&thpp=20&purity=001&board=123&aspect=1.78", query->url);
		TEST_ASSERT_NULL(query->post_data);

		wb_query_free(query);
	}
}

void test_wbGenerateQuery_toplist() {
	struct wb_query *query;

	resetOptions();
	options.toplist = WB_TOPLIST_1W;

	query = wb_generate_query(&options);

	TEST_ASSERT_NOT_NULL(query);

	if (query != NULL) {
		TEST_ASSERT_EQUAL_STRING("http://wallbase.cc/toplist/index/%d?section=wallpapers&res_opt=eqeq&res=0x0&thpp=20&purity=111&board=123&aspect=0.00&ts=1w", query->url);
		TEST_ASSERT_NULL(query->post_data);

		wb_query_free(query);
	}
}

void test_wbGenerateQuery_random() {
	struct wb_query *query;

	resetOptions();
	options.flags |= WB_FLAG_RANDOM;

	query = wb_generate_query(&options);

	TEST_ASSERT_NOT_NULL(query);

	if (query != NULL) {
		TEST_ASSERT_EQUAL_STRING("http://wallbase.cc/random/index/%d?section=wallpapers&res_opt=eqeq&res=0x0&thpp=20&purity=111&board=123&aspect=0.00", query->url);
		TEST_ASSERT_NULL(query->post_data);

		wb_query_free(query);
	}
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_wbGenerateQuery_search, __LINE__);
	RUN_TEST(test_wbGenerateQuery_toplist, __LINE__);
	RUN_TEST(test_wbGenerateQuery_random, __LINE__);
	return UnityEnd();
}
