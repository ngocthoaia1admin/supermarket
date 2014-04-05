server : server.o lib.o xml.o connectdb.o
	gcc -o server server.o lib.o xml.o connectdb.o -lmysqlclient_r -I/usr/include/mysql -lpthread
server.o : source/server.c
	gcc -o server.o -c source/server.c -lmysqlclient_r -I/usr/include/mysql
lib.o : source/lib.c
	gcc -o lib.o -c source/lib.c -lmysqlclient_r -I/usr/include/mysql
connectdb.o : source/connectdb.c
	gcc -o connectdb.o -c source/connectdb.c -lmysqlclient_r -I/usr/include/mysql
xml.o : source/xml.c
	gcc -o xml.o -c source/xml.c