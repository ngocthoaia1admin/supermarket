#include <string.h>
#include <stdio.h>
#include <unistd.h>
bool get_data(int sockfd, char* buffer) {
    int size = 0;
    while(1) {
        int rc = read(sockfd, &buffer[size], 1);        
        if(buffer[size] == '\n') {
            buffer[size] = '\0';
            return true;
        }
        if(rc <= 0) {
            //close(sockfd);
            printf("khong doc duoc ket qua\n");
            return false;
        }
        size++;
    }
}
void send_data(int sockfd, char* buffer) {
    strcat(buffer, "\n");
    write(sockfd, buffer, strlen(buffer));
}