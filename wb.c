#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <curl/curl.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>

/*
 * Global constants
 */

static const char *URL_HOMEPAGE = "http://wallbase.cc/start";
static const char *URL_LOGIN = "http://wallbase.cc/user/login";
static const char *URL_TOPLIST = "http://wallbase.cc/toplist";

static const char *FORMAT_LOGIN = "usrname=%s&pass=%s&nopass_email=Type+in+your+e-mail+and+press+enter&nopass=0&1=1";

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
struct curl_slist *wb_get_image_page_urls(char *html_data);

char *curl_get_response(const char *url, char *post_data, struct curl_slist *cookies);
void curl_add_cookies(CURL *curl, struct curl_slist *cookies);

char *tidy_convert_to_xml(char *html);

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data);
char *url_encode(char *str);
char to_hex(char code);

/*
 * Main
 */

int main(int argc, char* argv[]) {
	/* Variables */
	struct curl_slist *cookies;
	char *toplist;
	char *toplist_xml;

	/* Init */
	curl_global_init(CURL_GLOBAL_ALL);

	/* Main operation */
	puts("Logging in...");
	cookies = wb_login("", "");
	puts("Getting toplist...");
	toplist = curl_get_response(URL_TOPLIST, NULL, cookies);
	puts("Converting to XML...");
	toplist_xml = tidy_convert_to_xml(toplist);
	puts("Cleaning up...");
	/*printf("%s\n", toplist_xml);*/
	free(toplist);
	free(toplist_xml);

	/* Cleanup nd return */
	curl_slist_free_all(cookies);
	curl_global_cleanup();
	return 0;
}

/*
 * wallbase.cc function implementations
 */

/* Login to wallbase.cc */
/* Returns a list of cookies */
/* IMPORTANT: curl_slist_free_all() the cookies after usage */
struct curl_slist *wb_login(char *username, char *password) {
	char *enc_username;
	char *enc_password;
	char post_data[256];
	CURL *curl;
	CURLcode res;
	struct curl_slist *cookies;

	struct curl_response response;
	response.size = 0;
	response.data = malloc(4096);
	if (response.data == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(1);
	}
	response.data[0] = '\0';

	enc_username = url_encode(username);
	enc_password = url_encode(password);

	sprintf(post_data, FORMAT_LOGIN, enc_username, enc_password);

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL_LOGIN);
	curl_easy_setopt(curl, CURLOPT_REFERER, URL_HOMEPAGE);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
		exit(1);
	}

	if (response.size != 0) {
		fprintf(stderr, "Failed to login to wallbase.cc\n");
		exit(1);
	}

	res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
	if (res != CURLE_OK) {
		fprintf(stderr, "Curl get info failed: %s\n", curl_easy_strerror(res));
		exit(1);
	}

	curl_easy_cleanup(curl);
	free(response.data);
	free(enc_username);
	free(enc_password);

	return cookies;
}

/* Get wallbase.cc image page URLs from HTML */
/* IMPORTANT: the returned list must be freed with curl_slist_free_all() */
struct curl_slist *wb_get_image_page_urls(char *html_data) {
	struct curl_slist *urls = NULL;

	return urls;
}

/*
 * Helper function implementations
 */

/* Connect to URL with GET or POST requests and return the response. */
/* If post_data is NULL, then a GET request is issued. */
/* Uses cookies if cookies is not NULL. */
/* IMPORTANT: the returned string should be freed with free() */
char *curl_get_response(const char *url, char *post_data, struct curl_slist *cookies) {
	CURL *curl;
	CURLcode res;

	struct curl_response response;
	response.size = 0;
	response.data = malloc(4096);
	if (response.data == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(1);
	}
	response.data[0] = '\0';

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	if (post_data != NULL) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
	}

	if (cookies != NULL) {
		curl_add_cookies(curl, cookies);
	}

	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
		exit(1);
	}

	curl_easy_cleanup(curl);
	return response.data;
}

/* Add all cookies in a curl_slist (returned by CURLINFO_COOKIELIST) */
/* to a CURL object */
void curl_add_cookies(CURL *curl, struct curl_slist *cookies) {
	struct curl_slist *cookie = cookies;
	while (cookie != NULL) {
		curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie->data);
		cookie = cookie->next;
	}
}

/* Converts HTML to XML. */
/* IMPORTANT: the resulting string must be freed using free(). */
char *tidy_convert_to_xml(char *html) {
	TidyDoc document;
	TidyBuffer doc_buffer = {0};
	TidyBuffer tidy_err_buffer = {0};
	int res;

	/* Intentionaly left 0 to get the required buffer size. */
	unsigned int buffer_size = 0;
	char *clean_html = (char *) malloc(1);

	document = tidyCreate();
	tidyOptSetBool(document, TidyForceOutput, yes);
	tidyOptSetBool(document, TidyXmlOut, yes);
	tidyOptSetInt(document, TidyWrapLen, 4096);
	tidySetErrorBuffer(document, &tidy_err_buffer);
	tidyBufInit(&doc_buffer);

	tidyBufAppend(&doc_buffer, html, strlen(html));

	res = tidyParseBuffer(document, &doc_buffer);
	if (res >= 0) {
		res = tidyCleanAndRepair(document);
		if (res >= 0) {
			res = tidySaveString(document, clean_html, &buffer_size);
			/* Expand the buffer until tidy's output fits */
			while (res == -ENOMEM) {
				buffer_size++;
				clean_html = (char *) realloc(clean_html, buffer_size);
				res = tidySaveString(document, clean_html, &buffer_size);
				clean_html[buffer_size] = '\0';
			}
		}
	}

	if (res < 0) {
		fprintf(stderr, "Error tidying HTML\n");
		exit(1);
	}

	tidyBufFree(&doc_buffer);
	tidyBufFree(&tidy_err_buffer);
	tidyRelease(document);

	return clean_html;
}

/* Write curl response to a string */
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

/* Converts an integer value to its hex character*/
char to_hex(char code) {
	static char hex[] = "0123456789abcdef";
	return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
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