/****************** SERVER CODE ****************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#define MAXI 10



pthread_t thread1[MAXI];
void *function(void *new);

int main(){
	int rc1,t=0,i=0,j=0;
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t addr_size;
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.45.0.2");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if(listen(welcomeSocket,5)==0)
	{
		printf("Listening\n");
	}
	i=0;
	while(1)
	{
		newSocket = accept(welcomeSocket, (struct sockaddr *) &clientAddr, &addr_size);
		perror("accept");
		if(rc1=pthread_create(&thread1[i], NULL,function,(void *)newSocket))
		{
			printf("Thread creation failed: %d\n", rc1);
		}
		i++;
		if(i>=MAXI-1)
			break;
	}
	for(j=0;j<10;j++)
	{
		pthread_join(thread1[j], NULL);
	}
	return 0;
}

void *function(void *new)
{
          char message[100];//Recived message from Clients.
	int newSocket,k,count=9;//Socket name and Total number of Clients is 10.
          newSocket = (int)new;
        	while(1)
        	{
		memset(message,0,100);
		recv(newSocket,message, 100, 0);
		//Given message is send to all clients.
		for(k=4;k<count;k++)
		{
			if(k!=newSocket)
			{
				send(k, message, 100, 0);
			} 
        		}
		printf("ClientDest:%d Message: %s\n",newSocket,message);
		if(strlen(message)==0)
		{
			printf("\nSocket:%d",newSocket);
		    	close(newSocket);
          		perror("Client Exited");
			pthread_exit((void*)newSocket);
			break;
		}
	}
}
