Project written by: Matthew Barroso
Email: mbbu3@gatech.edu
Files submitted: 
	Makefile: run make chat to create executables for the necessary files.
	client.c: client file for chat.
	server.c: server filec for chat.

How to run:
First to make the necessary executables, you must first run "make chat". This will create files called
"chatclient" and "chatserver"

To start the server, simply run "./chatserver -s <port number>". If port number is not specified it will default to 5001

To start a client, you must run "./chatclient -h <hostname> -s <port number> -u <username> -p <passcode>" If hostname 
is not specified it will default to 127.0.0.1. If port number is not specified it will defaul to port 5001
