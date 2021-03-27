server: server.c
	gcc -o chatserver chatserver.c
client: client.c
	gcc -o chatclient chatclient.c
chat:
	gcc -o chatclient chatclient.c
	gcc -o chatserver chatserver.c
clean:
	rm chatclient
	rm chatserver
	rm output.txt

