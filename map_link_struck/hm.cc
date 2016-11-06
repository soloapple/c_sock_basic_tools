/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: hm.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   10/13/16 13:45:32
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   10/13/16                  build this moudle  
 ***************************************************************************************/
#include<ext/hash_map>
#include<iostream>
using namespace std;
using __gnu_cxx::hash_map;

int main(void)
{
	hash_map<const char*,float>hm;
	hm["apple"]=1.0f;
	hm["pear"]=1.5f;
	hm["orange"]=2.0f;
	hm["banana"]=1.8f;

	hash_map<const char*,float>::iterator i,iend,j;
	iend=hm.end();
	for(i=hm.begin();i!=iend;i++)
	{
		cout<<(*i).first<<"   "
			<<(*i).second<<endl;
	}

	cout<<"**************************************************"<<endl;
	hm.erase("pear");
	for(i=hm.begin();i!=iend;i++)
	{
		cout<<(*i).first<<"   "
			<<(*i).second<<endl;
	}

	j=hm.find("pear");
	i=hm.find("apple");
	cout<<"pruit"<<(*i).first<<"  "
		<<"price"<<(*i).second<<endl;
	cout<<"**************************************************"<<endl;
	if(j!=hm.end())
	{
		cout<<"hash_map num:"<<hm.size()<<endl;
	}
	else
	{
		cout<<"table length:"<<hm.bucket_count()<<endl;
	}
	return 0;
}


