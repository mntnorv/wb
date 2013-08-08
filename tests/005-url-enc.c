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
#include "url_enc.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_urlEncode() {
	char *res;

	res = url_encode("simple_test");
	TEST_ASSERT_EQUAL_STRING("simple_test", res);
	free(res);

	res = url_encode("A more ɔomqliɔɒƚɘb test");
	TEST_ASSERT_EQUAL_STRING("A+more+%c9%94omqli%c9%94%c9%92%c6%9a%c9%98b+test", res);
	free(res);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_urlEncode, __LINE__);
	return UnityEnd();
}