#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include "../header/connectdb.h"
#include "../header/xml.h"
#include "../header/lib.h"

void login(char* data, int* user_type, MYSQL* my_connection, int client_sockfd) {
    char username[100];
    char password[100];
    get_content_tag(data, "<username>", username);
    get_content_tag(data, "<password>", password);
    char sql[1000] = "\0";
    strcat(sql, "SELECT * FROM users WHERE username= '");
    strcat(sql, username);
    strcat(sql, "' and password = '");
    strcat(sql, password);
    strcat(sql, "'");
    printf("%s\n", sql);
    int res = mysql_query(my_connection, sql);
    MYSQL_RES* res_ptr = mysql_store_result(my_connection);
    *user_type = -1;
    if(res_ptr) {
        printf("Retrieved %lu row\n", (unsigned long) mysql_num_rows(res_ptr));
        MYSQL_ROW sqlrow = mysql_fetch_row(res_ptr);
        if(sqlrow != NULL) {
            if(sqlrow[2] != NULL) {
                *user_type = atoi(sqlrow[2]);
            } else {
                *user_type = 0;
            }
        }
    }
    mysql_free_result(res_ptr);

    char data_return[1000];
    if(*user_type == -1) {
        strcpy(data_return, create_tag("error", "<login>"));        
    } else {
        strcpy(data_return, create_tag("success", "<login>"));
    }
    send_data(client_sockfd, data_return);
}

void logout(int client_sockfd) {
}