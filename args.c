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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>

#include "args.h"
#include "error.h"
#include "types.h"

/**************************************************
 * Constants
 **************************************************/

const char ABOUT[] = "wb -- A wallbase.cc image downloader";
const char *BUG_ADDRESS = "<mntnorv+bugs@gmail.com>";

const char *SHORT_USAGE = "Usage: wb [OPTION...]";
const char *LONG_USAGE = "\
Usage: wb [-AGHKNShV] [-a ASPECT] [-c COLOR] [-d DIR] [-n COUNT] [-p PASSWORD]\n\
            [-q STRING] [-r RES] [-s SORT] [-t INTERVAL] [-u USERNAME]";

const char *SHORT_HELP = "Try `wb --help' or `wb --usage' for more information.";
const char *LONG_HELP = "\
  -a, --aspect=ASPECT        Search for images with this aspect ratio\n\
  -A, --anime, --manga       Search in the Anime / Manga board\n\
  -c, --color=COLOR          Search for images containing this color\n\
  -d, --download-dir=DIR     Directory to download images to (defaults to\n\
                             current directory)\n\
  -G, --general              Search in the Wallpapers / General board\n\
  -H, --high-res             Search in the High Resolution board\n\
  -K, --sketchy              Search for sketchy images\n\
  -n, --images=COUNT         Number of images to download\n\
  -N, --nsfw                 Search for NSFW images (requires wallbase.cc login\n\
                             information)\n\
  -p, --password=PASSWORD    wallbase.cc password, required for NSFW content\n\
      --print-only           Print image URLs to stdout (do not download\n\
                             images)\n\
  -q, --query=STRING         Search for images related to this string\n\
  -r, --resolution=RES       Search for images with at least or exactly this\n\
                             resolution\n\
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

const char *FORMAT_VERSION = "\
wb, version %s\nCopyright (C) 2013 Mantas Norvaiša\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n";

const char *FORMAT_FULL_HELP = "%s\n%s\n\n%s\n\nReport bugs to %s\n";

static const char *GETOPT_SHORT_OPTIONS = "a:c:d:n:p:q:r:s:t:u:AGHKNShV";
static struct option GETOPT_LONG_OPTIONS[] = {
	/* Options with arguments */
	{"aspect",       required_argument, 0, 'a'},
	{"color",        required_argument, 0, 'c'},
	{"download-dir", required_argument, 0, 'd'},
	{"images",       required_argument, 0, 'n'},
	{"password",     required_argument, 0, 'p'},
	{"query",        required_argument, 0, 'q'},
	{"resolution",   required_argument, 0, 'r'},
	{"sort",         required_argument, 0, 's'},
	{"toplist",      required_argument, 0, 't'},
	{"username",     required_argument, 0, 'u'},

	/* Options without arguments */
	{"anime",        no_argument,       0, 'A'},
	{"manga",        no_argument,       0, 'A'},
	{"general",      no_argument,       0, 'G'},
	{"high-res",     no_argument,       0, 'H'},
	{"sketchy",      no_argument,       0, 'K'},
	{"nsfw",         no_argument,       0, 'N'},
	{"sfw",          no_argument,       0, 'S'},
	{"help",         no_argument,       0, 'h'},
	{"version",      no_argument,       0, 'V'},

	/* Long-only options */
	{"usage",        no_argument,       0, WB_KEY_USAGE},
	{"print-only",   no_argument,       0, WB_KEY_PRINT_ONLY},
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
	wb_error("invalid %s -- '%s'\n%s\n", name, arg, SHORT_HELP);
}

/**
 * Prints the full help.
 */
void
print_full_help() {
	printf(FORMAT_FULL_HELP, SHORT_USAGE, ABOUT, LONG_HELP, BUG_ADDRESS);
}

/**
 * Prints the full usage info.
 */
void
print_full_usage() {
	printf("%s\n", LONG_USAGE);
}

/**
 * Prints version info.
 */
void
print_version() {
	printf(FORMAT_VERSION, VERSION);
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
	int num;
	char *temp_arg, *num_end;

	switch(key) {
		case 'a': /* aspect ratio */
			temp_arg = arg;

			/* Try to read the first number (before ':') */
			num = strtol(temp_arg, &num_end, 10);
			if (num <= 0) {
				invalid_arg_error("aspect ratio", arg);
				return -1;
			} else {
				options->aspect_ratio = num;
				temp_arg = num_end;
			}

			/* Check for a ':' between numbers */
			if (temp_arg[0] != ':') {
				invalid_arg_error("aspect ratio", arg);
				return -1;
			} else {
				temp_arg++;
			}

			/* Try to read the second number */
			num = strtol(temp_arg, &num_end, 10);
			if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
				invalid_arg_error("aspect ratio", arg);
				return -1;
			} else {
				options->aspect_ratio = options->aspect_ratio / num;
			}

			break;
		case 'c': /* color */
			num = strtol(arg, &num_end, 16);
			if (arg + strlen(arg) != num_end || num < 0 || num > 0xFFFFFF) {
				invalid_arg_error("color", arg);
				return -1;
			} else {
				options->color = num;
			}
			break;
		case 'd': /* download dir */
			options->dir = arg;
			break;
		case 'n': /* number of images */
			num = strtol(arg, &num_end, 10);
			if (arg + strlen(arg) != num_end || num <= 0) {
				invalid_arg_error("number of images", arg);
				return -1;
			} else {
				options->images = num;
			}
			break;
		case 'p': /* password */
			options->password = arg;
			break;
		case 'q': /* query string */
			options->query = arg;
			break;
		case 'r': /* resolution */
			temp_arg = arg;

			/* If starts with '=' search for the exact resolution */
			if (temp_arg[0] == '=') {
				options->res_opt = WB_RES_EXACTLY;
				temp_arg++;
			}

			/* Try to read the X resolution */
			num = strtol(temp_arg, &num_end, 10);
			if (num <= 0) {
				invalid_arg_error("resolution", arg);
				return -1;
			} else {
				options->res_x = num;
				temp_arg = num_end;
			}

			/* Check if there's an 'x' between the numbers */
			if (temp_arg[0] != 'x') {
				invalid_arg_error("resolution", arg);
				return -1;
			} else {
				temp_arg++;
			}

			/* Try to read the Y resolution */
			num = strtol(temp_arg, &num_end, 10);
			if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
				invalid_arg_error("resolution", arg);
				return -1;
			} else {
				options->res_y = num;
			}

			break;
		case 'u': /* username */
			options->username = arg;
			break;
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
			fprintf(stderr, "%s\n", SHORT_HELP);
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
	
	while ((key = getopt_long(argc, argv, GETOPT_SHORT_OPTIONS,
		GETOPT_LONG_OPTIONS, &option_index)) != -1) {

		if (parse_opt(key, optarg, options) != 0) {
			exit(1);
		}
	}
}
