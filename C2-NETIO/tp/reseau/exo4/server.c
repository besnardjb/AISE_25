#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

int safe_write(int fd, char *buff, size_t size) {
	size_t written = 0;

	while (0 < (size - written)) {
		ssize_t ret = write(fd, buff + written, size - written);

		if (ret < 0) {
			perror("write");
			return -1;
		}

		written += ret;
	}

	return 0;
}

ssize_t file_size(char * path)
{
	struct stat st;
	if(stat(path, &st))
	{
		return -1;
	}

	return st.st_size;
}


void send_header(FILE * out, size_t size, int code)
{
	char scode[512];
	
	snprintf(scode, 512, "HTTP/1.0 %d OK", code);

	fprintf(out,"%s\n\
Server: CHPS Server\n\
Date: Mon, 27 Nov 2023 15:26:20 GMT\n\
Content-type: text/html\n\
Content-Length: %lu\n\
Last-Modified: Sun, 26 Nov 2023 19:34:17 GMT\n\n", scode, size);

}

void send_file(char * path, FILE* out)
{
	printf("Sending file %s\n", path);
	int fd = open(path, O_RDONLY);

	if(fd < 0 )
	{
		perror("open");
		return;
	}


	char buff[512];

	ssize_t ret = 0;
	while((ret = read(fd, buff, 512)))
	{
		if(ret < 0)
		{
			perror("read");
			break;
		}

		fwrite(buff, sizeof(char), ret, out);
	}

}


void *handle_client(void *psocket) {

	FILE * inout = fdopen(*((int*)psocket), "w+");

	if(!inout)
	{
		perror("fdopen");
		return NULL;
	}

	char buff[2048];
	fgets(buff, 2048, inout);


	if(buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T')
	{

		char * uri = buff + 5;

		char * http = strstr(uri, "HTTP");

		if(http)
		{
			*(http - 1) = '\0';
		}

		printf("URI: %s\n", uri);

		char path[512];

		if(!strlen(uri))
		{
			uri = "index.html";
		}

		snprintf(path, 512, "./website/%s", uri);

		ssize_t fsize = file_size(path);

		if(fsize < 0)
		{
			send_header(inout, 0, 404);
			fclose(inout);
			return NULL;
		}

		
		send_header(inout, fsize, 200);

		send_file(path, inout);
	}


	fclose(inout);

	return NULL;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		(void)fprintf(stderr, "Usage %s [PORT]\n", argv[0]);
		exit(1);
	}

	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *aret = NULL;

	int ret = getaddrinfo(NULL, argv[1], &hints, &aret);

	if (ret < 0) {
		perror("getaddrinfo");
		return 1;
	}

	struct addrinfo *tmp = NULL;

	int sock = -1;
	int success = 0;

	for (tmp = aret; tmp != NULL; tmp = tmp->ai_next) {
		/* Parcours des choix*/
		sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

		if (sock < 0) {
			continue;
		}

		if (bind(sock, tmp->ai_addr, tmp->ai_addrlen)) {
			continue;
		}

		if (listen(sock, 5)) {
			continue;
		}

		/* All OK */
		success = 1;
		break;
	}

	if (!success) {
		(void)fprintf(stderr, "Failed to create server");
		exit(1);
	}

	while (1) {
		struct sockaddr addr;
		socklen_t len = sizeof(struct sockaddr);
		int ret = accept(sock, &addr, &len);

		if (ret < 0) {
			perror("accept");
			exit(1);
		}

		/* We have a client */
		int *sockfd = malloc(sizeof(int));

		if (sockfd == NULL) {
			perror("malloc");
			continue;
		}

		*sockfd = ret;

		pthread_t th = 0;
		pthread_create(&th, NULL, handle_client, sockfd);
	}

	return 0;
}
