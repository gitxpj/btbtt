#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "requests.h"

void init_buffer(buffer_t *b) {
	b->len = 0;
	b->ptr = malloc(b->len + 1);
	if (b->ptr == NULL) {
		printf("malloc buffer failed!");
		return;
	}
	b->ptr[0] = '\0';
}

size_t flush(void *ptr, size_t size, size_t nmemb, buffer_t *b) {
	size_t new_len = b->len + size * nmemb;
	b->ptr = realloc(b->ptr, new_len + 1);
	if (b->ptr == NULL) {
		printf("realloc failed!\n");
		return 0;
	}
	memcpy(b->ptr + b->len, ptr, size * nmemb);
	b->ptr[new_len] = '\0';
	b->len = new_len;
	
	return size * nmemb;
}

buffer_t *process_http(const char *url, const char *post) {
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if (curl) {
		buffer_t *b = malloc(sizeof(buffer_t));
		init_buffer(b);
		
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, flush);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, b);
		if (post)
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
		}
		
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		if (res == CURLE_OK) {
			return b;
		}
	}
	return NULL;
}

buffer_t *http_get(const char *url) {
	return process_http(url, NULL);
}

buffer_t *http_post(const char *url, const char *post) {
	return process_http(url, post);
}

void http_free(buffer_t *buf) {
	if (buf == NULL)
		return;
	
	if (buf->ptr) {
		free(buf->ptr);
	}
	free(buf);
}

