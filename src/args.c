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
#include <stdio.h>
#include <stdarg.h>
#include <libgen.h>
#include <getopt.h>

#include "args.h"
#include "error.h"
#include "types.h"

/**************************************************
 * Constant arrays
 **************************************************/

/* Toplist intervals */
static const char *WB_TOPLIST_INTERVALS[] = {
	"a", "1d", "3d", "1w", "2w", "1m", "2m", "3m"
};
static const unsigned char WB_TOPLIST_INTERVAL_IDS[] = {
	WB_TOPLIST_ALL_TIME, WB_TOPLIST_1D, WB_TOPLIST_3D,
	WB_TOPLIST_1W, WB_TOPLIST_2W, WB_TOPLIST_1M, WB_TOPLIST_2M,
	WB_TOPLIST_3M
};

#define WB_TOPLIST_INTERVALS_SIZE ARR_SIZE(WB_TOPLIST_INTERVALS)

/* Sort types */
static const char *WB_SORT_TYPES_SHORT[] = {
	"r", "v", "d", "f"
};
static const char *WB_SORT_TYPES_LONG[] = {
	"relevance", "views", "date", "favorites"
};
static const unsigned char WB_SORT_TYPE_IDS[] = {
	WB_SORT_RELEVANCE, WB_SORT_VIEWS, WB_SORT_DATE, WB_SORT_FAVORITES
};

#define WB_SORT_TYPES_SIZE ARR_SIZE(WB_SORT_TYPE_IDS)

/**************************************************
 * Constant strings
 **************************************************/

static char *APP_INVOKE_NAME = "wb";

static const char *ABOUT = "wb -- A wallbase.cc image search tool";
static const char *BUG_ADDRESS = "<mntnorv+bugs at gmail dot com>";

static const char *LONG_HELP = "\
  -a, --aspect=ASPECT        Search for images with this aspect ratio\n\
  -A, --anime, --manga       Search in the Anime / Manga board\n\
  -c, --color=COLOR          Search for images containing this color\n\
  -G, --general              Search in the Wallpapers / General board\n\
  -H, --high-res             Search in the High Resolution board\n\
  -K, --sketchy              Search for sketchy images\n\
  -n, --images=COUNT         Number of images to download\n\
  -N, --nsfw                 Search for NSFW images (requires wallbase.cc login\n\
                             information)\n\
  -p, --password=PASSWORD    wallbase.cc password, required for NSFW content\n\
  -P, --show-progress        Show progress information (off by default)\n\
  -q, --query=STRING         Search for images related to this string\n\
  -r, --resolution=RES       Search for images with at least or exactly this\n\
                             resolution\n\
  -R, --random               Get randomly sorted images. Purity, board,\n\
                             resolution and aspect ratio filters can all be used\n\
                             with this option.\n\
  -s, --sort=SORT            Specify the sort order\n\
  -S, --sfw                  Search for SFW images\n\
  -t, --toplist=INTERVAL     Get the top images in the specified time interval\n\
  -u, --username=USERNAME    wallbase.cc username, required for NSFW content\n\
  -h, --help                 Give this help list\n\
      --usage                Give a short usage message\n\
  -V, --version              Print program version\n\
\n\
Mandatory or optional arguments to long options are also mandatory or optional\n\
for any corresponding short options.";

/**************************************************
 * Formats
 **************************************************/

static const char *FORMAT_SHORT_USAGE = "Usage: %s [OPTION...]";
static const char *FORMAT_LONG_USAGE = "\
Usage: %s [-AGHKNPRShV] [-a ASPECT] [-c COLOR] [-n COUNT] [-p PASSWORD]\n\
            [-q STRING] [-r RES] [-s SORT] [-t INTERVAL] [-u USERNAME]\n";

static const char *FORMAT_SHORT_HELP = "Try '%s --help' or '%s --usage' for more information.";

