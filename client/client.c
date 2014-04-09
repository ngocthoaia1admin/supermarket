#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void write_server(int sockfd) {    
    char data[] = "<login><username>admin</username><password>123</password></login>\n";
    write(sockfd, data, strlen(data));
}

void start_client() {
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = '\n';
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    address.sin_family = PF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9738;
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*) &address, len);
    if(result == -1) {
        printf("oops: client2\n");
        exit(1);
    }
    // write(sockfd, &ch, 1);   
    write_server(sockfd);
    while(1) {
        int rc = read(sockfd, &ch, 1);
        if(rc < 0) {
        } else {
            printf("Char form server = %c\n", ch);
        }
    }
    close(sockfd);
}
int main(int argc, char* argv[]) {    
    start_client();
    sleep(2);
    exit(0);
}