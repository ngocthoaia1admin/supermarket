#ifndef LIB_H
#define LIB_H
#include "bool.h"
bool get_data(int sockfd, char* buffer);
void send_data(int sockfd, char* buffer);
#endif