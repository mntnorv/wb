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
#include "filesys.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_dirExists_valid() {
	int res;

	res = dir_exists(".");
	TEST_ASSERT_EQUAL_INT(1, res);

	res = dir_exists("unity");
	TEST_ASSERT_EQUAL_INT(1, res);
}

void test_dirExists_invalid() {
	int res;

	res = dir_exists("random-asdkfgakjhfg-dir");
	TEST_ASSERT_EQUAL_INT(0, res);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_dirExists_valid, __LINE__);
	RUN_TEST(test_dirExists_invalid, __LINE__);
	return UnityEnd();
}