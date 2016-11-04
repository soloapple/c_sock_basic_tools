/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: test.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/16/16 01:01:56
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/16/16                  build this moudle  
 ***************************************************************************************/

#include "test.h"


Test::Test ()
{
	cout << "construct test" << endl;
}

Test::Test ( const Test &other )
{
	cout << "test?" << endl;
}

Test::~Test ()
{

}

void 
Test::show()
{
	cout << "show " << endl;
}
