/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_class.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 00:21:59
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/

#include <iostream>
using namespace std;

template <class T>
inline T square(T x)
{
   T result;
   result = x * x;
   return result;
};

// Ä£°åÌØÊâ»¯
template <>
string square<string>(string ss)
{
   return (ss+ss);
};

main()
{
   int i = 2, ii;
   string ww("Aaa");

   ii = square<int>(i);
   cout << i << ": " << ii << endl;

    cout << square<string>(ww) << endl;
}
