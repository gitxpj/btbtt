#ifndef _H_REQUESTS
#define _H_REQUESTS

typedef struct buffer {
			size_t len;
				char *ptr;
} buffer_t;

buffer_t *http_get(const char *url);
buffer_t *http_post(const char *url, const char *buf);
void http_free(buffer_t *buf);
#endif

