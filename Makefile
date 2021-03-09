server: server.c
	gcc -o chatserver server.c
client: client.c
	gcc -o chatclient client.c
chat:
	gcc -o chatclient client.c
	gcc -o chatserver server.c
