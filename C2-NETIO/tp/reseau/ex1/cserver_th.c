#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

struct th_info
{
    int fd;
    int i;
};

int safe_write(int fd, char *buff, size_t size)
{
    size_t written = 0;

    while (0 < (size - written))
    {
        ssize_t ret = write(fd, buff + written, size - written);

        if (ret < 0)
        {
            perror("write");
            return -1;
        }

        written += ret;
    }
}

void *handle_client(void *pctx)
{
    struct th_info *ctx = (struct th_info *)pctx;
    int client_fd = ctx->fd;

    FILE *f = fopen("./starwars.txt", "r");

    if (f == NULL)
    {
        perror("fopen");
        return NULL;
    }

    char buff[1024];
    while (1)
    {

        char *s = fgets(buff, 1024, f);

        if (s == NULL)
        {
            if (feof(f))
            {
                break;
            }

            perror("fgets");
            return NULL;
        }

        if (strstr(s, "\033[H"))
        {
            usleep(100000);
        }

        int len = strlen(s);

        safe_write(client_fd, s, len);
    }

    close(client_fd);

    free(ctx);

    return NULL;
}

int main(int argc, char const *argv[])
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result = NULL;

    int ret = getaddrinfo(NULL, argv[1], &hints, &result);

    if (ret < 0)
    {
        herror("getaddrinfo");
        return 1;
    }

    int sock = 0;
    int server_ready = 0;

    struct addrinfo *tmp;
    for (tmp = result; tmp != NULL; tmp = tmp->ai_next)
    {
        sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

        if (sock < 0)
        {
            perror("socket");
            continue;
        }

        if (bind(sock, tmp->ai_addr, tmp->ai_addrlen) < 0)
        {
            perror("bind");
            continue;
        }

        if (listen(sock, 5) < 0)
        {
            perror("listen");
            continue;
        }

        server_ready = 1;
        break;
    }

    if (server_ready == 0)
    {
        fprintf(stderr, "PAS SERVER READY :-'(");
        return 1;
    }

    int client_fd = -1;

    struct sockaddr client_addr;
    socklen_t client_addr_len;

    int i = 0;

    while (1)
    {
        client_fd = accept(sock, &client_addr, &client_addr_len);

        if (client_fd < 0)
        {
            perror("accept");
            break;
        }

        struct th_info *ctx = malloc(sizeof(struct th_info));
        if (ctx == NULL)
        {
            perror("malloc");
        }
        ctx->fd = client_fd;
        ctx->i = i++;

        pthread_t th;
        pthread_create(&th, NULL, handle_client, (void *)ctx);
    }

    close(sock);

    return 0;
}
