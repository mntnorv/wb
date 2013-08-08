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

#include <errno.h>
#include <tidy.h>
#include <buffio.h>

#include "net.h"
#include "types.h"
#include "xml.h"

/**
 * Converts HTML to XML using libTidy.
 *
 * @param html - the HTML you want to convert to XML.
 * @return a string containing the converted XML on success,
 *   NULL otherwise. IMPORTANT: the resulting string must be
 *   freed using free().
 */
char *
convert_html_to_xml(const char *html) {
	TidyDoc document;
	int res;
	unsigned int xml_buffer_size;
	char *xml;

	/* Set up the tidy parser */
	document = tidyCreate();
	tidyOptSetBool(document, TidyMark, no);
	tidyOptSetBool(document, TidyForceOutput, yes);
	tidyOptSetBool(document, TidyXmlOut, yes);
	tidyOptSetBool(document, TidyNumEntities, yes);
	tidyOptSetInt(document, TidyWrapLen, 4096);
	tidyOptSetInt(document, TidyShowErrors, 0);
	tidyOptSetInt(document, TidyDoctypeMode, TidyDoctypeOmit);

	/* Parse HTML, repair it, and convert to XML */
	res = tidyParseString(document, html);
	if (res >= 0) {
		res = tidyCleanAndRepair(document);
	}

	if (res >= 0) {
		xml_buffer_size = 0;
		xml = (char *) malloc(1);

		while ((res = tidySaveString(document, xml, &xml_buffer_size)) == -ENOMEM) {
			xml = realloc(xml, xml_buffer_size + 1);
		}

		xml[xml_buffer_size] = '\0';
	}

	/* Check for errors */
	if (res < 0) {
		tidyRelease(document);
		free(xml);
		return NULL;
	}

	/* Clean up */
	tidyRelease(document);

	return xml;
}

/**
 * A wrapper for net_get_response() that converts the
 * response to XML.
 *
 * @return an XML document pointer on success, NULL otherwise.
 *   IMPORTANT: the returned document pointer must be freed
 *   using xmlFreeDoc().
 *
 * @see net_get_response()
 */
char *
net_get_response_as_xml(const char *url, const char *post_data,
	struct wb_str_list **cookies, int update_cookies) {

	char *html_data;
	char *xml_data;

	/* Get HTML */
	html_data = net_get_response(url, post_data, cookies, update_cookies);
	if (html_data == NULL) {
		fprintf(stderr, "Error: net_get_response() failed\n");
		return NULL;
	}

	/* Convert HTML to XML */
	xml_data = convert_html_to_xml(html_data);
	free(html_data);
	if (xml_data == NULL) {
		fprintf(stderr, "Error: unable to convert HTML to XML\n");
		return NULL;
	}

	return xml_data;
}
