#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/*
 * Global constants
 */
static const char *URL_HOMEPAGE = "http://wallbase.cc/start";
static const char *URL_LOGIN = "http://wallbase.cc/user/login";
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
struct curl_slist *login(char *username, char *password);

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_response *data);
char *url_encode(char *str);
char to_hex(char code);

/*
 * Main
 */
int main(int argc, char* argv[]) {
	/* Variables */
	struct curl_slist *cookies;

	/* Init */
	curl_global_init(CURL_GLOBAL_ALL);

	/* Main operation */
	cookies = login("user", "pass");

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
struct curl_slist *login(char *username, char *password) {
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
	free(enc_username);
	free(enc_password);

	return cookies;
}

/*
 * Helper function implementations
 */

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
	char *pstr = str, *buf = malloc(strlen(str) * 3 + 1), *pbuf = buf;
	while (*pstr) {
		if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') 
			*pbuf++ = *pstr;
		else if (*pstr == ' ') 
			*pbuf++ = '+';
		else 
			*pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}