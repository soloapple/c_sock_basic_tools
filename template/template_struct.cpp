/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_struct.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/08/16 17:04:43
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/08/16                  build this moudle  
 ***************************************************************************************/
#include <iostream>

using namespace std;

template <class ClassNode>
class temp_struct {
	public:
	temp_struct()
	{
		data = new ClassNode();
	};

	~temp_struct()
	{
	};
	
	void *data;

};				/* ----------  end of struct temp_struct  ---------- */

class ss
{
	public:
	ss(){
		cout << "construct ss" << endl;	
	};	
	~ss(){};	
};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] )
{
	//struct temp_struct ts = new struct temp_struct;
	temp_struct<class ss> *pts = new temp_struct<class ss>;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
