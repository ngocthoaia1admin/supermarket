#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <mysql.h>
#include <time.h>
#include "../header/connectdb.h"
#include "../header/xml.h"
#include "../header/route.h"
#include "../header/lib.h"

MYSQL* my_connection;

bool is_connected(int sock) {
    unsigned char buf;
    int err = recv(sock,&buf,1,MSG_PEEK);
    return err == -1 ? false : true;
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
                route(&user_type, buffer, my_connection, client_sockfd);
                time(&last_connect);
            } else {
                time_t current_time;
                time(&current_time);
                int seconds = difftime(current_time, last_connect);
                if(seconds > time_out * 60) {
                    close(client_sockfd);
                    printf("Disconnected\n");
                    return NULL;
                }
                usleep(100);
            }
        } else {
            close(client_sockfd);
            return NULL;
        }
        sleep(1);
    }
}

void init(int *server_sockfd, int* server_len, struct sockaddr_in* server_address) {
    *server_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    (*server_address).sin_family = PF_INET;
    //(*server_address).sin_addr.s_addr = inet_addr("127.0.0.1");
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
        client_sockfd[i] = accept(server_sockfd, (struct sockaddr*) &client_address[i],
                (socklen_t*) &client_len[i]);
        int res = pthread_create(&a_thread[i], NULL, service_for_client,
            (void*) &client_sockfd[i]);
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
