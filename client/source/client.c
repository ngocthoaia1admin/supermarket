#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../header/lib.h"
#include "../header/function_list.h"

void write_server(int sockfd) {    
    char data[] = "<login><username>admin</username><password>123</password></login>\n";
    write(sockfd, data, strlen(data));
}

void print_menu() {
    printf("Table list\n");
    printf("1. login\n");
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
    print_menu();
    while(ch != 'q') {
        printf("Nhap 1 ki tu: ");
        //ch = getchar();
        scanf("%c%*c", &ch);
        if(ch == '1') {
            login(sockfd);
            //write_server(sockfd);
        }
    }
    close(sockfd);
}
int main(int argc, char* argv[]) {    
    start_client();
    sleep(2);
    exit(0);
}