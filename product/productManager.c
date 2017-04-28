/*
 * productManager.c
 *
 *  Created on: 2017. 4. 21.
 *      Author: misa
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <pthread.h>
#include<time.h>

#include "./productList.h"
#include "./server.h"
void *StartMenu();
void ShowMenu();

int main()
{
	pthread_t menu_pthread;
	pthread_t time_pthread;
	loadProduct();

	if(pthread_create(&menu_pthread, NULL, StartMenu, NULL)<0)
	{
		printf("menu_pthread create error\n");
	}


	serverConnect();

//	pthread_join(menu_pthread, &ret);
//	pthread_detach(menu_pthread);

	return 0;
}

void *StartMenu()
{
	int num=0;
	char abBuf[256]={0,};
	char abBuf2[256]={0,};
	while(1)
	{
		ShowMenu();
		memset(abBuf, 0x00, sizeof(PRODUCT));
		memset(abBuf2, 0x00, sizeof(PRODUCT));

		scanf("%d", &num);

		switch(num)
		{
			case 1:
				addProduct();
				break;
			case 2:
				printProductList();
				break;
			case 3:
				printf("Delete Product Name : ");
				scanf("%s", abBuf);
				deleteProduct(abBuf);
				break;
			case 4:
				updateProduct();
				break;
			case 5:
				sortProduct();
				break;
			case 6:
				destroyProduct();
				break;
		}

		if(num==6)
		{
			break;
		}
	}
	printf("QUIT\n");
	exit(1);
}


void ShowMenu()
{

	printf("*********************\n");
	printf("*         SELECT MENU        *\n");
	printf("*********************\n");
	printf("* 1. ADD PRODUCT             \n");
	printf("* 2. PRODUCT LIST             \n");
	printf("* 3. DELETE PRODUCT         \n");
	printf("* 4. UPDATE PRODUCT        \n");
	printf("* 5. SORT PRODUCT            \n");
	printf("* 6. QUIT                            \n");
	printf("*********************\n");

	printf(">>> SELECT MENU : \n");

}
