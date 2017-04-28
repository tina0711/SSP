/*
 * goodsList.c
 *
 *  Created on: 2017. 4. 13.
 *      Author: LGCNS
 */
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>
#include<math.h>
#include "./goodsList.h"
#include "./util.h"
#include<string.h>
GList *list =NULL;

static void _free_fun(gpointer data)
{
	if(data)
		free(data);
}
gint sorter(gconstpointer a, gconstpointer b, gpointer data)
{
	return strcasecmp(((GOODS_INFO*)a)->abName, ((GOODS_INFO*)b)->abName);
}

void addGoods(GOODS_INFO inputGoods)
{
	GOODS_INFO *newGoods;
	newGoods =(GOODS_INFO*)malloc(sizeof(GOODS_INFO));
	memset(newGoods,0x00,sizeof(GOODS_INFO));
	memcpy(newGoods, &inputGoods, sizeof(GOODS_INFO));
	list = g_list_append( list, newGoods);

	FILE * file;

	file = fopen("goodslist.txt","ab+");

	if(file)
	{
		fwrite(newGoods,sizeof(GOODS_INFO),1, file);
		fclose(file);
	}

}
void deleteGoods(char* abName)
{
	GList* curr;
	for(curr = list; curr!= NULL; curr= curr->next)
	{
		if(memcmp(((GOODS_INFO*)curr->data)->abName, abName, sizeof(((GOODS_INFO*)curr->data)->abName))==0)
		{
			list= g_list_delete_link( list, curr );
			break;
		}

	}

}
void searchGoods(char* abName)
{
	GList* curr;
	for(curr = list; curr!= NULL; curr= curr->next)
	{
		if(memcmp(((GOODS_INFO*)curr->data)->abName, abName, sizeof(((GOODS_INFO*)curr->data)->abName))==0)
		{
			printGoodsRecord((GOODS_INFO*)curr->data);
			break;
		}

	}

}
void sortGoodsbyName()
{
	list =g_list_sort(list, (GCompareDataFunc)sorter);

}

void updateGoods(char* abName,char* abName2)
{
	GList* curr;
	for(curr = list; curr!= NULL; curr= curr->next)
	{
		if(memcmp(((GOODS_INFO*)curr->data)->abName, abName,sizeof(((GOODS_INFO*)curr->data)->abName))==0)
		{
			memset(((GOODS_INFO*)curr->data)->abName,0x00,sizeof(((GOODS_INFO*)curr->data)->abName));
			memcpy(((GOODS_INFO*)curr->data)->abName,abName2,strlen(abName2));
			break;
		}

	}

}
void loadGoods()
{
	FILE * file;
	int nResult=0;
	char buf[50]={0,};
	int len=0;
	int flag=0;
	char *ptr;
	file = fopen("goodslist.txt","r");

	GOODS_INFO *newGoods;

	if(file)
	{
		do
		{
			newGoods =(GOODS_INFO*)malloc(sizeof(GOODS_INFO));
			memset(newGoods,0x00,sizeof(GOODS_INFO));
			memset(buf, 0x00, 50);
			nResult = fgets(buf, 50, file);
//			memcpy(newGoods, &buf[0], sizeof(GOODS_INFO));

			printf("start\n");
//			printf("newGoods %s\n", newGoods);

			flag =0;
			ptr = strtok(buf, "\t");

			if(ptr)
			{
				memcpy(newGoods->abName, ptr, strlen(ptr)+1);
			}

			while(ptr !=NULL)
			{
				ptr = strtok(NULL, "\t");
				if(ptr)
				{
					if(flag ==0)
					{
						newGoods->nCount = atoi(ptr);
//						printf("%d, %d\n", flag, newGoods->nCount);
					}
					else if(flag ==1)
					{
						newGoods->dPrice = atof(ptr);
//						printf("%d, %.2lf\n", flag, newGoods->dPrice);
					}
					else if(flag ==2)
					{
						newGoods->dDisrate = atof(ptr);
//						printf("%d, %.2lf\n", flag, newGoods->dDisrate);
					}
					else if(flag ==3)
					{
//						printf("%d, %s\n", flag, ptr);
						newGoods->tRegistorDate = ASCTime2Timet(ptr);
					}
					flag++;
				}
			}

			if(nResult == NULL)
			{
				break;
			}
			list = g_list_append( list, newGoods);

		}
		while(nResult != 0);

	}

	if(file)
		fclose(file);
}
void printGoods()
{
	GList* curr;

	for(curr = list; curr!= NULL; curr= curr->next)
	{
		printGoodsRecord((GOODS_INFO*)curr->data);
	}

}
void printGoodsRecord(GOODS_INFO* data)
{
	char abASCTime[15]={0,};
	printf("%.15s\t",data->abName);
	printf("%d\t",data->nCount);
	printf("%.2lf\t",data->dPrice);
	printf("%.2lf\t",data->dDisrate);
	Timet2ASC( data->tRegistorDate,abASCTime, 0, 14);
	printf("%s\n",abASCTime);
}
void destroyGoods()
{
	g_list_free_full(list,_free_fun);

}
int getGoods(GOODS_INFO** goodsList)
{

	int nCount=0;
	int nIndex =0;
	GList* curr;
	for(curr = list; curr!= NULL; curr= curr->next)
	{
		nCount++;
	}
	*goodsList = (GOODS_INFO*)malloc(sizeof(GOODS_INFO)*nCount);

	for(curr = list; curr!= NULL; curr= curr->next)
	{
		memcpy(&(*goodsList)[nIndex++],(GOODS_INFO*)curr->data,sizeof(GOODS_INFO));

	}
	//for(int i = 0; i<sizeof(GOODS_INFO);i++)
	//{

	//}
	return nCount;
}

