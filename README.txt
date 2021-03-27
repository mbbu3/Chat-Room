Project written by: Matthew Barroso
Email: mbbu3@gatech.edu
OS: Ubuntu 18.04
Files submitted: 
	Makefile: run make chat to create executables for the necessary files.
	chatclient.c: client file for chat.
	chatserver.c: server file for chat.

How to run:
First to make the necessary executables, you must first run "make chat". This will create files called
"chatclient" and "chatserver"

To start the server, simply run "./chatserver -s <port number>". If port number is not specified it will default to 5001

To start a client, you must run "./chatclient -h <hostname> -s <port number> -u <username> -p <passcode>" If hostname 
is not specified it will default to 127.0.0.1. If port number is not specified it will defaul to port 5001. To close 
the client, you can simply type `exit`. To close the server for everyone, type `:close`.
