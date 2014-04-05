#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    address.sin_family = PF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*) &address, len);
    if(result == -1) {
        printf("oops: client2");
        exit(1);
    }
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("Char form server = %c\n", ch);
    close(sockfd);
    exit(0);
}