/*
 * util.h
 *
 *  Created on: 2017. 4. 24.
 *      Author: misa
 */

#ifndef UTIL_H_
#define UTIL_H_


//void TimeT2ASCDTime(time_t tSrcDTime, char *abDesASCDTime);
//time_t GetTimeTFromASCDtime(char *abSrcASCDtime);
//int GetDWORDFromASC(char *abSrcASC, int bLengthSrc);
void Timet2ASC(time_t tTime, char* abASCTime,int nStart, int nLen);
time_t ASCTime2Timet(char* abASCTime);
int ASC2INT(char* abASC, int nLen);
#endif /* UTIL_H_ */
