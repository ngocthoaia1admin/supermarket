#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/lib.h"
#include "../header/xml.h"


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
    strcat(data_login, "</login>");
    send_data(sockfd, data_login);
    
    char data_result[50];
    get_data(sockfd, data_result);
    char login_result[20];
    get_content_tag(data_result, "<login>", login_result);
    printf("%s\n", login_result);
    if(strcmp(login_result, "success")) {
        return true;
    } else {
        return false;
    }
}

bool logout(int sockfd) {
    char data[1000];
    strcpy(data, "<logout></logout");
    send_data(sockfd, data);

    char data_result[1000];
    get_data(sockfd, data_result);
}