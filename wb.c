/*
 * wb.c - A wallbase.cc image downloader
 *
 * Copyright (C) 2013 Mantas Norvaiša
 *
 * This file is part of wb.c.
 * 
 * wb.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wb.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wb.c.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <argp.h>

#include <curl/curl.h>

#include <tidy.h>
#include <buffio.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/**************************************************
 * Defines
 **************************************************/

/* Search types */
#define WB_TYPE_SEARCH        1
#define WB_TYPE_TOPLIST       2
#define WB_TYPE_COLOR         3
#define WB_TYPE_RANDOM        4

/* Sort types */
#define WB_SORT_RELEVANCE     1
#define WB_SORT_VIEWS         2
#define WB_SORT_DATE          3
#define WB_SORT_FAVORITES     4

/* Sort orders */
#define WB_SORT_ASCENDING     0
#define WB_SORT_DESCENDING    1

/* Resolution options */
#define WB_RES_EXACTLY        0
#define WB_RES_AT_LEAST       1

/* Flags */
#define WB_FLAG_DONT_DOWNLOAD 0x01
#define WB_FLAG_LEAVE_OLD     0x02

/* wallbase.cc purities */
#define WB_PURITY_SFW         0x01
#define WB_PURITY_SKETCHY     0x02
#define WB_PURITY_NSFW        0x04
#define WB_PURITY_ALL         0x07

/* wallbase.cc wallpaper boards */
#define WB_BOARD_GENERAL      0x01
#define WB_BOARD_ANIME        0x02
#define WB_BOARD_HIGHRES      0x04
#define WB_BOARD_ALL          0x07

/**************************************************
 * Structs
 **************************************************/

struct curl_response {
	size_t size;
	char *data;
};

struct options {
	char *username, *password;
	unsigned char search_type;
	char *dir;
	char *query;
	int color;
	int images, images_per_page;
	unsigned char flags, purity, boards;
	int res_x, res_y;
	unsigned char res_opt;
	unsigned char sort_by, sort_order;
};

/**************************************************
 * Function declarations
 **************************************************/

struct curl_slist *wb_login(const char *username, const char *password);
struct curl_slist *wb_get_image_page_urls(const char *url, const char *post_data, struct curl_slist *cookies);
struct curl_slist *wb_get_image_urls(const char *url, const char *post_data, struct curl_slist *cookies);
char *wb_get_image_url(const char *url, struct curl_slist *cookies);

static error_t parse_opt(int key, char *arg, struct argp_state *state);

char *curl_get_response(const char *url, const char *post_data, struct curl_slist **cookies, int update_cookies);
int curl_connect(const char *url, const char *post_data, struct curl_slist **cookies, int update_cookies);
xmlDocPtr curl_get_response_as_xml(const char *url, const char *post_data, struct curl_slist **cookies, int update_cookies);
void curl_add_cookies(CURL *curl, struct curl_slist *cookies);

char *tidy_convert_to_xml(const char *html);

xmlXPathObjectPtr eval_xpath_expr(xmlDocPtr xml_doc, const xmlChar *expression);

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data);
char *url_encode(const char *str);
char to_hex(char code);

void b64_decodeblock(unsigned char in[], char *clrstr);
char *b64_decode(char *src);

/**************************************************
 * argp global constants
 **************************************************/

const char *argp_program_version =
"wb.c, version 0.1\nCopyrght (C) 2013 Mantas Norvaiša\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.";

const char *argp_program_bug_address = "<mntnorv+bugs@gmail.com>";

/*static char args_doc[] = "";*/
static char doc[] =
"wb -- A wallbase.cc image downloader";

static struct argp_option argp_options[] = {
	{"username", 'u', "USERNAME", 0, "wallbase.cc username, required for NSFW content"},
	{"password", 'p', "PASSWORD", 0, "wallbase.cc password, required for NSFW content"},
	{0}
};

static struct argp argp = {argp_options, parse_opt, NULL, doc};

/**************************************************
 * General global constants
 **************************************************/

static const char *URL_LOGIN = "http://wallbase.cc/user/login";
static const char *URL_TOPLIST = "http://wallbase.cc/toplist";

static const char *FORMAT_LOGIN = "usrname=%s&pass=%s&nopass_email=Type+in+your+e-mail+and+press+enter&nopass=0&1=1";

