/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_class3.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 00:31:30
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/

#include <iostream>
using namespace std;


/* ----- typename is better than class, but both work. ----- */
//目前这样是编译不过去的，因为函数模板里不能有默认值，但是类模板里能有。
//<typename T=float, int count=3>
template <class T=float, int count=3>
T multIt(T x)
{
   for(unsigned int ii=0; ii<count; ii++)
   {
       x = x * x;
   }
   return x;
};

main()
{
   float xx = 2.1;

   cout << xx << ": " << multIt<>(xx) << endl;;
}
