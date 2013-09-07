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

#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "types.h"
#include "str_list.c"
#include "net.c"

/* Unity set up and tear down */
void setUp() {
	net_init();
}

void tearDown() {
	net_cleanup();
}

/* Mocks */
void wb_error(const char *format, ...) {
}

/* Tests */
void test_netGetResponse_validUrl() {
	char *res;

	res = net_get_response("www.google.com", NULL, NULL, 0);
	TEST_ASSERT_NOT_NULL(res);
	free(res);
}

void test_netGetResponse_invalidUrl() {
	char *res;

	res = net_get_response("invalid.test.url", NULL, NULL, 0);
	TEST_ASSERT_NULL(res);
}

void test_netGetResponse_cookies() {
	char *res;
	struct wb_str_list *cookies = NULL;

	res = net_get_response("www.google.com", NULL, &cookies, 0);
	TEST_ASSERT_NULL(cookies);
	free(res);

	res = net_get_response("www.google.com", NULL, &cookies, 1);
	TEST_ASSERT_NOT_NULL(cookies);
	free(res);
}

void test_netGetResponse_post() {
	char *res_nopost, *res_post;

	res_nopost = net_get_response("https://duckduckgo.com", NULL, NULL, 0);
	res_post = net_get_response("https://duckduckgo.com", "q=test", NULL, 0);
	TEST_ASSERT_NOT_NULL(res_nopost);
	TEST_ASSERT_NOT_NULL(res_post);
	TEST_ASSERT_TRUE(strcmp(res_nopost, res_post) != 0);
	free(res_nopost);
	free(res_post);
}

void test_netDownload_valid() {
	int res;

	res = net_download("https://www.google.com/images/srpr/logo4w.png", ".", "test");
	TEST_ASSERT_EQUAL_INT(0, res);
	res = remove("test");
	TEST_ASSERT_EQUAL_INT(0, res);
}

void test_netDownload_invalid() {
	int res;

	res = net_download("invalid.test.url", ".", "test");
	TEST_ASSERT_EQUAL_INT(-1, res);
	res = remove("test");
	TEST_ASSERT_NOT_EQUAL(0, res);
}

void test_netDownloadList_valid() {
	int res;
	struct wb_str_list *urls = NULL;

	urls = wb_list_prepend(urls, "https://www.google.com/images/srpr/logo4w.png");
	urls = wb_list_prepend(urls, "https://duckduckgo.com/assets/logo_homepage.normal.v102.png");

	res = net_download_list(urls, ".");
	TEST_ASSERT_EQUAL_INT(0, res);
	res = remove("logo4w.png");
	TEST_ASSERT_EQUAL_INT(0, res);
	res = remove("logo_homepage.normal.v102.png");
	TEST_ASSERT_EQUAL_INT(0, res);

	wb_list_free(urls);
}

void test_netDownloadList_invalid() {
	int res;
	struct wb_str_list *urls = NULL;

	urls = wb_list_prepend(urls, "invalid-test-1");
	urls = wb_list_prepend(urls, "invalid-test-2");

	res = net_download_list(urls, ".");
	TEST_ASSERT_EQUAL_INT(-1, res);
	res = remove("invalid-test-1");
	TEST_ASSERT_NOT_EQUAL(0, res);
	res = remove("invalid-test-1");
	TEST_ASSERT_NOT_EQUAL(0, res);

	wb_list_free(urls);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_netGetResponse_validUrl, __LINE__);
	RUN_TEST(test_netGetResponse_invalidUrl, __LINE__);
	RUN_TEST(test_netGetResponse_cookies, __LINE__);
	RUN_TEST(test_netGetResponse_post, __LINE__);
	RUN_TEST(test_netDownload_valid, __LINE__);
	RUN_TEST(test_netDownload_invalid, __LINE__);
	RUN_TEST(test_netDownloadList_valid, __LINE__);
	RUN_TEST(test_netDownloadList_invalid, __LINE__);
	return UnityEnd();
}
