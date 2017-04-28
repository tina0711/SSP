/*
 * util.h
 *
 *  Created on: 2017. 4. 21.
 *      Author: LGCNS
 */

#ifndef UTIL_H_
#define UTIL_H_
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void Timet2ASC(time_t tTime, char* abASCTime,int nStart, int nLen);
time_t ASCTime2Timet(char* abASCTime);
time_t ASCDate2Timet(char* abASCDate);
int ASC2INT(char* abASC, int nLen);

#endif /* UTIL_H_ */

