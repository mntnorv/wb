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
#include "base64.c"

/* Unity set up and tear down */
void setUp() {
}

void tearDown() {
}

/* Tests */
void test_b64Decode() {
	char *res;

	res = b64_decode("VGVzdGluZyBiYXNlNjQgZGVjb2Rl");
	TEST_ASSERT_EQUAL_STRING("Testing base64 decode", res);
	free(res);

	res = b64_decode("VEhFIFFVSUNLIEJST1dOIEZPWCBKVU1QUyBPVkVSIFRIRSBMQVpZIERPRw0KdGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw0KMDEyMzQ1Njc4OSwuLzsnXFtdLT0qKzw+PzoifHt9KCkhQCMkJV4m");
	TEST_ASSERT_EQUAL_STRING("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\r\nthe quick brown fox jumps over the lazy dog\r\n0123456789,./;'\\[]-=*+<>?:\"|{}()!@#$%^&", res);
	free(res);
}

/* Main */
int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_b64Decode, __LINE__);
	return UnityEnd();
}