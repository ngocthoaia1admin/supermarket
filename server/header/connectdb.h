#include <mysql.h>
#ifndef CONNECTDB_H
#define CONNECTDB_H
MYSQL* connect_db();
void close_connect(MYSQL* my_connection);
#endif