static const char *XHTML_PREFIX = "xhtml";
static const char *XHTML_HREF = "http://www.w3.org/1999/xhtml";
static const char *XPATH_IMAGE_PAGE_URL = "//xhtml:div[contains(@class,'thumb')]/xhtml:a[@class='thdraggable thlink']";
static const char *XPATH_IMAGE_URL = "//xhtml:div[@id='bigwall']/xhtml:script";

static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**************************************************
 * Main
 **************************************************/

int
main(int argc, char* argv[]) {
	/* Variables */
	struct curl_slist *cookies = NULL;
	struct curl_slist *image_urls = NULL;
	struct curl_slist *img_url;
	struct options options;

	/* Set default options */
	options.username = "";
	options.password = "";
	options.dir = ".";
	options.images = 20;
	options.images_per_page = 20;
	options.flags = 0;
	options.purity = WB_PURITY_ALL;
	options.boards = WB_BOARD_ALL;
	options.res_opt = WB_RES_AT_LEAST;
	options.sort_by = WB_SORT_RELEVANCE;
	options.sort_order = WB_SORT_DESCENDING;

	/* Parse arguments */
	argp_parse(&argp, argc, argv, 0, 0, &options);

	/* Init */
	curl_global_init(CURL_GLOBAL_ALL);
	xmlInitParser();

	/* Main operation */
	cookies = wb_login(options.username, options.password);
	if (cookies == NULL) {
		curl_global_cleanup();
		xmlCleanupParser();
		return 1;
	}

	image_urls = wb_get_image_urls(URL_TOPLIST, NULL, cookies);
	if (image_urls == NULL) {
		curl_slist_free_all(cookies);
		curl_global_cleanup();
		xmlCleanupParser();
		return 1;
	}

	img_url = image_urls;
	while (img_url != NULL) {
		printf("%s\n", img_url->data);
		img_url = img_url->next;
	}

	/* Cleanup nd return */
	curl_slist_free_all(cookies);
	curl_slist_free_all(image_urls);
	curl_global_cleanup();
	xmlCleanupParser();
	return 0;
}

/**************************************************
 * wallbase-specific function implementations
 **************************************************/

/**
 * wb_login:
 * @username - wallbase.cc username
 * @password - wallbase.cc password
 *
 * Login to wallbase.cc, by setting your specified cookies.
 * IMPORTANT: The resulting list of cookies must be freed with
 * curl_slist_free_all().
 *
 * Returns a curl_slist of cookies with the login session info.
 */
struct curl_slist *
wb_login(const char *username, const char *password) {
	char *enc_username;
	char *enc_password;
	char post_data[256];
	char *response;

	struct curl_slist *cookies = NULL;

	/* URL-encode username and password and insert into POST data */
	enc_username = url_encode(username);
	enc_password = url_encode(password);
	sprintf(post_data, FORMAT_LOGIN, enc_username, enc_password);
	free(enc_username);
	free(enc_password);

	/* Login */
	response = curl_get_response(URL_LOGIN, post_data, &cookies, 1);
	if (response == NULL) {
		fprintf(stderr, "Error: curl_get_response() failed\n");
		return NULL;
	}

	if (strlen(response) > 0) {
		fprintf(stderr, "Error: unable to login to wallbase.cc\n");
		free(response);
		curl_slist_free_all(cookies);
		return NULL;
	}

	free(response);

	return cookies;
}

/**
 * Connects to wallbase.cc with the specified post data and
 * cookies and retrieves image page urls.
 *
 * @param url - wallbase.cc url to get images from.
 * @param post_data - post data required for search parameters.
 * @param cookies - cookies with login session information.
 * @return a curl_slist of image page urls on success, NULL
 *   otherwise. IMPORTANT: the returned list must be freed with
 *   curl_slist_free_all().
 */