static const char *FORMAT_VERSION = "\
wb, version %s\nCopyright (C) 2013 Mantas Norvaiša\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";

/**************************************************
 * getopt specific vars
 **************************************************/

static const char *GETOPT_SHORT_OPTIONS = "a:c:n:p:q:r:s:t:u:AGHKNPRShV";
static struct option GETOPT_LONG_OPTIONS[] = {
	/* Options with arguments */
	{"aspect",        required_argument, 0, 'a'},
	{"color",         required_argument, 0, 'c'},
	{"images",        required_argument, 0, 'n'},
	{"password",      required_argument, 0, 'p'},
	{"query",         required_argument, 0, 'q'},
	{"resolution",    required_argument, 0, 'r'},
	{"sort",          required_argument, 0, 's'},
	{"toplist",       required_argument, 0, 't'},
	{"username",      required_argument, 0, 'u'},

	/* Options without arguments */
	{"anime",         no_argument,       0, 'A'},
	{"manga",         no_argument,       0, 'A'},
	{"general",       no_argument,       0, 'G'},
	{"high-res",      no_argument,       0, 'H'},
	{"sketchy",       no_argument,       0, 'K'},
	{"nsfw",          no_argument,       0, 'N'},
	{"show-progress", no_argument,       0, 'P'},
	{"random",        no_argument,       0, 'R'},
	{"sfw",           no_argument,       0, 'S'},
	{"help",          no_argument,       0, 'h'},
	{"version",       no_argument,       0, 'V'},

	/* Long-only options */
	{"usage",         no_argument,       0, WB_KEY_USAGE},
	{0}
};

/**************************************************
 * Function implementations
 **************************************************/

/**
 * Prints an invalid argument error.
 *
 * @param name - argument name
 * @param arg - the argument itself
 */
void
invalid_arg_error(char *name, char *arg) {
	wb_error("invalid %s -- %s", name, arg);
	wb_error_no_prefix(FORMAT_SHORT_HELP, APP_INVOKE_NAME, APP_INVOKE_NAME);
}

/**
 * Prints the full help.
 */
void
print_full_help() {
	printf(FORMAT_SHORT_USAGE, APP_INVOKE_NAME);
	printf("\n%s\n\n%s\n\n", ABOUT, LONG_HELP);
	printf("Report bugs to %s\n", BUG_ADDRESS);
}

/**
 * Prints the full usage info.
 */
void
print_full_usage() {
	printf(FORMAT_LONG_USAGE, APP_INVOKE_NAME);
}

/**
 * Prints version info.
 */
void
print_version() {
	printf(FORMAT_VERSION, VERSION);
}

/**
 * Checks if a string is in an array
 *
 * @param str - the string to search for
 * @param array - the array to search in
 * @param arr_size - size of the array
 * @return index of the string in the array if found, -1 otherwise
 */
