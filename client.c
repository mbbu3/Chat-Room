// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <getopt.h>
#define PORT 5001 
#define HOST "127.0.0.1"
#define PASSWORD "cs3251secret\0"

int main(int argc, char *argv[]) 
{ 
	char *host[16];
	strcpy(host, HOST);
	int port = PORT;
	char username[20];
	int opt;
	int password = 0;
	while ((opt = getopt(argc, argv, "h:s:u:p:")) != -1)
    {
      /* Detect the end of the options. */
      switch (opt)
        {
        case 'u':
          strcpy(username, optarg);
          break;

        case 'p':
          if (strcmp(optarg, PASSWORD) == 0) {
          	password = 1;
          	break;
          }
          	
          else {
          	printf("Incorrect password\n");
          	return 1;
          }
          case 'h':
          	strcpy(host, optarg);
          case 's':
          	port = optarg;

          	

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
        	printf("Incorrect flags provided");
         	return 1;
        }
    }
    if (strcmp(username, "\0") == 0) {
    	printf("Must enter a username, try -u <username>");
    	return 1;
    }
    if (password == 0) {
    	printf("Must enter a password, try -p <password>");
    	return 1;
    }



	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char input[1024] = {0};
	
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	send(sock, username, strlen(username), 0);
	send(sock, input, strlen(input), 0);  
	valread = read(sock, buffer, 1024); 
	printf("%s\n",buffer); 
	scanf("%s", input);
	return 0; 
} 