struct curl_slist *
wb_get_image_page_urls(const char *url, const char *post_data,
	struct curl_slist *cookies) {

	struct curl_slist *urls = NULL;
	int i, result_node_count;

	xmlDocPtr xml_doc;
	xmlXPathObjectPtr urls_xpath_object;
	xmlNodeSetPtr result_nodes;
	xmlNodePtr current_node;
	xmlChar *current_img_page;

	/* Get response as XML */
	xml_doc = curl_get_response_as_xml(url, post_data, &cookies, 0);
	if (xml_doc == NULL) {
		return NULL;
	}

	/* Get image url nodes from the XML by evaluating an XPath expression */
	urls_xpath_object = eval_xpath_expr(xml_doc, BAD_CAST XPATH_IMAGE_PAGE_URL);
	if (urls_xpath_object == NULL) {
		return NULL;
	}

	/* Add results to a list */
	result_nodes = urls_xpath_object->nodesetval;
	result_node_count = (result_nodes) ? result_nodes->nodeNr : 0;

	for (i = 0; i < result_node_count; i++) {
		current_node = result_nodes->nodeTab[i];
		if(current_node->type == XML_ELEMENT_NODE) {
			current_img_page = xmlGetProp(current_node, BAD_CAST "href");
			urls = curl_slist_append(urls, (char *)current_img_page);
			xmlFree(current_img_page);
		}
	}

	/* Clean up */
	xmlXPathFreeObject(urls_xpath_object);
	xmlFreeDoc(xml_doc);

	return urls;
}

/**
 * Connects to wallbase.cc with the specified post data and
 * cookies and retrieves image urls.
 *
 * @param url - wallbase.cc url to get images from.
 * @param post_data - post data required for search parameters.
 * @param cookies - cookies with login session information.
 * @return a curl_slist of image urls on success, NULL
 *   otherwise. IMPORTANT: the returned list must be freed with
 *   curl_slist_free_all().
 */
struct curl_slist *
wb_get_image_urls(const char *url, const char *post_data,
	struct curl_slist *cookies) {

	struct curl_slist *img_urls = NULL;
	struct curl_slist *img_page_urls;
	struct curl_slist *img_page_url;
	char *img_url;

	/* Get image page URLs */
	img_page_urls = wb_get_image_page_urls(url, post_data, cookies);

	/* Get an image URL from every image page URL */
	img_page_url = img_page_urls;
	while (img_page_url != NULL) {
		img_url = wb_get_image_url(img_page_url->data, cookies);
		if (img_url != NULL) {
			img_urls = curl_slist_append(img_urls, img_url);
			free(img_url);
		}

		img_page_url = img_page_url->next;
	}

	/* Cleanup */
	curl_slist_free_all(img_page_urls);

	return img_urls;
}

/**
 * Get the full image url from a wallbase.cc image page url.
 *
 * @param url - wallbase.cc image page url.
 * @param cookies - cookie list needed for NSFW images.
 * @return the URL of the image on success, NULL otherwise.
 *   IMPORTANT: the resulting string must be freed eith free().
 */
