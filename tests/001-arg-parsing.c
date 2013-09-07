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
#include "error.h"
#include "filesys.h"
#include "args.c"

struct options options;

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Mock functions */
void wb_error(const char *format, ...) {	
}

void wb_error_no_prefix(const char *format, ...) {
}

int dir_exists(const char *path) {
	return 1;
}

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

/* Tests*/
void test_parseOpt_aspectRatio_valid() {
	int res;

	resetOptions();
	res = parse_opt('a', "16:9", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_FLOAT(16.0f/9.0f, options.aspect_ratio);

	resetOptions();
	res = parse_opt('a', "4:3", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_FLOAT(4.0f/3.0f, options.aspect_ratio);
}

void test_parseOpt_aspectRatio_invalid() {
	int res;

	resetOptions();
	res = parse_opt('a', "169", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "16:0", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "0:9", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "garbage", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_color_valid() {
	int res;

	resetOptions();
	res = parse_opt('c', "0x123abc", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(0x123abc, options.color);

	resetOptions();
	res = parse_opt('c', "bd1dea", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_FLOAT(0xbd1dea, options.color);
}

void test_parseOpt_color_invalid() {
	int res;

	resetOptions();
	res = parse_opt('a', "ff", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "0x1234567", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "-fabcd", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('a', "0fail0", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_downloadDir_valid() {
	int res;

	resetOptions();
	res = parse_opt('d', "unity", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("unity", options.dir);

	resetOptions();
	res = parse_opt('d', ".", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING(".", options.dir);
}

void test_parseOpt_imageNum_valid() {
	int res;

	resetOptions();
	res = parse_opt('n', "1", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(1, options.images);

	resetOptions();
	res = parse_opt('n', "1000", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(1000, options.images);
}

void test_parseOpt_imageNum_invalid() {
	int res;

	resetOptions();
	res = parse_opt('n', "0", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('n', "-1", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('n', "0xfakenumber", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_password_valid() {
	int res;

	resetOptions();
	res = parse_opt('p', "password", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("password", options.password);
}

void test_parseOpt_query_valid() {
	int res;

	resetOptions();
	res = parse_opt('q', "myquery", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("myquery", options.query);
}

void test_parseOpt_resolution_valid() {
	int res;

	resetOptions();
	res = parse_opt('r', "1920x1080", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(1920, options.res_x);
	TEST_ASSERT_EQUAL_INT(1080, options.res_y);

	resetOptions();
	res = parse_opt('r', "=800x600", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(800, options.res_x);
	TEST_ASSERT_EQUAL_INT(600, options.res_y);
	TEST_ASSERT_EQUAL_INT(WB_RES_EXACTLY, options.res_opt);
}

void test_parseOpt_resolution_invalid() {
	int res;

	resetOptions();
	res = parse_opt('r', "10", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('r', "0x1080", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('r', "=0x1080", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('r', "1920x0", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('r', "=1920x0", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('r', "numxnum", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_sort_valid() {
	int res;

	resetOptions();
	res = parse_opt('s', "r", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_RELEVANCE, options.sort_by);

	resetOptions();
	res = parse_opt('s', "+v", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_VIEWS, options.sort_by);
	TEST_ASSERT_EQUAL_INT(WB_SORT_ASCENDING, options.sort_order);

	resetOptions();
	res = parse_opt('s', "-f", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_FAVORITES, options.sort_by);
	TEST_ASSERT_EQUAL_INT(WB_SORT_DESCENDING, options.sort_order);

	resetOptions();
	res = parse_opt('s', "d", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_DATE, options.sort_by);

	resetOptions();
	res = parse_opt('s', "relevance", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_RELEVANCE, options.sort_by);

	resetOptions();
	res = parse_opt('s', "+views", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_VIEWS, options.sort_by);
	TEST_ASSERT_EQUAL_INT(WB_SORT_ASCENDING, options.sort_order);

	resetOptions();
	res = parse_opt('s', "-favorites", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_FAVORITES, options.sort_by);
	TEST_ASSERT_EQUAL_INT(WB_SORT_DESCENDING, options.sort_order);

	resetOptions();
	res = parse_opt('s', "date", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_SORT_DATE, options.sort_by);
}

void test_parseOpt_sort_invalid() {
	int res;

	resetOptions();
	res = parse_opt('s', "randomstr", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('s', "favs", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('s', "+favorites+", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('s', "v+", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('s', "d-", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_toplist_valid() {
	int res;

	resetOptions();
	res = parse_opt('t', "1d", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_1D, options.toplist);

	resetOptions();
	res = parse_opt('t', "3d", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_3D, options.toplist);

	resetOptions();
	res = parse_opt('t', "1w", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_1W, options.toplist);

	resetOptions();
	res = parse_opt('t', "2w", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_2W, options.toplist);

	resetOptions();
	res = parse_opt('t', "1m", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_1M, options.toplist);

	resetOptions();
	res = parse_opt('t', "2m", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_2M, options.toplist);

	resetOptions();
	res = parse_opt('t', "3m", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_3M, options.toplist);

	resetOptions();
	res = parse_opt('t', "0", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_TOPLIST_ALL_TIME, options.toplist);
}

void test_parseOpt_toplist_invalid() {
	int res;

	resetOptions();
	res = parse_opt('t', "randomstr", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('t', "2d", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);

	resetOptions();
	res = parse_opt('t', "3w", &options);
	TEST_ASSERT_EQUAL_INT(-1, res);
}

void test_parseOpt_username_valid() {
	int res;

	resetOptions();
	res = parse_opt('u', "whatuser", &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("whatuser", options.username);
}

void test_parseOpt_flags() {
	int res;

	resetOptions();
	res = parse_opt('S', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_PURITY_SFW, options.purity & WB_PURITY_SFW);

	res = parse_opt('K', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_PURITY_SKETCHY, options.purity & WB_PURITY_SKETCHY);

	res = parse_opt('N', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_PURITY_NSFW, options.purity & WB_PURITY_NSFW);

	resetOptions();
	res = parse_opt('G', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_BOARD_GENERAL, options.boards & WB_BOARD_GENERAL);

	res = parse_opt('A', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_BOARD_ANIME, options.boards & WB_BOARD_ANIME);

	res = parse_opt('H', NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_BOARD_HIGHRES, options.boards & WB_BOARD_HIGHRES);

	resetOptions();
	res = parse_opt(WB_KEY_PRINT_ONLY, NULL, &options);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(WB_FLAG_PRINT_ONLY, options.flags & WB_FLAG_PRINT_ONLY);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_parseOpt_aspectRatio_valid, __LINE__);
	RUN_TEST(test_parseOpt_aspectRatio_invalid, __LINE__);
	RUN_TEST(test_parseOpt_color_valid, __LINE__);
	RUN_TEST(test_parseOpt_color_invalid, __LINE__);
	RUN_TEST(test_parseOpt_downloadDir_valid, __LINE__);
	RUN_TEST(test_parseOpt_imageNum_valid, __LINE__);
	RUN_TEST(test_parseOpt_imageNum_invalid, __LINE__);
	RUN_TEST(test_parseOpt_password_valid, __LINE__);
	RUN_TEST(test_parseOpt_query_valid, __LINE__);
	RUN_TEST(test_parseOpt_resolution_valid, __LINE__);
	RUN_TEST(test_parseOpt_resolution_invalid, __LINE__);
	RUN_TEST(test_parseOpt_sort_valid, __LINE__);
	RUN_TEST(test_parseOpt_sort_invalid, __LINE__);
	RUN_TEST(test_parseOpt_toplist_valid, __LINE__);
	RUN_TEST(test_parseOpt_toplist_invalid, __LINE__);
	RUN_TEST(test_parseOpt_username_valid, __LINE__);
	RUN_TEST(test_parseOpt_flags, __LINE__);
	return UnityEnd();
}
