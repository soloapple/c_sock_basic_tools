/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_class2.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 00:29:28
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/

#include <iostream>
using namespace std;

template <typename T, int count>
void loopIt(T x)
{
	T val[count];

	for(int ii=0; ii<count; ii++)
	{ 
		val[ii] = x++;
		cout <<  val[ii] << endl;
	}
};

main()
{
	float xx = 2.1;

	loopIt<float,3>(xx);
}
