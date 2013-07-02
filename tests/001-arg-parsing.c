#include "unity.h"
#include "types.h"
#include "error.h"
#include "args.c"

struct options options;

void setUp() {
}

void tearDown() {
}

void wb_error(const char *format, ...) {	
}

void wb_error_no_prefix(const char *fomrat, ...) {
}

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

int main(int argc, char *argv[]) {
	Unity.TestFile=__FILE__;
	UnityBegin();
	RUN_TEST(test_parseOpt_aspectRatio_valid, __LINE__);
	RUN_TEST(test_parseOpt_aspectRatio_invalid, __LINE__);
	RUN_TEST(test_parseOpt_color_valid, __LINE__);
	RUN_TEST(test_parseOpt_color_invalid, __LINE__);
	return UnityEnd();
}