#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <curl/curl.h>

#include <tidy/tidy.h>
#include <tidy/buffio.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/*
 * Global constants
 */

static const char *URL_LOGIN = "http://wallbase.cc/user/login";
static const char *URL_TOPLIST = "http://wallbase.cc/toplist";

static const char *FORMAT_LOGIN = "usrname=%s&pass=%s&nopass_email=Type+in+your+e-mail+and+press+enter&nopass=0&1=1";

static const char *XHTML_PREFIX = "xhtml";
static const char *XHTML_HREF = "http://www.w3.org/1999/xhtml";
static const char *XPATH_IMAGE_PAGE_URL = "//xhtml:div[@class='thumb']/xhtml:a[@class='thdraggable thlink']";

/*
 * Structs
 */

struct curl_response {
	size_t size;
	char *data;
};

/*
 * Function declarations
 */

struct curl_slist *wb_login(char *username, char *password);

char *curl_get_response(const char *url, char *post_data, struct curl_slist **cookies, int update_cookies);
int curl_connect(const char *url, char *post_data, struct curl_slist **cookies, int update_cookies);
void curl_add_cookies(CURL *curl, struct curl_slist *cookies);

char *tidy_convert_to_xml(char *html);

xmlXPathObjectPtr eval_xpath_expr(xmlChar *xml_data, xmlChar *expression);

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data);
char *url_encode(char *str);
char to_hex(char code);

void
print_xpath_nodes(xmlNodeSetPtr nodes);

/*
 * Main
 */

int main(int argc, char* argv[]) {
	/* Variables */
	struct curl_slist *cookies = NULL;
	char *toplist;
	char *toplist_xml;
	xmlXPathObjectPtr urls_xpath_object;

	/* Init */
	curl_global_init(CURL_GLOBAL_ALL);
	xmlInitParser();

	/* Main operation */
	puts("Logging in...");
	cookies = wb_login("", "");
	if (cookies == NULL) {
		return 1;
	}

	puts("Getting HTML...");
	toplist = curl_get_response(URL_TOPLIST, NULL, &cookies, 0);
	if (toplist == NULL) {
		fprintf(stderr, "Error: curl_get_response() failed\n");
		return 1;
	}

	puts("Converting to XML...");
	toplist_xml = tidy_convert_to_xml(toplist);
	free(toplist);
	if (toplist_xml == NULL) {
		fprintf(stderr, "Error: unable to convert HTML to XML\n");
		return 1;
	}

	puts("Parsing XML...");
	urls_xpath_object = eval_xpath_expr(BAD_CAST toplist_xml, BAD_CAST XPATH_IMAGE_PAGE_URL);
	free(toplist_xml);
	if (urls_xpath_object == NULL) {
		fprintf(stderr, "Error: unable to parse XML\n");
		return 1;
	}

	xmlXPathFreeObject(urls_xpath_object);

	/* Cleanup nd return */
	puts("Cleaning up...");
	curl_slist_free_all(cookies);
	curl_global_cleanup();
	xmlCleanupParser();
	return 0;
}

/*
 * wallbase.cc function implementations
 */

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
 * If an error occurs returns NULL.
 */
struct curl_slist *wb_login(char *username, char *password) {
	char *enc_username;
	char *enc_password;
	char post_data[256];
	char *response;

	struct curl_slist *cookies = NULL;

	/* URL-encode username and password and insert into POST data */
	enc_username = url_encode(username);
	enc_password = url_encode(password);
	sprintf(post_data, FORMAT_LOGIN, enc_username, enc_password);

	/* Login */
	response = curl_get_response(URL_LOGIN, post_data, &cookies, 1);
	if (response == NULL) {
		fprintf(stderr, "Error: curl_get_response() failed\n");
		return NULL;
	}

	if (strlen(response) > 0) {
		fprintf(stderr, "Error: unable to login to wallbase.cc\n");
		free(response);
		return NULL;
	}
	free(response);

	return cookies;
}

/*
 * Helper function implementations
 */

/**
 * curl_get_response:
 * @url:                         URL to connect to
 * @post_data: (optional)        the post data as a string. If specified,
 *                               a POST request is made. If post is not
 *                               needed, pass NULL here and a GET request
 *                               will be made.
 * @cookies: (optional)          the cookies to use for this request.
 * @update_cookies:              1 if you need the cookies to be updated
 *                               0 to leave the cookies as they were
 *
 * Connects to URL with a GET or POST request and returns the response.
 * IMPORTANT: the returned string should be freed with free().
 * 
 * Returns the response as a string. If an error occurs, returns NULL.
 */
char *curl_get_response(const char *url, char *post_data, struct curl_slist **cookies, int update_cookies) {
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
 * curl_connect:
 *
 * A wrapper for curl_get_response. Should be used when the
 * response is not needed.
 * For argument descriptions see curl_get_response().
 *
 * Returns 0 on success, -1 otherwise.
 */
int curl_connect(const char *url, char *post_data, struct curl_slist **cookies, int update_cookies) {
	char *response;

	response = curl_get_response(url, post_data, cookies, update_cookies);
	if (response == NULL) {
		return -1;
	}

	free(response);
	return 0;
}

/**
 * curl_add_cookies:
 * @curl - the CURL structure to add cookies to
 * @cookies - a curl_slist containing the cookies to be added
 *
 * Adds all cookies from a curl_slist to a CURL structure.
 */
void curl_add_cookies(CURL *curl, struct curl_slist *cookies) {
	struct curl_slist *cookie = cookies;
	while (cookie != NULL) {
		curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie->data);
		cookie = cookie->next;
	}
}

