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
#include "base64.h"

static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * Decodes four 6-bit chars into 3 bytes. Appends the result
 * to the specified string.
 *
 * @param in - the input chars.
 * @param clrstr - the result string.
 */
void
b64_decodeblock(unsigned char in[], char *clrstr) {
	unsigned char out[4];
	out[0] = in[0] << 2 | in[1] >> 4;
	out[1] = in[1] << 4 | in[2] >> 2;
	out[2] = in[2] << 6 | in[3] >> 0;
	out[3] = '\0';
	strncat(clrstr, (char *)out, 4);
}

/**
 * Decodes a base64-encoded string.
 *
 * @param src - the base64-encoded string.
 * @return decoded data as a char array. IMPORTANT: the
 *   returned array must be freed using free().
 */
char *
b64_decode(char *src) {
	int c, phase, i, dst_len;
	unsigned char in[4];
	char *p, *dst;

	dst_len = (strlen(src) / 4) * 3;
	dst = (char *)malloc(dst_len + 1);
	dst[0] = '\0';
	dst[dst_len] = '\0';

	phase = 0;
	i = 0;
	while(src[i]) {
		c = (int) src[i];
		if(c == '=') {
			b64_decodeblock(in, dst); 
			break;
		}
		p = strchr(BASE64, c);
		if(p) {
			in[phase] = p - BASE64;
			phase = (phase + 1) % 4;
			if(phase == 0) {
				b64_decodeblock(in, dst);
				in[0]=in[1]=in[2]=in[3]=0;
			}
		}
		i++;
	}

	return dst;
}
