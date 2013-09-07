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
#include <ctype.h>

#include "url_enc.h"

 /**
 * Converts a number from 0 to 15 to hex.
 *
 * @param code - char (from 0 to 15) to convert to hex.
 * @return the number converted to hex as a char.
 */
char
to_hex(char code) {
	static char hex[] = "0123456789abcdef";
	return hex[code & 15];
}

/**
 * URL-encodes a string.
 *
 * @param str - string to URL-encode.
 * @return the URL-encoded string.
 * IMPORTANT: the returned string must be freed with free().
 */
char *
url_encode(const char *str) {
	const char *pstr = str;
	char *buf = malloc(strlen(str) * 3 + 1);
	char *pbuf = buf;
	while (*pstr) {
		if (isalnum((unsigned char)*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') {
			*pbuf++ = *pstr;
		} else if (*pstr == ' ') {
			*pbuf++ = '+';
		} else {
			*pbuf++ = '%';
			*pbuf++ = to_hex(*pstr >> 4);
			*pbuf++ = to_hex(*pstr & 15);
		}
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}