int
find_in_array(const char *str, const char *array[], int arr_size) {
	int i;
	for (i = 0; i < arr_size; i++) {
		if (strcmp(str, array[i]) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * Parses the aspect ratio from a string.
 *
 * @param arg - a string containing the aspect ratio.
 *   Format <number>:<number>.
 * @param options - pointer to the options struct.
 * @return 0 on success, -1 otherwise
 */
int
parse_aspect_ratio(char *arg, struct options *options) {
	int num;
	char *temp_arg, *num_end;

	temp_arg = arg;

	/* Try to read the first number (before ':') */
	num = strtol(temp_arg, &num_end, 10);
	if (num <= 0) {
		return -1;
	} else {
		options->aspect_ratio = num;
		temp_arg = num_end;
	}

	/* Check for a ':' between numbers */
	if (temp_arg[0] != ':') {
		return -1;
	} else {
		temp_arg++;
	}

	/* Try to read the second number */
	num = strtol(temp_arg, &num_end, 10);
	if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
		return -1;
	} else {
		options->aspect_ratio = options->aspect_ratio / num;
	}

	return 0;
}

/**
 * Parses a color from a string.
 *
 * @param arg - a string containing a color. The color must be
 *   represented as a 24-bit hexadecimal number. The '0x' prefix
 *   is optional.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_color(char *arg, struct options *options) {
	int num;
	char *num_end;

	if (strlen(arg) != 6 && strlen(arg) != 8) {
		return -1;
	}

	num = strtol(arg, &num_end, 16);
	if (arg + strlen(arg) != num_end || num < 0 || num > 0xFFFFFF) {
		return -1;
	} else {
		options->color = num;
	}

	return 0;
}

/**
 * Parses a favorites id from a string.
 *
 * @param arg - a string containing a favorites id. The id must
 *     be an integer greater than 0.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_favorites_id(char *arg, struct options *options) {
	int num;
	char *num_end;

	num = strtol(arg, &num_end, 10);
	if (arg + strlen(arg) != num_end || num <= 0) {
		return -1;
	} else {
		options->favorites_id = num;
	}

	return 0;
}

/**
 * Parses the number of images from a string.
 *
 * @param arg - a string containing a number. The number must
 *   be greater than 0.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_image_number(char *arg, struct options *options) {
	int num;
	char *num_end;

	num = strtol(arg, &num_end, 10);
	if (arg + strlen(arg) != num_end || num <= 0) {
		return -1;
	} else {
		options->images = num;
	}

	return 0;
}

/**
 * Parses a resolution from a string.
 *
 * @param arg - a string containing a resolution.
 *   Format [=]<number>x<number>. The '=' is optional.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_resolution(char *arg, struct options *options) {
	int num;
	char *temp_arg, *num_end;

	temp_arg = arg;

	/* If starts with '=' search for the exact resolution */
	if (temp_arg[0] == '=') {
		options->res_opt = WB_RES_EXACTLY;
		temp_arg++;
	}

	/* Try to read the X resolution */
	num = strtol(temp_arg, &num_end, 10);
	if (num <= 0) {
		return -1;
	} else {
		options->res_x = num;
		temp_arg = num_end;
	}

	/* Check if there's an 'x' between the numbers */
	if (temp_arg[0] != 'x') {
		return -1;
	} else {
		temp_arg++;
	}

	/* Try to read the Y resolution */
	num = strtol(temp_arg, &num_end, 10);
	if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
		return -1;
	} else {
		options->res_y = num;
	}

	return 0;
}

/**
 * Parses the sort type an order from a string.
 *
 * @param arg - a string containing a sort type and an optional
 *   sort order.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_sort(char *arg, struct options *options) {
	int index;
	char *temp_arg;

	temp_arg = arg;

	/* Parse sort order if specified */
	if (temp_arg[0] == '+') {
		options->sort_order = WB_SORT_ASCENDING;
		temp_arg++;
	} else if (temp_arg[0] == '-') {
		options->sort_order = WB_SORT_DESCENDING;
		temp_arg++;
	}

	/* Check if specified sort type is in the short types array */
	index = find_in_array(temp_arg, WB_SORT_TYPES_SHORT, WB_SORT_TYPES_SIZE);
	if (index != -1) {
		options->sort_by = WB_SORT_TYPE_IDS[index];
		return 0;
	}

	/* Check if specified sort type is in the long types array */
	index = find_in_array(temp_arg, WB_SORT_TYPES_LONG, WB_SORT_TYPES_SIZE);
	if (index != -1) {
		options->sort_by = WB_SORT_TYPE_IDS[index];
		return 0;
	}

	return -1;
}

/**
 * Parses the sort toplist interval from a string.
 *
 * @param arg - a string containing a toplist interval.
 * @param options - a pointer to an options struct.
 * @return 0 on success, -1 otherwise.
 */
