/*
 * util.c
 *
 *  Created on: 2017. 4. 24.
 *      Author: misa
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>
#include "./util.h"

int ASC2INT(char* abASC, int nLen)
{
	char abBuf[256]={0,};
	memcpy(abBuf, abASC, nLen);
	abBuf[nLen]='\0';
	return strtoul(abBuf,NULL,10);

}
void Timet2ASC(time_t tTime, char* abASCTime,int nStart, int nLen)
{
	struct tm timeInfo;
	char abASCTime_temp[15]={0,};

	localtime_r(&tTime,&timeInfo);
	strftime(abASCTime_temp,15,"%Y%m%d%H%M%S",&timeInfo);
	memcpy(abASCTime, &abASCTime_temp[nStart], nLen);
}

//YYYYMMDDHHMMSS ->time_t
time_t ASCTime2Timet(char* abASCTime)
{
	struct tm timeInfo;

	timeInfo.tm_year=ASC2INT(abASCTime, 4)-1900;
	timeInfo.tm_mon=ASC2INT(abASCTime+4, 2)-1;
	timeInfo.tm_mday=ASC2INT(abASCTime+6, 2);
	timeInfo.tm_hour=ASC2INT(abASCTime+8, 2);
	timeInfo.tm_min=ASC2INT(abASCTime+10, 2);
	timeInfo.tm_sec=ASC2INT(abASCTime+12, 2);

	return mktime(&timeInfo);
}
//YYYYMMDD ->time_t
time_t ASCDate2Timet(char* abASCDate)
{
	struct tm timeInfo;

	timeInfo.tm_year=ASC2INT(abASCDate, 4)-1900;
	timeInfo.tm_mon=ASC2INT(abASCDate+4, 2)-1;
	timeInfo.tm_mday=ASC2INT(abASCDate+6, 2);

	return mktime(&timeInfo);

}

//
//void TimeT2ASCDTime(time_t tSrcDTime, char *abDesASCDTime)
//{
//	struct tm *time_ptr;
//	char buf[15] ={0,};
//
//	if(tSrcDTime ==0)
//	{
//		memset(abDesASCDTime, '0', 14);
//		return;
//	}
//
//	time_ptr = localtime(&tSrcDTime);
//	strftime(buf, 15, "%Y%m%d%H%M%S", time_ptr);
//	memcpy(abDesASCDTime, buf, 14);
//}

//time_t GetTimeTFromASCDtime(char *abSrcASCDtime)
//{
//	struct tm time;
//	char buf[4];
//
//	memset(&time, 0x00, sizeof(time));
//
//	if(memcmp(abSrcASCDtime, "00000000000000", 14)==0)
//	{
//		return 0;
//	}
//
//	memcpy(buf, &abSrcASCDtime[0], 4);
//	time.tm_year = GetDWORDFromASC(buf, 4)-1900;
//	memcpy(buf, &abSrcASCDtime[4], 2);
//	time.tm_mon = GetDWORDFromASC(buf, 2)-1;
//	memcpy(buf, &abSrcASCDtime[6], 2);
//	time.tm_mday = GetDWORDFromASC(buf, 2);
//	memcpy(buf, &abSrcASCDtime[8], 2);
//	time.tm_hour = GetDWORDFromASC(buf, 2);
//	memcpy(buf, &abSrcASCDtime[10], 2);
//	time.tm_min = GetDWORDFromASC(buf, 2);
//	memcpy(buf, &abSrcASCDtime[12], 2);
//	time.tm_sec = GetDWORDFromASC(buf, 2);
//
//	return mktime(&time);
//}
