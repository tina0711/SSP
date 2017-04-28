/*
 * server.c
 *
 *  Created on: 2017. 4. 14.
 *      Author: misa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <glib.h>

#include "./productList.h"
#include "./server.h"


//void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
//{
//	setvbuf(stdout, NULL, _IONBF, 0);
//	setvbuf(stderr, NULL, _IONBF, 0);
//}


int clnt_number=0; int clnt_socks[10];
pthread_mutex_t mutx;

int serverConnect()
{
	 int serv_sock;
	 int clnt_sock;
	 struct sockaddr_in serv_addr;
	 struct sockaddr_in clnt_addr;

	 int clnt_addr_size;
	 pthread_t thread;
//	 if(argc != 2)
//	 {
//		 printf("Usage : %s <port>\n", argv[0]);
//		 exit(1);
//	 }

	 if(pthread_mutex_init(&mutx,NULL))
		 error_handling("mutex init error");

	 serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	 if(serv_sock == -1)
		 error_handling("socket() error");

	 memset(&serv_addr, 0, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	 serv_addr.sin_port = htons(9190); // ��Ʈ �ϵ��ڵ�

	 if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		 error_handling("bind() error");

	 if(listen(serv_sock, 5) == -1)
		 error_handling("listen() error");

	 while(1) {
		  clnt_addr_size = sizeof(clnt_addr);
		  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
		  pthread_mutex_lock(&mutx);
		  clnt_socks[clnt_number++]=clnt_sock;
		  pthread_mutex_unlock(&mutx);
		  pthread_create(&thread, NULL, clnt_connection, (void*) clnt_sock);
		  printf(" IP : %s \n", inet_ntoa(clnt_addr.sin_addr));
	 }
//	 return 0;
}
void *clnt_connection(void *arg)
{
	 int clnt_sock = (int) arg;
	 int str_len=0;
	 char message[BUFSIZE]={0,};
	 PRODUCT *products;
	 int nCount=0;
	 int nIndex=0;
	 int i=0;
	//	memset(message, 0x00, sizeof(message));
	 while((str_len=read(clnt_sock, message, sizeof(message))) != 0 )
	 {

		printf("message %s\n", message);
	    if(memcmp(message, "LIST", strlen("LIST"))==0)
		{
	    	memset(message, 0x00, sizeof(message));
	    	nIndex =0;
	    	nCount = getProducts(&products);
	    	printf("nCount = %d\n", nCount);

	    	for(i=0; i<nCount; i++)
	    	{
	        	memcpy(&message[nIndex], (char*)&products[i], sizeof(PRODUCT));
//	        	for(int j=0; j<sizeof(PRODUCT); j++)
//	        	{
//	        		printf("message[%d] = %02x\n", j, message[j]);
//	        	}
	        	nIndex += sizeof(PRODUCT);
//	        	message[nIndex++]=0x0D;
//	       		message[nIndex++]=0x0A;
	    	}
	        send_message(message, clnt_sock, nIndex);
		}
	 }
	 pthread_mutex_lock(&mutx);
	 for(i=0;i<clnt_number;i++)
	 {
		 if(clnt_sock == clnt_socks[i])
		 {
			 for(;i<clnt_number-1;i++) clnt_socks[i] = clnt_socks[i+1]; break;
		 }
	 }
	 clnt_number--;
	 pthread_mutex_unlock(&mutx);
	 close(clnt_sock);
	 return 0;
}
void send_message(char * message, int clnt_sock, int len)
{
	 pthread_mutex_lock(&mutx);
//	 for(i=0;i<clnt_number;i++)
//		 write(clnt_socks[i], message, len);
	 write(clnt_sock, message, len);
	 pthread_mutex_unlock(&mutx);
}
void error_handling(char * message)
{
	 fputs(message, stderr);
	 fputc('\n',stderr);
	 exit(1);
}



