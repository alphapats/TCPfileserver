/*
FILE NAME: client.cpp
CREATED BY:163054001 AMIT PATHANIA
			15305r007 Nivia Jatain
This files create a peer. File takes two commandline input arguments server-ip and server port.
Server IP and port will be used to connect the server and publish and subscribe events.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

#define ERROR     -1			//returns -1 on error as message
#define MAX_BUFFER    512      //this is max size of input and output MAX_BUFFER used to store send and recieve data
//#define LISTENING_PORT 

int fetch_file(int ,char*); //functionn to recieve file

int main(int argc, char **argv)  //IP and port mentioned
{
	int sock; // sock is socket desriptor for connecting to remote server 
	struct sockaddr_in remote_server; // contains IP and port no of remote server
	char input[MAX_BUFFER];  //user input stored 
	char output[MAX_BUFFER]; //recd from remote server
	int len;//to measure length of recieved input stram on TCP
	char const *temp; // variable to store temporary value	int choice;//to take user input
	int choice;//to take user input

	//client takes two arguements SERVER IP ADDRESS,SERVER PORT 
	if (argc < 3)    // check whether port number provided or not
	{ 
		fprintf(stderr, "ERROR, ENTER SERVER IP ADDRESS AND PORT \n");
		exit(-1);
	}

	//for connecting with server for publishing and search files
	if ((sock= socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{ 
		perror("socket");  // error checking the socket
		exit(-1);  
	} 
	  
	remote_server.sin_family = AF_INET; // family
	remote_server.sin_port =htons(atoi(argv[2])); // Port No and htons to convert from host to network byte order. atoi to convert asci to 		integer
	remote_server.sin_addr.s_addr = inet_addr(argv[1]);//IP addr in ACSI form to network byte order converted using inet
	bzero(&remote_server.sin_zero, 8); //padding zeros
	
	if((connect(sock, (struct sockaddr *)&remote_server,sizeof(struct sockaddr_in)))  == ERROR) //pointer casted to sockaddr*
	{
		perror("connect");
		exit(-1);
	}
	printf("%s","\n\nConnected to server\t \n\n");

	//setting up own port for listening incoming connections for fetch

	while(1)
	{
		//DISPLAY MENU FOR USER INPUTS
		printf("\n#####################WELCOME#########################################\n");
		printf("##################FILE MANAGEMENT SYSTEM############################ \n");
		printf("1.NEW USER\n");
		printf("2.REQUEST FILE\n");
		printf("3.TERMINATE THE CONNECTION TO FILE SERVER\n");
		printf("\n############################################################## \n");
		printf("Enter your choice : ");
		if(scanf("%d",&choice)<=0)
			{
	    	printf("Enter only an integer from 1 to 3 \n");
	    	exit(0);
			} 
		else
			{
	   		switch(choice)
				{
				case 1:  //ADD NEW USER 
					
					temp="new"; // keyword to be send to server so that server knows it is a publish operation

					if( (len = send(sock, temp, sizeof(temp) ,0)) < 0 ) 
						{
							perror("Error in send");
							return -1;
						}

					//send(sock, temp, sizeof(temp) ,0); // send input to server


					/* read acknowlegment from socket */
						if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}

					//len = recv(sock, output, MAX_BUFFER, 0); // recieve confirmation message from server
					output[len] = '\0';
					printf("%s\n" , output); // display confirmation message
					bzero(output,MAX_BUFFER); // pad MAX_BUFFER with zeros

					
					printf("Enter the username     ");
		   			//fgets(input,MAX_BUFFER,stdin); //take input from user
					scanf(" %[^\t\n]s",input); //recieve user input


					if( (len = send(sock, input, strlen(input) ,0)) < 0 ) 
						{
							perror("Error in send");
							return -1;
						}
					//send(sock, input, strlen(input) ,0); // send input to server

					if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in recieve");
						exit(0);
						}

					//len = recv(sock, output, MAX_BUFFER, 0); // recieve confirmation message from server
					output[len] = '\0';
					printf("%s\n" , output); // display confirmation message
					bzero(output,MAX_BUFFER); // pad MAX_BUFFER with zeros

					printf("Enter the password     ");
		   			//fgets(input,MAX_BUFFER,stdin); //take input from user
					scanf(" %[^\t\n]s",input); //recieve user input

					if( (len = send(sock, input, strlen(input) ,0)) < 0 ) 
						{
							perror("Error in send");
							return -1;
						}

					//send(sock, input, strlen(input) ,0); // send input to server

					if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}

					//len = recv(sock, output, MAX_BUFFER, 0); // recieve confirmation message from server
					output[len] = '\0';
					printf("%s\n" , output); // display confirmation message
					bzero(output,MAX_BUFFER); // pad MAX_BUFFER with zeros
					printf("Connection terminated with server.\n");
					/* close socket*/
				if(close(sock) < 0)
				{
					perror("socket close error");
					exit(EXIT_FAILURE);
				}
					return 0;
		
							
                 	break;

      		 	case 2:   //AUTHENTICATE USER

				temp="get"; // keyword to be send to server so that server knows it is a search operation
				char file_name[MAX_BUFFER];
				//ssize_t sent_bytes;

				if( (len = send(sock, temp, sizeof(temp) ,0)) < 0 ) 
				{
					perror("Error in send");
					return -1;
				}

				//send(sock, temp, sizeof(temp) ,0); // send input to server

				if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}
				//len = recv(sock, output, MAX_BUFFER, 0); // recieve confirmation message from server
					output[len] = '\0';
					printf("%s\n" , output); // display confirmation message
					bzero(output,MAX_BUFFER); // pad MAX_BUFFER with zeros

				printf("Enter the username    ");
		   			
				scanf(" %[^\t\n]s",input);
				//send(sock, input, strlen(input) ,0); // send input keyword to server
				if( (len = send(sock, input, strlen(input) ,0)) < 0 ) 
				{
				perror("send error");
				return -1;
				}

				if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}


				//len = recv(sock, output, MAX_BUFFER, 0);
				output[len] = '\0';
				printf("%s\n" , output);
				bzero(output,MAX_BUFFER);  

				printf("Enter password  ");	
				scanf(" %[^\t\n]s",input);
				if( (len = send(sock, input, strlen(input) ,0)) < 0 ) 
				{
				perror("send error");
				return -1;
				}
				//send(sock, input, strlen(input) ,0); // send input keyword to server

				if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}
				//len = recv(sock, output, MAX_BUFFER, 0);
				output[len] = '\0';
				printf("%s\n" , output);
				

				if(output[0]=='S' && output[1]=='u' && output[2]=='c') 
				{
				bzero(output,MAX_BUFFER); 
				printf("Enter FILENAME WITH EXTENSION  ");	
				scanf(" %[^\t\n]s",input);
				
				//send(sock, input, strlen(input) ,0); // send input keyword to server
				//len = recv(sock, output, MAX_BUFFER, 0);
				//output[len] = '\0';
				//printf("%s\n" , output);
				strcpy(file_name, input);

				//bzero(output,MAX_BUFFER); 
				
				
				

				printf("Server searching...... Waiting \n");
				fetch_file(sock, file_name); /* argv[1] = file name */
				
				
				//close(sock); // Disconnect from server
				printf(" \n SEARCH COMPLETE!!! \n");
				}

				printf("Connection terminated with server.\n");
					/* close socket*/
				if(close(sock) < 0)
				{
					perror("socket close error");
					exit(EXIT_FAILURE);
				}
					return 0;
		
				


				
				break;

        		case 3:  //when client want to terminate connection with server  
					temp="ter"; // keyword to be send to server so that server knows client wants to terminate connection to server

					if ( (len = send(sock, temp, sizeof(temp) ,0)) < 0) {
						perror("error in receive");
						exit(0);
						}
					//send(sock, temp, sizeof(temp) ,0); // send input to server

					if ( (len = recv(sock, output, MAX_BUFFER, 0)) < 0) {
						perror("error in receive");
						exit(0);
						}
					//len = recv(sock, output, MAX_BUFFER, 0); // recieve confirmation message from server
					output[len] = '\0';
					printf("%s\n" , output); // display confirmation message
					bzero(output,MAX_BUFFER); // pad MAX_BUFFER with zeros

					//close(sock);
					printf("Connection terminated with server.\n");
					/* close socket*/
				if(close(sock) < 0)
				{
					perror("socket close error");
					exit(EXIT_FAILURE);
				}
					return 0;
		
       			

        		default:    printf("Invalid option\n");
			} // terminates switch case
		
		} // terminates else statement
	} // terminates while loop 
		

	
	return (0);
}


