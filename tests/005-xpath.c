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
#include "str_list.h"
#include "xpath.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Mocks */
void wb_list_free(struct wb_str_list *list) {
}

struct wb_str_list *wb_list_append(struct wb_str_list *list, const char *str) {
	TEST_ASSERT_EQUAL_STRING("test", str);
	return NULL;
}

struct wb_str_list *wb_list_prepend(struct wb_str_list *list, const char *str) {
	TEST_ASSERT_EQUAL_STRING("test", str);
	return NULL;
}

/* Tests */
void test_xpathEvalExpr() {
	xpath_eval_expr(
		"<root><node attr=\"test\" /><node attr=\"test\" /><node attr=\"test\" /><node anotherattr=\"test\" /></root>",
		"//node/@attr",
		NULL
	);

	xpath_eval_expr(
		"<root><node check=\"true\" attr=\"test\" /><node check=\"false\" attr=\"FAIL\" /><node check=\"true\" attr=\"test\" /></root>",
		"/root/node[@check='true']/@attr",
		NULL
	);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_xpathEvalExpr, __LINE__);
	return UnityEnd();
}
