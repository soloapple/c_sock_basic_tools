/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: macro_for_loop.cc
 * Description: this function is for save.
 *				it only offer one way, to read conf auto by point.
 *     Version: 1.0
 *     Created: soloapple   2017年02月24日 05时35分35秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月24日                  build this moudle  
 *****************************************************************************/
#include <iostream>

using namespace std;
typedef struct snmp
{
	string key;
	string *value;
} snmp_t;

typedef struct conf_snmp {
	string path;
	string ver;	
} conf_snmp_t;			

conf_snmp_t *c_snmp = new conf_snmp_t;

struct snmp xx[] =
{
	{"path", &c_snmp->path},
	{"ver", &c_snmp->ver}
};

int 
main()
{
	size_t i;
	size_t max = sizeof(xx)/sizeof(struct snmp);

	/* path = "./root" */
	string key = "path";
	string value = "./root";

	for ( i=0; i<max; i++ )
	{
		if ( key == xx[i].key)	
		{
			cout << "equal:" << xx[i].key << endl;

			*(xx[i].value) = value;
			break;
		}
	}

	cout << *(xx[i].value) << endl;
	cout << "path:" << c_snmp->path << endl;
	cout << "ver:" << c_snmp->ver << endl;

	delete c_snmp;

	return 0;
}