int fetch_file(int sock, char* file_name)
{
	ssize_t len, data_received, total_data_received; // variables to store daat recd
	int counter; //to count number of receives
	char send_buff[MAX_BUFFER]; // buffer to store sending msg
	char receive_buff[MAX_BUFFER]; //buffer to store recieved data
	size_t send_bufflen; //length of data sent

	int fp; //file descriptor

	//sending file name to server
	sprintf(send_buff, "%s\n", file_name); 
	send_bufflen = strlen(send_buff); 
	if( (len = send(sock, file_name, send_bufflen, 0)) < 0 ) {
		perror("Error sending filename");
		return -1;
	}

	char file_name_full[MAX_BUFFER];
	strcpy(file_name_full,"downloads/");
	strcat(file_name_full,file_name);
	//cout<<file_name_full;


	if ( (fp = open(file_name_full, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0 ) //open file
	{
		perror("File couldn't be created");
		return -1;
	}

	counter = 0; 
	total_data_received = 0; 


	while ( (data_received = recv(sock, receive_buff, MAX_BUFFER, 0)) > 0 )
	{

	counter++;
	total_data_received += data_received;
		if (write(fp, receive_buff, data_received) < 0 )
		{
		perror("error writing to file");
		return -1;
		}
	}
	close(fp); //close file
	if (total_data_received == 0 )
	{
		cout<<"File not found";
		remove(file_name_full);
		return -1;
	}

cout<<"Total data received (file size):  " << total_data_received << " (bytes) in " <<counter<< " receive(s)\n";
return total_data_received;
}		
	
	
