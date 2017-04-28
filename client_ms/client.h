/*
 * client.h
 *
 *  Created on: 2017. 4. 21.
 *      Author: misa
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#define BUFSIZE 1024
#define NAMESIZE 100
void send_message(char *message);
void* recv_message(void* arg);
void error_handling(char * message);
int clientConnect(char *name);

void Timet2ASC(time_t tTime, char* abASCTime,int nStart, int nLen);

typedef struct product
{
	char name[15];
	int count;
	int price;
	double discount;
	time_t date;

} PRODUCT;

#endif /* CLIENT_H_ */
