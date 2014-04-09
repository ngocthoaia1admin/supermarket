#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

MYSQL* connect_db() {
	MYSQL *my_connection = malloc(sizeof(MYSQL));
	mysql_init(my_connection);
	if(mysql_real_connect(my_connection, "localhost", "root", "123", "supermarket", 0, NULL, 0)) {
		printf("Connect is successful\n");		
		return my_connection;
	} else {
		fprintf(stderr, "Connection failed\n");
		if(mysql_errno(my_connection)) {
			fprintf(stderr, "Connection error %d: %s\n", mysql_errno(my_connection), mysql_error(my_connection));
		}
	}
}
void close_connect(MYSQL* my_connection) {
	mysql_close(my_connection);
}