char *
wb_get_image_url(const char *url, struct curl_slist *cookies) {
	char *img_url = NULL;
	char *encoded_url = NULL;

	xmlDocPtr xml_doc;
	xmlXPathObjectPtr img_xpath_object;
	xmlNodeSetPtr result_nodes;
	xmlChar *result_str;

	int result_node_count;
	int encoded_length = 0;
	char *encoded_start, *encoded_end;

	/* Get response as XML */
	xml_doc = curl_get_response_as_xml(url, NULL, &cookies, 0);
	if (xml_doc == NULL) {
		return NULL;
	}

	/* Get the encoded image url */
	img_xpath_object = eval_xpath_expr(xml_doc, BAD_CAST XPATH_IMAGE_URL);
	if (img_xpath_object == NULL) {
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	/* Get nodes from the result object */
	result_nodes = img_xpath_object->nodesetval;
	result_node_count = (result_nodes) ? result_nodes->nodeNr : 0;
	if (result_node_count != 1) {
		/* Not really an error, 99% of the time this is the fault of wallbase.cc */
		/* fprintf(stderr, "Error: failed fetching encoded image url\n"); */
		xmlXPathFreeObject(img_xpath_object);
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	result_str = xmlNodeListGetString(xml_doc, result_nodes->nodeTab[0]->xmlChildrenNode, 1);
	
	/* Extract encoded URL from the result node */
	encoded_url = (char *)malloc(256);
	encoded_start = strstr((char *)result_str, "B('") + 3;
	encoded_end = strstr((char *)result_str, "')");
	encoded_length = encoded_end - encoded_start;
	strncpy(encoded_url, encoded_start, encoded_length);
	encoded_url[encoded_length] = '\0';
	xmlFree(result_str);

	/* Decode URL*/
	img_url = b64_decode(encoded_url);
	free(encoded_url);

	/* Clean up */
	xmlXPathFreeObject(img_xpath_object);
	xmlFreeDoc(xml_doc);

	return img_url;
}

/**************************************************
 * Helper function implementations
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

	switch(key) {
		case 'p':
			options->password = arg;
			break;
		case 'u':
			options->username = arg;
			break;
		case ARGP_KEY_ARG:
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
 * Connects to URL with a GET or POST request and returns
 * the response.
 *
 * @param url - the URL to connect to.
 * @param post_data (optional) - the post data as a string.
 *   If specified, a POST request is made. If post is not
 *   needed, pass NULL here and a GET request will be made.
 * @param cookies (optional) - the cookies to use for this
 *   request.
 * @param update_cookies - 1 if you need the cookies to be
 *   updated, 0 to leave the cookies as they were.
 * @return the response as a string on success, NULL otherwise.
 *   IMPORTANT: the returned string should be freed with free().
 */
char *
curl_get_response(const char *url, const char *post_data,
	struct curl_slist **cookies, int update_cookies) {

	CURL *curl;
	CURLcode res;

	/* Set up struct for CURL response */
	struct curl_response response;
	response.size = 0;
	response.data = malloc(4096);
	if (response.data == NULL) {
		return NULL;
	}
	response.data[0] = '\0';

	/* Set up CURL */
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	if (update_cookies) {
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	}

	if (post_data != NULL) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
	}

	if (cookies != NULL) {
		curl_add_cookies(curl, *cookies);
	}

	/* Perform CURL transaction */
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		curl_easy_cleanup(curl);
		return NULL;
	}

	/* Update cookies if needed */
	if (update_cookies) {
		if (cookies != NULL) {
			curl_slist_free_all(*cookies);
		}

		res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, cookies);
		if (res != CURLE_OK) {
			curl_easy_cleanup(curl);
			return NULL;
		}
	}

	/* Cleanup */
	curl_easy_cleanup(curl);
	return response.data;
}

/**
 * A wrapper for curl_get_response(). Should be used when the
 * response is not needed.
 *
 * @return 0 on success, -1 otherwise.
 *
 * @see curl_get_response()
 */
int
curl_connect(const char *url, const char *post_data,
	struct curl_slist **cookies, int update_cookies) {

	char *response;

	response = curl_get_response(url, post_data, cookies, update_cookies);
	if (response == NULL) {
		return -1;
	}

	free(response);
	return 0;
}

/**
 * A wrapper for curl_get_response() that converts the
 * response to XML.
 *
 * @return an XML document pointer on success, NULL otherwise.
 *   IMPORTANT: the returned document pointer must be freed
 *   using xmlFreeDoc().
 *
 * @see curl_get_response()
 */
xmlDocPtr
curl_get_response_as_xml(const char *url, const char *post_data,
	struct curl_slist **cookies, int update_cookies) {

	char *html_data;
	char *xml_data;

	xmlDocPtr xml_doc;

	/* Get HTML */
	html_data = curl_get_response(url, post_data, cookies, update_cookies);
	if (html_data == NULL) {
		fprintf(stderr, "Error: curl_get_response() failed\n");
		return NULL;
	}

	/* Convert HTML to XML */
	xml_data = tidy_convert_to_xml(html_data);
	free(html_data);
	if (xml_data == NULL) {
		fprintf(stderr, "Error: unable to convert HTML to XML\n");
		return NULL;
	}

	/* Create an XML document */
	xml_doc = xmlParseDoc(BAD_CAST xml_data);
	free(xml_data);
	if (xml_doc == NULL) {
		fprintf(stderr, "Error: unable to parse XML\n");
		return NULL;
	}

	return xml_doc;
}

/**
 * Adds all cookies from a curl_slist to a CURL structure.
 *
 * @param curl - the CURL structure to add cookies to.
 * @param cookies - a curl_slist containing the cookies to
 *   be added.
 */
void
curl_add_cookies(CURL *curl, struct curl_slist *cookies) {
	struct curl_slist *cookie = cookies;
	while (cookie != NULL) {
		curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie->data);
		cookie = cookie->next;
	}
}

/**
 * Converts HTML to XML using libTidy.
 *
 * @param html - the HTML you want to convert to XML.
 * @return a string containing the converted XML on success,
 *   NULL otherwise. IMPORTANT: the resulting string must be
 *   freed using free().
 */
