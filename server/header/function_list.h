#ifndef LIB_H
#define LIB_H
#include <mysql.h>

void login(char* data, int* user_type, MYSQL* my_connection);
#endif