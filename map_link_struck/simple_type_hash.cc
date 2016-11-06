/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: simple_type_hash.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   10/13/16 14:39:10
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/13/16                  build this moudle  
 ***************************************************************************************/

#include <ext/hash_map>
#include <iostream>
#include <cassert>
#include <sys/time.h>

using namespace std;
using namespace __gnu_cxx;

	void 
HashIntInt()
{
	hash_map<int, int>IntHash;
	IntHash[1] = 123;
	IntHash[2] = 333;
	int val1 = IntHash[1];
	int val2 = IntHash[2];

	cout << "1:" << val1 << endl;
	cout << "2:" << val2 << endl;
}

	void
HashCharInt()
{
	hash_map<const char*, int>CharHash;
	CharHash["a"] = 123;
	CharHash["b"] = 456;

	char szInput[64] = "";
	scanf("%s", szInput);
	int val=CharHash[szInput];

	cout << "a:" << CharHash["a"] << endl;
	cout << val << endl;
}

struct str_hash{
    size_t operator()(const string& str) const {
        return __stl_hash_string(str.c_str());
    }
};
 
struct compare_str {
    bool operator()(const string& str1,const string& str2) const{
        return str1 == str2;
    }
};
 
	void
HashString()
{
    hash_map<string, string, str_hash, compare_str> HashString;
    hash_map<string, string, str_hash, compare_str>::iterator it, itb;
	
	HashString["hello"] = "1234";
	HashString["world"] = "4567";
	HashString["hello1"] = "12341";
	HashString["hello2"] = "12342";
	HashString["hello3"] = "12343";
	HashString["hello4"] = "12344";
	HashString["hello5"] = "12345";
	HashString["hello6"] = "12346";
	HashString["hello7"] = "12347";
	HashString["hello8"] = "12348";
	HashString["hello9"] = "12349";

//    HashString.insert(pair("hello10", "world10"));
    HashString.insert(make_pair("hello11", "world11"));
// 
    it = HashString.find("hello");
    cout<<"IntPassion -> "<<HashString["hello"] << endl;
// 
//    for(itb = HashString.begin(); itb!= HashString.end(); itb++)
//        cout<<itb->first<<" -> "<<itb->second<<endl;

	int times;
	unsigned long timer;
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	for(times=0;times<20000000;times++)
	{
		itb= HashString.find("hello");
		assert(itb != HashString.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';

		itb = HashString.find("hello9");
		assert(itb != HashString.end());
//		std::cout << "Key: " << i->first << " Value: " << i->second << '\n';
	}

	gettimeofday(&end, NULL);
	timer=1000000*(end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec);
	printf ( "timer=%ld us\n", timer );

}

	int
main ( int argc, char *argv[] )
{
	HashString();

	return 0;
}				

				