char *
tidy_convert_to_xml(const char *html) {
	TidyDoc document;
	TidyBuffer doc_buffer = {0};
	TidyBuffer tidy_err_buffer = {0};
	TidyBuffer output_buffer = {0};
	int res;
	char *xml;

	/* Set up the tidy parser */
	document = tidyCreate();
	tidyOptSetBool(document, TidyForceOutput, yes);
	tidyOptSetBool(document, TidyXmlOut, yes);
	tidyOptSetBool(document, TidyNumEntities, yes);
	tidyOptSetInt(document, TidyWrapLen, 4096);
	tidyOptSetInt(document, TidyDoctypeMode, TidyDoctypeOmit);
	tidySetErrorBuffer(document, &tidy_err_buffer);
	tidyBufInit(&doc_buffer);

	tidyBufAppend(&doc_buffer, (void *) html, strlen(html));

	/* Parse HTML, repair it, and convert to XML */
	res = tidyParseBuffer(document, &doc_buffer);
	if (res >= 0) {
		res = tidyCleanAndRepair(document);
		if (res >= 0) {
			res = tidySaveBuffer(document, &output_buffer);
			if (res >= 0) {
				xml = (char *) malloc(output_buffer.size + 1);
				memcpy(xml, output_buffer.bp, output_buffer.size);
				xml[output_buffer.size] = '\0';
			}
			tidyBufFree(&output_buffer);
		}
	}

	/* Check for errors */
	if (res < 0) {
		tidyBufFree(&doc_buffer);
		tidyBufFree(&tidy_err_buffer);
		tidyRelease(document);
		free(xml);
		return NULL;
	}

	/* Clean up */
	tidyBufFree(&doc_buffer);
	tidyBufFree(&tidy_err_buffer);
	tidyRelease(document);

	return xml;
}

/**
 * Evaluates an XPath expression on the given XML file.
 *
 * @param xml_doc - the XML document pointer.
 * @param expression - the expressions to evaluate.
 * @return an xmlXPathObjectPtr with the results on success, NULL
 *   otherwise. IMPORTANT: the returned object must be freed with
 *   xmlXPathFreeObject().
 */
xmlXPathObjectPtr
eval_xpath_expr(xmlDocPtr xml_doc, const xmlChar *expression) {
	xmlXPathContextPtr xpath_context;
	xmlXPathObjectPtr xpath_object;

	/* Create XPath context */
	xpath_context = xmlXPathNewContext(xml_doc);
	if (xpath_context == NULL) {
		fprintf(stderr, "Error: unable to create XPath context\n");
		return NULL;
	}

	/* Add XML namespace for XHTML */
	if (xmlXPathRegisterNs(xpath_context, BAD_CAST XHTML_PREFIX, BAD_CAST XHTML_HREF) != 0) {
		fprintf(stderr, "Error: unable to register XML namespace\n");
		xmlXPathFreeContext(xpath_context);
		return NULL;
	}

	/* Evaluate XPath expression */
	xpath_object = xmlXPathEvalExpression(expression, xpath_context);
	if (xpath_object == NULL) {
		fprintf(stderr, "Error: unable to evaluate XPath expression\n");
		xmlXPathFreeContext(xpath_context);
		return NULL;
	}

	/* Clean up */
	xmlXPathFreeContext(xpath_context);

	return xpath_object;
}

/**
 * Writes CURL response to a curl_response structure.
 *
 * @param ptr - CURL response data pointer.
 * @param size - size of the data to write in units of nmemb.
 * @param nmemb - multiplier of size.
 * @param data - the structure to write data to.
 * @return the size of data written in bytes.
 */
size_t
write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data) {
	size_t index = data->size;
	size_t n = (size * nmemb);
	char* tmp;

	data->size += (size * nmemb);

#ifdef DEBUG
	fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif

	tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

	if(tmp) {
		data->data = tmp;
	} else {
		if(data->data) {
			free(data->data);
		}
		fprintf(stderr, "Failed to allocate memory.\n");
		return 0;
	}

	memcpy((data->data + index), ptr, n);
	data->data[data->size] = '\0';

	return size * nmemb;
}

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
	strncat(clrstr, (char *)out, sizeof(out));
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
