/*
 * goodsManager.c
 *
 *  Created on: 2017. 4. 10.
 *      Author: LGCNS
 */

#include<stdio.h>
#include<glib.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

int startProgram()
{
	int cnt=0;
	char ch;

	while(1)
	{
		if(cnt ==5)
		{
			memcpy(ch, "q", 1);
		}
		printf("%d hello\n", cnt);
		sleep(1);
		cnt++;
	}


}
int main()
{
	int pid, status=0;

	while(1)
	{
		pid = fork();

		if(pid <0)
		{
			printf("fork failed with error\n");
			exit(0);
		}
		else if(pid ==0)
		{
			startProgram();
			exit(1);
		}

		waitpid(-1, &status, 0);

		if(WIFEXITED(status))
		{
			printf("normally terminated..exit(%d)\n", WEXITSTATUS(status));
		}
		else
		{
			printf("abnormally terminated..\n");
		}


	}
	exit(0);

}