/**
 * tidy_convert_to_xml:
 * @html - the HTML you want to convert to XML
 * 
 * Converts HTML to XML using libTidy.
 * IMPORTANT: the resulting string must be freed using free().
 * 
 * Returns a string containing the converted XML. If an error occurs
 * returns NULL.
 */
char *tidy_convert_to_xml(char *html) {
	TidyDoc document;
	TidyBuffer doc_buffer = {0};
	TidyBuffer tidy_err_buffer = {0};
	int res;

	/* Intentionaly left 0 to get the required buffer size. */
	unsigned int buffer_size = 0;
	char *xml = (char *) malloc(1);

	/* Set up the tidy parser */
	document = tidyCreate();
	tidyOptSetBool(document, TidyForceOutput, yes);
	tidyOptSetBool(document, TidyXmlOut, yes);
	tidyOptSetBool(document, TidyNumEntities, yes);
	tidyOptSetInt(document, TidyWrapLen, 4096);
	tidyOptSetInt(document, TidyDoctypeMode, TidyDoctypeOmit);
	tidySetErrorBuffer(document, &tidy_err_buffer);
	tidyBufInit(&doc_buffer);

	tidyBufAppend(&doc_buffer, html, strlen(html));

	/* Parse HTML, repair it, and convert to XML */
	res = tidyParseBuffer(document, &doc_buffer);
	if (res >= 0) {
		res = tidyCleanAndRepair(document);
		if (res >= 0) {
			res = tidySaveString(document, xml, &buffer_size);
			/* Expand the buffer until tidy's output fits */
			while (res == -ENOMEM) {
				buffer_size++;
				xml = (char *) realloc(xml, buffer_size);
				res = tidySaveString(document, xml, &buffer_size);
				xml[buffer_size] = '\0';
			}
		}
	}

	/* Check for errors */
	if (res < 0) {
		tidyBufFree(&doc_buffer);
		tidyBufFree(&tidy_err_buffer);
		tidyRelease(document);
		return NULL;
	}

	/* Clean up */
	tidyBufFree(&doc_buffer);
	tidyBufFree(&tidy_err_buffer);
	tidyRelease(document);

	return xml;
}

/**
 * eval_xpath_expr:
 * @xml_data - a string with the xml data
 * @expression - the expressions to evaluate
 * 
 * Evaluates an XPath expression on the given XML file.
 * 
 * Returns an xmlXPathObjectPtr, that must be freed with
 * xmlXPathFreeObject(). If an error occurs, returns NULL.
 */
xmlXPathObjectPtr eval_xpath_expr(xmlChar *xml_data, xmlChar *expression) {
	xmlDocPtr xml_doc;
	xmlXPathContextPtr xpath_context;
	xmlXPathObjectPtr xpath_object;

	/* Create an XML document */
	xml_doc = xmlParseDoc(xml_data);
	if (xml_doc == NULL) {
		fprintf(stderr, "Error: unable to parse XML\n");
		return NULL;
	}

	/* Create XPath context */
	xpath_context = xmlXPathNewContext(xml_doc);
	if (xpath_context == NULL) {
		fprintf(stderr, "Error: unable to create XPath context\n");
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	/* Add XML namespace for XHTML */
	if (xmlXPathRegisterNs(xpath_context, BAD_CAST XHTML_PREFIX, BAD_CAST XHTML_HREF) != 0) {
		fprintf(stderr, "Error: unable to register XML namespace\n");
		xmlXPathFreeContext(xpath_context);
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	/* Evaluate XPath expression */
	xpath_object = xmlXPathEvalExpression(expression, xpath_context);
	if (xpath_object == NULL) {
		fprintf(stderr, "Error: unable to evaluate XPath expression\n");
		xmlXPathFreeContext(xpath_context);
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	/* Clean up */
	xmlXPathFreeContext(xpath_context);
	xmlFreeDoc(xml_doc);

	return xpath_object;
}

/**
 * write_data:
 * @ptr - CURL response data pointer
 * @size - size of the data to write in units of nmemb
 * @nmemb - multiplier of size
 * @data - the structure to write data to
 * 
 * Writes CURL response to a curl_response structure.
 *
 * Returns the size of data written in bytes.
 */
size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data) {
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
 * to_hex:
 * @code - char (from 0 to 15) to convert to hex
 *
 * Converts a number from 0 to 15 to hex.
 *
 * Returns the number converted to hex as a char.
 */
char to_hex(char code) {
	static char hex[] = "0123456789abcdef";
	return hex[code & 15];
}

/**
 * url_encode:
 * @str - string to URL-encode
 *
 * URL-encodes a string.
 * IMPORTANT: the returned string must be freed with free().
 *
 * Returns the URL-encoded string.
 */
char *url_encode(char *str) {
	char *pstr = str;
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

void
print_xpath_nodes(xmlNodeSetPtr nodes) {
    xmlNodePtr cur;
    int size;
    int i;
    
    size = (nodes) ? nodes->nodeNr : 0;
    
    printf("Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
		if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
		    cur = nodes->nodeTab[i];   	    
		    if(cur->ns) { 
	    	        printf("= element node \"%s:%s\": href=%s\n", 
			    cur->ns->href, cur->name, xmlGetProp(cur, BAD_CAST "href"));
		    } else {
	    	        printf("= element node \"%s\": href=%s\n", 
			    cur->name, xmlGetProp(cur, BAD_CAST "href"));
		    }
		} else {
		    cur = nodes->nodeTab[i];    
		    printf("= node \"%s\": type %d", cur->name, cur->type);
		}
    }
}