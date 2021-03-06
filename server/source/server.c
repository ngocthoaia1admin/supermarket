#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "../header/connectdb.h"
#include "../header/xml.h"
#include "../header/function_list.h"
#include <mysql.h>
#include <time.h>

MYSQL* my_connection;
typedef enum {
  false = 0,
  true = 1
} bool;

bool is_connected(int sock) {
    unsigned char buf;
    int err = recv(sock,&buf,1,MSG_PEEK);
    return err == -1 ? false : true;
}

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
            printf("khong doc duoc request\n");
            return false;
        }
        size++;
    }
}

void* service_for_client(void* arg) {
    int time_out = 1;
    time_t last_connect;   
    int user_type = -1;
    int client_sockfd = *((int*)arg);
    char buffer[5000];
    char request_type[100];

    time(&last_connect);
    while(1) {
        if(is_connected(client_sockfd)) {
            if(get_data(client_sockfd, buffer)) {
                get_first_tag(buffer, request_type);
                if(strcmp(request_type, "<login>") == 0) {
                    login(buffer, &user_type, my_connection, client_sockfd);
                    //solve(buffer, user_type, result);            
                    printf("client: %d\n", client_sockfd);
                    printf("request_type: %s\n", request_type);
                    printf("data: %s\n", buffer);
                    printf("user_type: %d\n", user_type);               
                    time(&last_connect);
                }
            } else {
                time_t current_time;
                time(&current_time);
                int seconds = difftime(current_time, last_connect);
                if(seconds > time_out * 60) {
                    close(client_sockfd);
                    printf("Disconnected\n");
                    return;
                }
                usleep(100);
            }
        } else {
            close(client_sockfd);
            return;
        }
        sleep(1);
    }
}

void init(int *server_sockfd, int* server_len, struct sockaddr_in* server_address) {
    *server_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    (*server_address).sin_family = PF_INET;
    (*server_address).sin_addr.s_addr = inet_addr("127.0.0.1");
    (*server_address).sin_port = 9738;
    *server_len = sizeof(*server_address);
    bind(*server_sockfd, (struct sockaddr*) server_address, *server_len);
    listen(*server_sockfd, 5);
}

void start_server(int server_sockfd) {
    my_connection = connect_db();
    pthread_t a_thread[1000];
    int client_sockfd[1000];    
    int client_len[1000];    
    struct sockaddr_in client_address[1000];
    int i = 0;
    while(1) {
        char ch;
        printf("server waiting\n");
        client_len[i] = sizeof(client_address[i]);
        client_sockfd[i] = accept(server_sockfd, (struct sockaddr*) &client_address[i], &client_len[i]);
        int res = pthread_create(&a_thread[i], NULL, service_for_client, (void*) &client_sockfd[i]);
        usleep(1000);
        while(is_connected(client_sockfd[i])) {
            i = (i + 1) % 1000;
            usleep(100);
        }
    }
}
int main(int argc, char* argv[]) {
    int server_sockfd;
    int server_len;
    struct sockaddr_in server_address;
    init(&server_sockfd, &server_len, &server_address); 
    start_server(server_sockfd);
    exit(0);
}