int
parse_toplist_interval(char *arg, struct options *options) {
	int index;

	/* Check if specified sort type is in the short types array */
	index = find_in_array(arg, WB_TOPLIST_INTERVALS, WB_TOPLIST_INTERVALS_SIZE);
	if (index != -1) {
		options->toplist = WB_TOPLIST_INTERVAL_IDS[index];
		return 0;
	}

	return -1;
}

/**
 * Parses one argp option.
 *
 * @param key - option key
 * @param arg - the argument of this option
 * @param options - a pointer to the options struct
 * @return 0 when the parsing should continue, -1 when the parsing
 *   should be stopped.
 */
int
parse_opt(int key, char *arg, struct options *options) {
	switch(key) {

		/* Options with arguments */

		case 'a': /* aspect ratio */
			if (parse_aspect_ratio(arg, options) == -1) {
				invalid_arg_error("aspect ratio", arg);
				return -1;
			}
			break;
		case 'c': /* color */
			if (parse_color(arg, options) == -1) {
				invalid_arg_error("color", arg);
				return -1;
			}
			break;
		case 'f': /* favorites id */
			if (parse_favorites_id(arg, options) == -1) {
				invalid_arg_error("favorites id", arg);
				return -1;
			}
			break;
		case 'n': /* number of images */
			if (parse_image_number(arg, options) == -1) {
				invalid_arg_error("number of images", arg);
				return -1;
			}
			break;
		case 'p': /* password */
			options->password = arg;
			break;
		case 'q': /* query string */
			options->query = arg;
			break;
		case 'r': /* resolution */
			if (parse_resolution(arg, options) == -1) {
				invalid_arg_error("resolution", arg);
				return -1;
			}
			break;
		case 's': /* sort */
			if (parse_sort(arg, options) == -1) {
				invalid_arg_error("sort type", arg);
				return -1;
			}
			break;
		case 't': /* toplist interval */
			if (parse_toplist_interval(arg, options) == -1) {
				invalid_arg_error("toplist interval", arg);
				return -1;
			}
			break;
		case 'u': /* username */
			options->username = arg;
			break;

		/* Options without arguments */

		case 'P':
			options->flags |= WB_FLAG_PROGRESS;
			break;
		case 'R':
			options->flags |= WB_FLAG_RANDOM;
			break;
		case 'S': /* SFW */
			options->purity |= WB_PURITY_SFW;
			break;
		case 'K': /* Sketchy */
			options->purity |= WB_PURITY_SKETCHY;
			break;
		case 'N': /* NSFW */
			options->purity |= WB_PURITY_NSFW;
			break;
		case 'G': /* Wallpapers / General board */
			options->boards |= WB_BOARD_GENERAL;
			break;
		case 'A': /* Anime / Manga board */
			options->boards |= WB_BOARD_ANIME;
			break;
		case 'H': /* High Resolution board */
			options->boards |= WB_BOARD_HIGHRES;
			break;

		/* Help, usage, errors */

		case 'h': /* help */
			print_full_help();
			return -1;
		case 'V': /* version */
			print_version();
			return -1;
		case WB_KEY_USAGE: /* usage */
			print_full_usage();
			return -1;
		case '?': /* getopt error */
			wb_error_no_prefix(FORMAT_SHORT_HELP, APP_INVOKE_NAME, APP_INVOKE_NAME);
			return -1;
		default:
			return -1;
	}

	return 0;
}

/**
 * Parses all command line options.
 *
 * @param argc - argument count
 * @param argv - array of arguments
 * @param options - the option structure
 *
 * On error DOES NOT RETURN, calls exit().
 */
void
wb_parse_args(int argc, char *argv[], struct options *options) {
	int key, option_index;

	/* Set app invoke name */
	APP_INVOKE_NAME = basename(argv[0]);

	/* Parse args */
	while ((key = getopt_long(argc, argv, GETOPT_SHORT_OPTIONS,
		GETOPT_LONG_OPTIONS, &option_index)) != -1) {

		if (parse_opt(key, optarg, options) != 0) {
			exit(1);
		}
	}
}
