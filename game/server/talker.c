#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "9034"    // порт для соединения

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    char buf[10];
    if (argc != 3) {
        fprintf(stderr,"usage: client hostname messagen");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %sn", gai_strerror(rv));
        return 1;
    }

    // пробегаемся по результатам и создаём сокет
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to bind socketn");
        return 2;
    }
    while (1) {
        if ((numbytes = send(sockfd, argv[2], strlen(argv[2]), 0) == -1)) {
            perror(": sendto");
            exit(1);
        }
        if ((numbytes = recv(sockfd, buf, 9, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        freeaddrinfo(servinfo);

        printf("client: sent %d bytes to %sn", numbytes, argv[1]);
    }
    close(sockfd);

    return 0;
}