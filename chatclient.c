#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
	
#define BUFSIZE 1024
#define PORT 5001
#define HOST "127.0.0.1"
#define PASSWORD "cs3251secret"
#define EVER ;;
		
void send_recv(int i, int sockfd, char *username)
{
	char send_buf[BUFSIZE];
	char recv_buf[BUFSIZE];
	char in_buf[BUFSIZE];
	char new_buf[10];
	int nbyte_recvd;

	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	
	if (i == 0){
		strcpy(send_buf, username);
		fgets(in_buf, BUFSIZE, stdin);
		if (strcmp(in_buf , "exit\n") == 0) {
			strcat(send_buf, " has left the chat\n");
			send(sockfd, send_buf, strlen(send_buf), 0);
			exit(0);
		} else
			strcat(send_buf, ": ");
		if(strcmp(in_buf, ":)\n") == 0) 
			strcat(send_buf, "[feeling happy]\n");
		else if (strcmp(in_buf, ":(\n") == 0)
			strcat(send_buf, "[feeling sadn");
		else if (strcmp(in_buf, ":mytime\n") == 0){ 
			
			sprintf(new_buf, "%02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			strcat(send_buf, new_buf);}
		else if (strcmp(in_buf, ":+1hr\n") == 0) {
			sprintf(new_buf, "%02d:%02d:%02d\n", (timeinfo->tm_hour) + 1, timeinfo->tm_min, timeinfo->tm_sec);
			strcat(send_buf, new_buf);
		}

		else strcat(send_buf, in_buf);
		send(sockfd, send_buf, strlen(send_buf), 0);
		if (strstr(send_buf, ":close\n") != NULL)
			exit(0);
		
		
	}else {
		if ((nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0)) <= 0) {
			printf("Server has closed, have a good day!\n");
			close(i);
		}
		recv_buf[nbyte_recvd] = '\0';
		printf("> %s" , recv_buf);
		fflush(stdout);
		if (strstr(":close\n", recv_buf) != NULL) {
			printf("Server is closing, have a nice day!\n");
			exit(0);
		}
	}
}
		
		
void connect_request(int *sockfd, struct sockaddr_in *server_addr, char *addr, int port)
{
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(port);
	server_addr->sin_addr.s_addr = inet_addr(addr);
	memset(server_addr->sin_zero, '\0', sizeof server_addr->sin_zero);
	if(connect(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
}
	
int main(int argc, char *argv[])
{
	char host[16];
	strcpy(host, HOST);
	int port = PORT;
	char username[20];
	int opt;
	int password = 1;
	while ((opt = getopt(argc, argv, "h:s:u:p:")) != -1)
    {
      /* Detect the end of the options. */
      switch (opt)
        {
        case 'u':
          for (int i = 0; i < strlen(optarg); i++) {
          	if (isalnum(optarg[i]) == 0) {
          		printf("Username must be alphanumeric\n");
          		return 1;
          	}
          }
          
          strcpy(username, optarg);
          break;
        case 'p':
          if (strcmp(optarg, PASSWORD) == 0) {
          	password = 0;
          	break;
          }
          	
          else {
          	printf("Incorrect password\n");
          	return 1;
          }
          case 'h':
          	strcpy(host, optarg);
          case 's':
          	port = atoi(optarg);
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
        	printf("Incorrect flags provided\n");
         	return 1;
        }
    }
    if (strcmp(username, "\0") == 0) {
    	printf("Must enter a username, try -u <username>\n");
    	return 1;
    }
    if (password) {
    	printf("Must enter the server password, try -p <password>\n");
    	return 1;
    }


	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;
	
	connect_request(&sockfd, &server_addr, host, port);

	puts("~~~ Welcome to the CS3251 chat room~~~\n");
	char joinmsg[50];
	strcpy(joinmsg, username);
	strcat(joinmsg, " has joined the chat!\n");
	send(sockfd, joinmsg, strlen(joinmsg), 0);


	FD_ZERO(&master);
        FD_ZERO(&read_fds);
        FD_SET(0, &master);
        FD_SET(sockfd, &master);
	fdmax = sockfd;
	
	for(EVER){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		
		for(i=0; i <= fdmax; i++ )
			if(FD_ISSET(i, &read_fds))
				send_recv(i, sockfd, username);
	}
	printf("client-quit\n");
	close(sockfd);
	return 0;
}