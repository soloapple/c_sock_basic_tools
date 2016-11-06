/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: unordered_map.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   10/13/16 10:02:12
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/13/16                  build this moudle  
 ***************************************************************************************/

#include <map>
#include <iostream>
#include <cassert>
#include <tr1/unordered_map>
#include <sys/time.h>

using namespace std;

int main(int argc, char **argv)
{
	std::tr1::unordered_map<string, string> m;
	m["hello"] = "23";
	m["world"] = "4567";
	m["hello1"] = "12341";
	m["hello2"] = "12342";
	m["hello3"] = "12343";
	m["hello4"] = "12344";
	m["hello5"] = "12345";
	m["hello6"] = "12346";
	m["hello7"] = "12347";
	m["hello8"] = "12348";

	//	if (m.find("world") != m.end())
	//		cout << "map contains key world!\n";

	//	cout << m["hello"] << '\n';
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);
	std::tr1::unordered_map<string, string>::iterator i;

	int times;
	for(times=0;times<100000;times++)
	{

		i = m.find("hello");
		assert(i != m.end());
		//	cout << "Key: " << i->first << " Value: " << i->second << '\n';
		i = m.find("hello8");
		assert(i != m.end());
	}

	gettimeofday(&end, NULL);
	timer=1000000*(end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec);
	printf ( "timer=%ld us\n", timer );

	return 0;
}



