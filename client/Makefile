client : client.o function_list.o xml.o
	gcc -o client client.o function_list.o xml.o
client.o : source/client.c
	gcc -o client.o -c source/client.c
function_list.o : source/function_list.c
	gcc -o function_list.o -c source/function_list.c
xml.o : source/xml.c
	gcc -o xml.o -c source/xml.c