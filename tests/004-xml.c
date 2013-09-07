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
#include <string.h>

#include "unity.h"
#include "xml.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Mocks */
void net_init() {
}

void net_cleanup() {
}

char *net_get_response(const char *url, const char *post_data, struct wb_str_list **cookies, int update_cookies) {
	char *html = "<html><body><a href=\"test\"></body></html>";
	char *dyn_html = (char *) malloc(strlen(html) + 1);
	strncpy(dyn_html, html, strlen(html));
	return dyn_html;
}

int net_connect(const char *url, const char *post_data, struct wb_str_list **cookies, int update_cookies) {
	return 0;
}

/* Tests */
void test_convertHtmlToXml_valid() {
	char *res;

	res = convert_html_to_xml("<html><body><a href=\"test\"></body></html>");
	TEST_ASSERT_EQUAL_STRING("<html>\n<head>\n<title></title>\n</head>\n<body>\n<a href=\"test\"></a>\n</body>\n</html>\n", res);
	free(res);
}

void test_convertHtmlToXml_invalid() {
	char *res;

	res = convert_html_to_xml("<html></fake tag here></html>");
	TEST_ASSERT_EQUAL_STRING("<html>\n<head>\n<title></title>\n</head>\n<body></body>\n</html>\n", res);
	free(res);

	res = convert_html_to_xml("complete garbage \1\2\3\4\5\6\7");
	TEST_ASSERT_EQUAL_STRING("<html>\n<head>\n<title></title>\n</head>\n<body>complete garbage</body>\n</html>\n", res);
	free(res);
}

void test_netGetResponseAsXml() {
	char *res;

	res = net_get_response_as_xml("fake url", NULL, NULL, 0);
	TEST_ASSERT_EQUAL_STRING("<html>\n<head>\n<title></title>\n</head>\n<body>\n<a href=\"test\"></a>\n</body>\n</html>\n", res);
	free(res);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_convertHtmlToXml_valid, __LINE__);
	RUN_TEST(test_convertHtmlToXml_invalid, __LINE__);
	RUN_TEST(test_netGetResponseAsXml, __LINE__);
	return UnityEnd();
}
