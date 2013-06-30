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

#include <stdio.h>
#include <stdarg.h>
#include "error.h"

static const char *ERROR_PREFIX = "wb: ";

/**
 * Print a formatted error message.
 * Does not exit.
 *
 * @param format - the format string
 * @param args - format arguments
 */
void
wb_verror(const char *format, va_list args) {
	fprintf(stderr, "%s", ERROR_PREFIX);
	vfprintf(stderr, format, args);
}

/**
 * Print a formatted error message.
 * Does not exit.
 *
 * @param format - the format string
 * @param ... - format arguments
 */
void
wb_error(const char *format, ...) {
	va_list args;
	va_start(args, format);
	wb_verror(format, args);
	va_end(args);
}
