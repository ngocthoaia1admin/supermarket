CC = gcc
CFLAGS=-c
SOURCES= client.c session_controller.c xml.c lib.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=client
$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lm
%.o : source/%.c
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm *.o