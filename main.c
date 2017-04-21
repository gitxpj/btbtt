#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "requests.h"

#define MOVIE_ID   951
#define TV_ID      950
#define BTBTT_HOST "http://www.btbtt.co/"

void
get_page_by_id(int id, int page) {
	int i;
	char path[255];
	memset(path, 0, 255);

	i = sprintf(path, "%sforum-index-fid-%d", BTBTT_HOST, id);

	if (page > 1)
		i += sprintf(path + i, "-page-%d.htm", page);
	else
		i += sprintf(path + i, ".htm");
#ifdef DEBUG
	printf("path: %s\n", path);
#endif

	buffer_t *buf = http_get(path);
#ifdef DEBUG
	printf("%s", buf->ptr);
#endif
	http_free(buf);
}

int 
main(char **argc, int argv) {
	
	get_page_by_id(MOVIE_ID, 1);

	return 0;
}
