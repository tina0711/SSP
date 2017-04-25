/*
 * goodsManager.c
 *
 *  Created on: 2017. 4. 10.
 *      Author: LGCNS
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

#define NUM_THREAD 100

void *thread_inc(void *arg);
void *thread_des(void *arg);
long num=0;
pthread_mutex_t mutex;

int main(int argc, char*argv[])
{

	pthread_t thread_id[NUM_THREAD];
	int i;

//	printf("sizeof long long: %d \n", sizeof(long long));

	pthread_mutex_init(&mutex, NULL);

	for(i=0; i<NUM_THREAD; i++)
	{
		if(i%2)
		{
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		}
		else
		{
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
		}
	}

	for(i=0; i<NUM_THREAD; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	printf("result : %ld\n", num);
	pthread_mutex_destroy(&mutex);
	return 0;

}
void *thread_inc(void *arg)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0; i<10000; i++)
	{
		num+=1;
		printf("%d\n", num);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *thread_des(void *arg)
{
	int i;

	for(i=0; i<10000; i++)
	{
		pthread_mutex_lock(&mutex);
		num -=1;
		printf("%d\n", num);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}
