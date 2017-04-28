/*
 * util.c
 *
 *  Created on: 2017. 4. 21.
 *      Author: LGCNS
 */

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


