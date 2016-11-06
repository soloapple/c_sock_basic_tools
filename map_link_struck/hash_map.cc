/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: hash_map.cc
 * Description: i
 *     Version: 1.0
 *     Created: soloapple   10/03/16 10:30:40
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/03/16                  build this moudle  
 ***************************************************************************************/

#include <ext/hash_map>
#include <string>
#include <iostream>
#include <map>
#include <tr1/unordered_map>
#include <sys/time.h>
#include <cassert>

using namespace std;
using __gnu_cxx::hash_map;

//define the class
class ClassA{
        public:
        ClassA(int a):c_a(a){}
        int getvalue()const { return c_a;}
        void setvalue(int a){c_a;}
        private:
        int c_a;
};

//1 define the hash function
struct hash_A{
        size_t operator()(const class ClassA & A)const{
                //  return  hash<int>(classA.getvalue());
                return A.getvalue();
        }
};

//2 define the equal function
struct equal_A{
        bool operator()(const class ClassA & a1, const class ClassA & a2)const{
                return  a1.getvalue() == a2.getvalue();
        }
};

void exam()
{
	__gnu_cxx::hash_map <ClassA, string, hash_A, equal_A> hmap;
	ClassA a1(12);
	hmap[a1]="I am 12";
	ClassA a2(198877);
	hmap[a2]="I am 198877";

	cout<<hmap[a1]<<endl;
	cout<<hmap[a2]<<endl;
}

int main()
{
	__gnu_cxx::hash_map <const char*, const char*> hp;
	hp["hello"] = "1234";
	hp["world"] = "4567";
	hp["hello1"] = "12341";
	hp["hello2"] = "12342";
	hp["hello3"] = "12343";
	hp["hello4"] = "12344";
	hp["hello5"] = "12345";
	hp["hello6"] = "12346";
	hp["hello7"] = "12347";
	hp["hello8"] = "12348";
	hp["hello9"] = "12349";

	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);

	hash_map<const char*, const char*>::iterator i;
	int times;
	for(times=0;times<20000000;times++)
	{
		i = hp.find("hello");
		assert(i != hp.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';

		i = hp.find("hello9");
		assert(i != hp.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';
	}

	gettimeofday(&end, NULL);
	timer=1000000*(end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec);
	printf ( "timer=%ld us\n", timer );

	return 0;
}

