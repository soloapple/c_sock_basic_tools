/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: replace.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年03月03日 21时58分19秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年03月03日                  build this moudle  
 *****************************************************************************/
#include "radio_cross.h"

std::map<int, int>switch_send_type;

void 
test_style_map()
{
	int i = 0;

	int row = 8;
	int col = 3;

	for ( i=0; i<(row*col); i++ )
	{
		switch_send_type[i] = i%2;
		cout << "i:" << switch_send_type[i] << " " << endl;
	}

	cout << switch_send_type[6*2] << endl;
	cout << switch_send_type[6*2+1] << endl;
}
