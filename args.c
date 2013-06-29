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
#include <argp.h>

#include "args.h"
#include "types.h"

/**************************************************
 * Function declarations
 **************************************************/

static error_t parse_opt(int key, char *arg, struct argp_state *state);

/**************************************************
 * argp constants
 **************************************************/

const char *argp_program_version =
"wb, version 0.1\nCopyright (C) 2013 Mantas Norvaiša\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.";

const char *argp_program_bug_address = "<mntnorv+bugs@gmail.com>";

static char doc[] =
"wb -- A wallbase.cc image downloader";

static struct argp_option argp_options[] = {
	/* Options with arguments */
	{"username",     'u', "USERNAME", 0,
	"wallbase.cc username, required for NSFW content"},
	{"password",     'p', "PASSWORD", 0,
	"wallbase.cc password, required for NSFW content"},
	{"download-dir", 'd', "DIR",      0,
	"Directory to download images to (defaults to current directory)"},
	{"images",       'n', "COUNT",    0,
	"Number of images to download"},
	{"query",        'q', "STRING",   0,
	"Search for images related to this string"},
	{"toplist",      't', "INTERVAL", 0,
	"Get the top images in the specified time interval"},
	{"color",        'c', "COLOR",    0,
	"Search for images containing this color"},
	{"resolution",   'r', "RES",      0,
	"Search for images with at least or exactly this resolution"},
	{"aspect",       'a', "ASPECT",   0,
	"Search for images with this aspect ratio"},
	{"sort",         's', "SORT",     0,
	"Specify the sort order"},

	/* Options without arguments */
	{"sfw",      'S', 0, 0, "Search for SFW images"},
	{"sketchy",  'K', 0, 0, "Search for sketchy images"},
	{"nsfw",     'N', 0, 0, "Search for NSFW images (requires wallbase.cc login information)"},
	{"general",  'G', 0, 0, "Search in the Wallpapers / General board"},
	{"anime",    'A', 0, 0, "Search in the Anime / Manga board"},
	{"manga",     WB_KEY_MANGA, 0, OPTION_ALIAS},
	{"high-res", 'H', 0, 0, "Search in the High Resolution board"},

	/* Long-only options */
	{"print-only", WB_KEY_PRINT_ONLY, 0, 0,
	"Print image URLs to stdout (do not download images)"},
	{0}
};

static struct argp argp = {argp_options, parse_opt, NULL, doc};

/**************************************************
 * Function implementations
 **************************************************/

/**
 * Parses one argp option.
 *
 * @param key - option key
 * @param arg - the argument of this option
 * @param state - current argp state
 * @return 0 on success, an argp error code otherwise.
 */
static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
	struct options *options = state->input;
	int num;
	char *temp_arg, *num_end;

	switch(key) {
		case 'a': /* aspect ratio */
			temp_arg = arg;

			/* Try to read the first number (before ':') */
			num = strtol(temp_arg, &num_end, 10);
			if (num <= 0) {
				argp_error(state, "`%s' is not a valid aspect ratio.", arg);
			} else {
				options->aspect_ratio = num;
				temp_arg = num_end;
			}

			/* Check for a ':' between numbers */
			if (temp_arg[0] != ':') {
				argp_error(state, "`%s' is not a valid aspect ratio.", arg);
			} else {
				temp_arg++;
			}

			/* Try to read the second number */
			num = strtol(temp_arg, &num_end, 10);
			if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
				argp_error(state, "`%s' is not a valid aspect ratio.", arg);
			} else {
				options->aspect_ratio = options->aspect_ratio / num;
			}

			break;
		case 'c': /* color */
			num = strtol(arg, &num_end, 16);
			if (arg + strlen(arg) != num_end || num < 0 || num > 0xFFFFFF) {
				argp_error(state, "`%s' is not a valid color.", arg);
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
				argp_error(state, "`%s' is not a valid number of images.", arg);
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
				argp_error(state, "`%s' is not a valid resolution.", arg);
			} else {
				options->res_x = num;
				temp_arg = num_end;
			}

			/* Check if there's an 'x' between the numbers */
			if (temp_arg[0] != 'x') {
				argp_error(state, "`%s' is not a valid resolution.", arg);
			} else {
				temp_arg++;
			}

			/* Try to read the Y resolution */
			num = strtol(temp_arg, &num_end, 10);
			if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
				argp_error(state, "`%s' is not a valid resolution.", arg);
			} else {
				options->res_y = num;
			}

			break;
		case 'u': /* username */
			options->username = arg;
			break;
		case ARGP_KEY_ARG: /* non-option arguments */
			argp_usage(state);
			break;
		case ARGP_KEY_END:
			break;
		default:
			return ARGP_ERR_UNKNOWN;
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
	argp_parse(&argp, argc, argv, 0, 0, options);
}
