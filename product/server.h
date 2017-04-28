/*
 * server.h
 *
 *  Created on: 2017. 4. 21.
 *      Author: misa
 */

#ifndef SERVER_H_
#define SERVER_H_

void* clnt_connection(void * arg);
void send_message(char * message, int clnt_sock, int len);
void error_handling(char * message);
int serverConnect();

#define BUFSIZE 1024

#endif /* SERVER_H_ */
