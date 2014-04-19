#include <string.h>
#include "../header/xml.h"
#include "../header/session_controller.h"

void route(int* user_type, char* client_request,
    MYSQL* my_connection, int client_sockfd) {
    char request_type[20];
    get_first_tag(client_request, request_type);
    if(strcmp(request_type, "<login>") == 0) {
        login(client_request, user_type, my_connection, client_sockfd);
    }
}