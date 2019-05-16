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

#define MYPORT "4950"
#define MAXBUFLEN 100

void *get_in_addr(struct sockaddr *sa) {
    //определение ipv4 или ipv6
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void) {
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; //ipv4 || ipv6
    hints.ai_socktype = SOCK_DGRAM; //использование датаграмм
    hints.ai_flags = AI_PASSIVE; //использовать текущий ip
    //проверка срабатывания getinfo
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        
        fprintf(stderr, "getaddrinfo: %sn", gai_strerror(rv));
        return 1;
    }
    //проход по списку
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socketn");
        return 2;
    }
    freeaddrinfo(servinfo);
    printf("listener: waiting to recvform...n");

    addr_len = sizeof their_addr;
    //проверка пакета
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    printf("listener: packet is %d bytes longn", numbytes);
    buf[numbytes] = ' ';
    printf("listener: packet contains %s n", buf);
    close(sockfd);

    return 0;

}