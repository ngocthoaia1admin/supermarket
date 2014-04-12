#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H
#include <mysql.h>

void login(char* data, int* user_type, MYSQL* my_connection, int client_sockfd);
void logout(int client_sockfd);
#endif