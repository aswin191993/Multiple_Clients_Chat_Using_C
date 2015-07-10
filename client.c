/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<pthread.h>

void *functionSend(void *new);
void *functionRcv(void *new);
pthread_t thread1,thread2;

int main()
{
	int clientSocket,rc1;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.45.0.2");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	perror("connect"); 	               
	//Multiple thread is created to access Receiving and sending.
	if(rc1=pthread_create(&thread1, NULL,functionSend,(void *)clientSocket))
	{
		printf("Thread creation failed: %d\n", rc1);
	}
	if(rc1=pthread_create(&thread2, NULL,functionRcv,(void *)clientSocket))
	{
		printf("Thread creation failed: %d\n", rc1);
	}
	pthread_join(thread1, NULL);
	return 0;
}
/*This Function using for sending data from Client to Server
with Multiple access sending and Receiving*/
void *functionSend(void *new)
{
          char message[100];
	int clientSocket,lenstr;
	char name[150],tempname[50],message_rec[100];
          clientSocket = (int)new;
	printf("enter your name:");
	scanf("%s",name);
	strcat(name,": ");
	strcpy(tempname,name);
	while(1)
	{
		fgets(message, 100, stdin);
		lenstr=strlen(message);
		message[lenstr-1]='\0';
		if(strlen(message) > 0)
		{
			strcat(name,message);
			send(clientSocket, name, 100, 0);
			memset(name, 0,150);
			memset(message_rec, 0,100);
			strcat(name,tempname);
		}	
	}
	close(clientSocket);
}
/*This Function using for Receiving data from Server and Display
with Multiple access sending and Receiving*/
void *functionRcv(void *new)
{
          char message_rec[100];
	int clientSocket;
          clientSocket = (int)new;
	while(1)
	{
		recv(clientSocket,message_rec, 100, 0);
		printf("%s\n",message_rec);
	}
}


