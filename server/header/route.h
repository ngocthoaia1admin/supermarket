#ifndef ROUTE_H
#define ROUTE_H
void route(int* user_type, char* client_request,
    MYSQL* my_connection, int client_sockfd);
#endif