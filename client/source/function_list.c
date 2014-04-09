#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/lib.h"
#include "../header/xml.h"

bool get_data(int client_sockfd, char* buffer) {
    int size = 0;
    while(1) {
        int rc = read(client_sockfd, &buffer[size], 1);        
        if(buffer[size] == '\n') {
            buffer[size] = '\0';
            return true;
        }
        if(rc <= 0) {
            //close(client_sockfd);
            printf("khong doc duoc ket qua\n");
            return false;
        }
        size++;
    }
}

bool login(int sockfd) {
    char username[100];
    char password[100];
    printf("Nhap user name:\n");
    gets(username);
    printf("nhap password:\n");
    gets(password);
    char data_login[1000];
    strcpy(data_login, "<login>");
    strcat(data_login, (char*) create_tag(username, "<username>"));
    strcat(data_login, (char*) create_tag(password, "<password>"));
    strcat(data_login, "</login>\n");
    write(sockfd, data_login, strlen(data_login));
    char data_result[1000];
    get_data(sockfd, data_result);
    printf("%s\n", data_result);
}

bool logout(int sockfd) {

}