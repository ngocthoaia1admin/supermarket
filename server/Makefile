CC = g++
CFLAGS=-c
SOURCES= connectdb.c session_controller.c lib.c server.c xml.c route.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=server
$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lmysqlclient_r -I/usr/include/mysql -lpthread
%.o : source/%.c
	$(CC) $(CFLAGS) $< -o $@ -lmysqlclient_r -I/usr/include/mysql -lpthread
clean :
	rm *.o
	rm $(EXECUTABLE)