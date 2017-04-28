/*
 * client.c
 *
 *  Created on: 2017. 4. 14.
 *      Author: misa
 */


#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <glib.h>
#include <time.h>
#include "./client.h"


char name[NAMESIZE] = "[Default]";
char message[BUFSIZE];

int sock;

int clientConnect(char *name)
{
	 struct sockaddr_in serv_addr;
	 pthread_t snd_thread, rcv_thread;
	 void* thread_result;

	 sprintf(name, "[%s]", name);
	 sock = socket(PF_INET, SOCK_STREAM, 0);
	 if(sock == -1)
	  error_handling("socket() error");

	 memset(&serv_addr, 0, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	 serv_addr.sin_port=htons(9190);

	 if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	  error_handling("connect() error!");

//	 pthread_create(&snd_thread, NULL, send_message, (void*)sock);
	 pthread_create(&rcv_thread, NULL, recv_message, (void*)sock);

//	 pthread_join(snd_thread, &thread_result);
	 pthread_join(rcv_thread, &thread_result);

	 close(sock);
	 return 0;
}

//void* send_message(void * arg)
void send_message(char *message)
{
//	 int sock = (int) arg;
	 char name_message[NAMESIZE+BUFSIZE]={0,};
//	 while(1){
//		 fgets(message, BUFSIZE, stdin);
//		 if(!strcmp(message, "q\n")) {
//			 close(sock);
//			 exit(0);
//		 }
	 printf("send message\n");
	 sprintf(name_message, "%s", message);
	 write(sock, name_message, strlen(name_message));
//	 }
}

void* recv_message(void* arg)
{
	 int sock = (int) arg;
	 char name_message[NAMESIZE+BUFSIZE]={0,};
	 char abAddProductTime[16]={0,};
	 int str_len=0;
	 int nCount=0;
	 PRODUCT *product[100];
	 int i;
	 int nIndex=0;

	 while(1)
	 {
		 str_len = read(sock, name_message, NAMESIZE+BUFSIZE-1);
		  if(str_len == -1) return (void*)1;
		  name_message[str_len]=0;

//		  fputs(message,stdout);
		  nCount =  str_len/sizeof(PRODUCT);

		  *product = (PRODUCT*)malloc(sizeof(PRODUCT)*nCount);

		  printf("str_len = %d\n", str_len);
		  printf("str_len/sizeof(PRODUCT) = %d\n",  nCount);
//		  for(i =0 ;i< str_len; i++)
//		  {
//			  printf("%c",name_message[i]);
//		  }
		  for(i=0; i<nCount; i++)
		  {
			 memcpy(&(*product)[i], &name_message[nIndex], sizeof(PRODUCT));
			 nIndex += sizeof(PRODUCT);

		     printf("%.15s\t", (*product)[i].name);
		     printf("%d\t", (*product)[i].count);
		     printf("%d\t",(*product)[i].price);
		     printf("%0.2lf\t", (*product)[i].discount);
		     Timet2ASC((*product)[i].date, abAddProductTime,0,14);
		     printf("%s\n", abAddProductTime);
		  }

	 }
}

void error_handling(char * message)
{
	 fputs(message ,stderr);
	 fputc('\n', stderr);
}


void Timet2ASC(time_t tTime, char* abASCTime,int nStart, int nLen)
{
	struct tm timeInfo;
	char abASCTime_temp[15]={0,};

	localtime_r(&tTime,&timeInfo);
	strftime(abASCTime_temp,14,"%Y%m%d%H%M",&timeInfo);
	memcpy(abASCTime, &abASCTime_temp[nStart], nLen);
}


