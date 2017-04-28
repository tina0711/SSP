/*
 * productMenu.c
 *
 *  Created on: 2017. 4. 21.
 *      Author: misa
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <pthread.h>
#include "./client.h"

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void requestProductList();
void *StartMenu();
void ShowMenu();

int main(int argc, char **argv)
{
	pthread_t menu_pthread;

	 if(argc != 2){
	  printf("Usage : %s <ip> <port> \n", argv[0]);
	  exit(1);
	 }

	if(pthread_create(&menu_pthread, NULL, StartMenu, NULL)<0)
	{
		printf("thread create error\n");
	}

	clientConnect(argv[1]);

//	pthread_join(menu_pthread, &ret);
	pthread_detach(menu_pthread);

	return 0;
}

void *StartMenu()
{
	int num;
	while(1)
	{
		ShowMenu();
		scanf("%d", &num);
		switch(num)
		{
			case 1:
				printf("requestProductList\n");
				requestProductList();
				break;
			case 2:
				break;
		}
	}
	printf("QUIT\n");
}

void ShowMenu()
{

	printf("*********************\n");
	printf("*         SELECT MENU        *\n");
	printf("*********************\n");
	printf("* 1. PRODUCT LIST             \n");
	printf("* 2. QUIT                            \n");
	printf("*********************\n");

	printf(">>> SELECT MENU : \n");

}

void requestProductList()
{
	send_message("LIST");
}
