#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <mysql.h>
#include <time.h>
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
void send_data(int client_sockfd, char* buffer) {
    strcat(buffer, "\n");
    write(client_sockfd, buffer, strlen(buffer));
}