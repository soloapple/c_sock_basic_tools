/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: map.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   10/13/16 10:01:26
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/13/16                  build this moudle  
 ***************************************************************************************/

#include <map>
#include <iostream>
#include <cassert>
#include <string>
#include <sys/time.h>

using namespace std;

int main(int argc, char **argv)
{
	std::map<string, string> m;
	m["hello"] = "1234";
	m["world"] = "4567";
	m["hello1"] = "12341";
	m["hello2"] = "12342";
	m["hello3"] = "12343";
	m["hello4"] = "12344";
	m["hello5"] = "12345";
	m["hello6"] = "12346";
	m["hello7"] = "12347";
	m["hello8"] = "12348";
	m["hello9"] = "12349";

//	if (m.find("world") != m.end())
//		std::cout << "map contains key world!\n";

//	std::cout << m["hello"] << '\n';

	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);

	std::map<string, string>::iterator i;
	int times;
	for(times=0;times<20000000;times++)
	{
		i= m.find("hello");
		assert(i != m.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';

		i = m.find("hello9");
		assert(i != m.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';
	}

	gettimeofday(&end, NULL);
	timer=1000000*(end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec);
	printf ( "timer=%ld us\n", timer );

	return 0;
}

