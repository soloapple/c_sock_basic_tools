/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: map_mix_map.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月24日 10时44分45秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月24日                  build this moudle  
 *****************************************************************************/
#include <map>
#include <iostream>

using namespace std;

int 
main()
{
	map< int, string >temp;
	map< int, map<int,string> >multiMap;

	temp.insert(make_pair(90,"hi"));
	temp.insert(pair<int,string>(100,"maxi"));

	multiMap.insert(make_pair(10, temp));

	multiMap[10][80] = "xiaoyu";
	multiMap[5][30] = "xiaoma";

	map<int,map<int,string> >::iterator multitr;
	map<int,string>::iterator intertr;

	for(multitr=multiMap.begin();multitr!=multiMap.end();multitr++)
	{
		for( intertr=multitr->second.begin(); intertr!=multitr->second.end(); intertr++ )
			std::cout<< multitr ->first<<" "<<intertr->first<<" ("<< intertr -> second <<")"<<endl;
	}

	return 0;
}  

