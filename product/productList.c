/*
 * server.c
 *
 *  Created on: 2017. 4. 14.
 *      Author: misa
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "./productList.h"
#include "./server.h"
#include "./util.h"

GList* product_list = NULL;
//GList* storage_list = NULL;

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

static void _free_fun(gpointer data)
{
	if(data)
		free(data);
}
gint sorterByPrice(gconstpointer a, gconstpointer b, gpointer data)
{
	return GPOINTER_TO_INT(((PRODUCT*)b)->price)-GPOINTER_TO_INT(((PRODUCT*)a)->price);
}

gint sorterByCount(gconstpointer a, gconstpointer b, gpointer data)
{
	return GPOINTER_TO_INT(((PRODUCT*)a)->count)-GPOINTER_TO_INT(((PRODUCT*)b)->count);
}

gint sorterByName(gconstpointer a, gconstpointer b, gpointer data)
{
	int result;
	result = strcasecmp(((PRODUCT*)a)->name, ((PRODUCT*)b)->name);
    if(result == 0)
    {
    	result = ((PRODUCT*)a)->price  - ((PRODUCT*)b)->price;
    }
	return result;
}

//gint sorterByDiscount(gconstpointer a, gconstpointer b, gpointer data)
//{
//	return GPOINTER_TO_INT(((PRODUCT*)b)->discount)-GPOINTER_TO_INT(((PRODUCT*)a)->discount);
//}

gint sorterByDiscount(gconstpointer a, gconstpointer b, gpointer data)
{
	return GPOINTER_TO_INT(((PRODUCT*)a)->discount)-GPOINTER_TO_INT(((PRODUCT*)b)->discount);
}



gint sorterByDate(gconstpointer a, gconstpointer b, gpointer data)
{
	return GPOINTER_TO_INT(((PRODUCT*)a)->date)-GPOINTER_TO_INT(((PRODUCT*)b)->date);
}

int sortProduct()
{
	int crit=0;

	printf("Sort Criteria (1=name, 2=count, 3=price, 4=discount, 5=date : ");
	scanf("%d", &crit);

	switch(crit)
	{
		 case 1:
			 sortProductsbyPrice();
			 sortProductsbyName();
			 break;
		 case 2:
			 sortProductsbyCount();
			 break;
		 case 3:
			 sortProductsbyPrice();
			 break;
		 case 4:
			 sortProductsbyDiscount();
			 break;
		 case 5:
			 sortProductsbyDate();
			 break;
	}
	return 0;
}
void sortProductsbyName()
{
	product_list =g_list_sort(product_list, (GCompareDataFunc)sorterByName);
}

void sortProductsbyCount()
{
	product_list =g_list_sort(product_list, (GCompareDataFunc)sorterByCount);
}

void sortProductsbyPrice()
{
	product_list =g_list_sort(product_list, (GCompareDataFunc)sorterByPrice);
}

void sortProductsbyDiscount()
{
	product_list =g_list_sort(product_list, (GCompareDataFunc)sorterByDiscount);
}

void sortProductsbyDate()
{
	product_list =g_list_sort(product_list, (GCompareDataFunc)sorterByDate);
}

void loadProduct()
{
	FILE *fp;
	int size=0;
	PRODUCT *product=NULL;

	printf("load Product\n");

	fp = fopen("product.txt", "rb");

	if(fp == NULL)
	{
		printf("File Open Error!\n");
	}
	else
	{

		do
		{
			product = (PRODUCT*)malloc(sizeof(PRODUCT));
			size = fread(product, sizeof(PRODUCT), 1, fp);

			if(size <= 0)
			{
				break;
			}
			product_list = g_list_append(product_list, product);

		}
		while(size>0);

	}

	if(fp)
	{
		fclose(fp);
	}

}

void addProduct()
{
	FILE *fp;
	PRODUCT *product=NULL;
	time_t tNowTime=0;

	printf("add Product\n");

	product= (PRODUCT*)malloc(sizeof(PRODUCT));
	memset(product,0x00,sizeof(PRODUCT)); // Áß¿ä!!!!!!!!!!!!!!!!
	scanf("%s", product->name);
	scanf("%d", &product->count);
	scanf("%d", &product->price);
	scanf("%lf", &product->discount);
//	scanf("%s", product->date);
	tNowTime = time(0);
	product->date = tNowTime;
	product_list = g_list_append(product_list, product);

	fp = fopen("product.txt", "ab+");

	if(fp)
	{
		fwrite(product, sizeof(PRODUCT),1,  fp);
		fclose(fp);
	}
	else
	{
		printf("FILE not exist\n");
	}
}

int getProducts(PRODUCT ** products)
{
	int nCount=0;
	int nIndex=0;
	GList * curr = NULL;

	for(curr = product_list; curr !=NULL; curr = curr->next)
	{
		nCount++;
	}

	*products = (PRODUCT*)malloc(sizeof(PRODUCT)*nCount);


	for(curr = product_list; curr !=NULL; curr = curr->next)
	{
//		printf("PRODUCT= %s\n", ((PRODUCT*)curr->data)->name);
		memcpy(&(*products)[nIndex++], (PRODUCT*)curr->data, sizeof(PRODUCT));
//		printf("products[%d]= %s\n", nIndex-1, (*products)[nIndex-1].name);
	}

	return nCount;
}


int printProductList()
{
	GList*curr=NULL;

	printf("printProductList\n");

    for(curr = product_list; curr != NULL; curr= curr->next)
	{
    	printProductRecord((PRODUCT *)curr->data);
	}

	return 0;
}

int printProductRecord(PRODUCT * data)
{
	char abAddProductTime[15]={0,};

   	printf("%.15s\t", data->name);
   	printf("%d\t", data->count);
   	printf("%d\t", data->price);
   	printf("%0.2lf\t", data->discount);
   	Timet2ASC(data->date, abAddProductTime, 0, 14);
   	printf("%s\n", abAddProductTime);

	return 0;
}


void deleteProduct(char *abName)
{
	char inputName[15] ={0,};
	GList*curr=NULL;
//	FILE *fp;
//	PRODUCT *product=NULL;


	for(curr = product_list; curr != NULL; curr= curr->next)
	{
		if(memcmp(abName, ((PRODUCT *)curr->data)->name, strlen(((PRODUCT *)curr->data)->name))==0)
		{
			printf("[DELETE] %s\n", ((PRODUCT *)curr->data)->name);
			product_list=g_list_delete_link(product_list, curr);
			break;
		}
	}

	if(updateFile()<0)
	{
		printf("file write fail \n");
	}

}

int updateFile()
{
	FILE *fp;
	GList*curr=NULL;
	PRODUCT *product=NULL;
	fp = fopen("product_temp.txt", "ab+");

	if(fp)
	{
		printf("file open\n");

		product =(PRODUCT *)malloc(sizeof(PRODUCT));
		for(curr = product_list; curr != NULL; curr= curr->next)
		{
			printf("write! \n");
			memcpy(product, ((PRODUCT *)curr->data), sizeof(PRODUCT));
			printf("product->name %s\n", product->name);
			fwrite(product, sizeof(PRODUCT),1,  fp);
		}

		fclose(fp);
	}
	else
	{
		printf("FILE not exist\n");
	}

	if(unlink("product.txt")==0)
	{
		printf("file delete OK!\n");
	}
	else
	{
		printf("file delete ERROR!\n");
	}

	if(rename("product_temp.txt", "product.txt")==0)
	{
		printf("file rename OK!\n");
		return 0;
	}
	else
	{
		printf("file rename ERROR!\n");
		return -1;
	}
}



void updateProduct()
{
	char inputName[15] ={0,};
	int inputCount=0;
	GList*curr=NULL;

	printf("Order Product Name : ");
	scanf("%s", inputName);

	printf("Order Product Quantity : ");
	scanf("%d", &inputCount);
	for(curr = product_list; curr != NULL; curr= curr->next)
	{
		if(memcmp(inputName, ((PRODUCT *)curr->data)->name, strlen(((PRODUCT *)curr->data)->name))==0)
		{
			printf("[UPDATE] %s\n", ((PRODUCT *)curr->data)->name);
			((PRODUCT *)product_list->data)->count = inputCount;
			break;
		}
	}

	if(updateFile()<0)
	{
		printf("file write fail \n");
	}
}



void destroyProduct()
{
	g_list_free_full(product_list,_free_fun);

}

