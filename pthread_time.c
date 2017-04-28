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
#include<time.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

void* readTime(void *arg);

int main(int argc, char*argv[])
{

	pthread_t thread;
	void* status=0;
	pthread_create(&thread, NULL, readTime, NULL);

	pthread_join(thread, &status);
	printf("THREAD END!!\n");
	return 0;

}
void* readTime(void *arg)
{
	time_t tStartTime=0;
	time_t tEndTime=0;
	int nDiff=0;

	time(&tStartTime);
	printf("tStartTime = %d\n", tStartTime);

	while(1)
	{
		time(&tEndTime);
		nDiff = tEndTime-tStartTime;

		if(nDiff > 2*60)
		{
			printf("TIME OVER!!\n");
			break;
		}

	}
	printf("BYE!!\n");
}
