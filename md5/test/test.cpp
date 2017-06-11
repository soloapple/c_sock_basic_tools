/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: test.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月08日 22时55分48秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月08日                  build this moudle  
 *****************************************************************************/

/**
 * @file test.cpp
 * @The test file of md5.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Oct 19 2014
 *
 */

#include <iostream>
#include <string>
#include <sys/time.h>
#include "../src/md5.h"

const int TIMES = 10000000;
int len = 512;

using std::cout;
using std::endl;

void printMD5(const string& message) 
{
	cout << "md5(\"" << message << "\") = "
		<< MD5(message).toStr() << endl;
}

int main() 
{
	float time_use=0;
	struct timeval start;
	struct timeval end;

	unsigned long i = 0;
	string part("一");
	string message;

	cout << "Now here DEBUG" << endl;

	do 
	{
		message = message + part;
	} while ( (i++) < len );				

	cout << "message is:" << message.c_str() << endl;

	gettimeofday(&start,NULL);//gettimeofday(&start,&tz);结果一样
	printf("start.tv_sec:%d\n",start.tv_sec);
	printf("start.tv_usec:%d\n",start.tv_usec);

	for ( i = 0 ; i < TIMES ; i++ ) 
	{
		MD5(message).toStr();
	}

	printf ( "%d\n", TIMES );

	gettimeofday(&end,NULL);
	printf("end.tv_sec:%d\n",end.tv_sec);
	printf("end.tv_usec:%d\n",end.tv_usec);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %f\n",time_use);
	printf ( "speed is %f tiao/s, single tiao length is %d\n", TIMES/time_use*1000000, len );

	return 0;
}
