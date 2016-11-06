/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: main.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/16/16 01:03:38
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/16/16                  build this moudle  
 ***************************************************************************************/

#include "test.h"
#include "data.h"

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

using namespace std;
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

#include "SimpleIni.h"

list<string>g_LogFacilityLocalList;
list<string>g_LogFacilityRemoteList;

string FlagFacilityLocal("local=");
string FlagFacilityRemote("remote=");

static int times;

int
parse_line ( string line )
{
	if ( line.substr(0, FlagFacilityLocal.size()) == FlagFacilityLocal )
	{
		string mode("local0");
		string tt = line.substr(FlagFacilityLocal.size(), line.size());

		stringstream ss(tt);
		string sub_str;
		while(getline(ss,sub_str,','))
		{
			cout << "subis:" << sub_str << endl;
			g_LogFacilityLocalList.push_back(sub_str);
		}

		list<string>::iterator g_mi;
		for(g_mi=g_LogFacilityLocalList.begin();g_mi!=g_LogFacilityLocalList.end();g_mi++)
		{
			cout << "facility:" << *g_mi << " times:" << times++ << endl;
			if(*g_mi == mode)
				cout << "pop" << endl;
		}

		return 1;
	}

	if ( line.substr(0, FlagFacilityRemote.size()) == FlagFacilityRemote )
	{
		string tt = line.substr(FlagFacilityRemote.size(), line.size());

		stringstream ss(tt);
		string sub_str;
		while(getline(ss,sub_str,','))
		{
			cout << "subis:" << sub_str << endl;
			g_LogFacilityRemoteList.push_back(sub_str);
		}

		return 1;
	}

	return 0;
}		

const static char SqlFacilityConf[] = "./config/sql_facility.conf";

/*-----------------------------------------------------------------------------*
 * local=local1,local2...local7 
 * remote=local3,local4...local7
 *-----------------------------------------------------------------------------*/
	int 
LoadFile()
{
	ifstream in;
	in.open(SqlFacilityConf);

	string line;

	while (getline(in, line))
	{
		parse_line(line);	
	}

	return EXIT_SUCCESS;
}

	int 
CutString()
{
	string text = "big|dog|china|sonic|free";

	stringstream ss(text);
	string sub_str;
	while(getline(ss,sub_str,'|'))
		cout << sub_str << endl;

	return 0;
}

	int 
SimpleList()
{
	list<string>m;

	char *s1 = "111";
 	
	m.push_back(s1);
	m.push_back("1");
	m.push_back("2");
	m.push_front("3");
	m.push_front("4");

	list<string>::iterator g_mi;
	for(g_mi=m.begin();g_mi!=m.end();g_mi++)
		cout << *g_mi << endl;

	return 0;
}


const static char SqlLoginConf[] = "./config/sql_login.conf";
const static char c_cFlagSqlLocal[]	= "local";
const static char c_cFlagSqlRemote[] = "remote";
const static char c_cFlagSqlDefault[] = "default";

const static char c_cFlagSqlUser[] = "user";
const static char c_cFlagSqlPassword[] = "password";
const static char c_cFlagSqlHost[] = "host";
const static char c_cFlagSqlDatabase[] = "database";
const static char c_cFlagSqlPort[] = "port";
const static char c_cFlagSqlSock[] = "sock";

int 
LoadSqlLoginConf()
{
	bool bLoadLocal = 0;
	bool bLoadRemote = 0;
	//	LoadFile();
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(SqlLoginConf);

	list<CSimpleIniA::Entry> m;
	ini.GetAllSections(m);

	list<CSimpleIniA::Entry>::iterator g_mi;
	for(g_mi=m.begin();g_mi!=m.end();g_mi++)
	{
		cout << "1" << endl;
		cout << (*g_mi).pItem << endl;

		if (!strncmp((*g_mi).pItem, c_cFlagSqlLocal, strlen(c_cFlagSqlLocal)))
			bLoadLocal = 1;

		if (!strncmp((*g_mi).pItem, c_cFlagSqlRemote, strlen(c_cFlagSqlRemote)))
			bLoadRemote = 1;
	}

	const char * pUser = NULL;
	const char * pPassword = NULL;
	const char * pHost = NULL;
	const char * pDatabase = NULL;
	const char * pPort = NULL;
	const char * pSock = NULL;

	if (bLoadLocal)
	{
		cout << "A" << endl;
		pUser = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlUser, c_cFlagSqlDefault);
	cout << pUser << endl;
		pPassword = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlPassword, c_cFlagSqlDefault);
	cout << pPassword << endl;
		pHost = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlHost, c_cFlagSqlDefault);
	cout << pHost<< endl;
		pDatabase = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlDatabase, c_cFlagSqlDefault);
	cout << pDatabase << endl;
		pPort = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlPort, c_cFlagSqlDefault);
	cout << pPort << endl;
		pSock = ini.GetValue(c_cFlagSqlLocal, c_cFlagSqlSock, c_cFlagSqlDefault);
	cout << pSock << endl;
	}


	if (bLoadRemote)
	{
		cout << "B" << endl;
		pUser = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlUser, c_cFlagSqlDefault);
	cout << pUser << endl;
		pPassword = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlPassword, c_cFlagSqlDefault);
	cout << pPassword << endl;
		pHost = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlHost, c_cFlagSqlDefault);
	cout << pHost<< endl;
		pDatabase = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlDatabase, c_cFlagSqlDefault);
	cout << pDatabase << endl;
		pPort = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlPort, c_cFlagSqlDefault);
	cout << pPort << endl;
		pSock = ini.GetValue(c_cFlagSqlRemote, c_cFlagSqlSock, c_cFlagSqlDefault);
	cout << pSock << endl;
	}


	CSimpleIniA::TNamesDepend keys;
	ini.GetAllKeys("local", keys);

	return EXIT_SUCCESS;
}

map<string, string>g_ModeTableMap; 

void 
ParseTableLine( string line )
{
	stringstream ssModeTable(line);
	string szMode;
	string szTable;

	getline(ssModeTable, szMode,'=');
	getline(ssModeTable,szTable,'=');

	g_ModeTableMap.insert(pair<string,string>(szMode,szTable));
}

const static char SqlTableConf[] = "./config/sql_table.conf";
void
LoadSqlTableConf()
{
	ifstream in;
	in.open(SqlTableConf);

	string line;

	cout << "1" << endl;
	while (getline(in, line))
	{
		cout << "line:" << line << endl;
		ParseTableLine(line);		
//		parse_line(line);	
	}
	
	map<string, string>::iterator ModeTableIterator;
	for(ModeTableIterator = g_ModeTableMap.begin(); ModeTableIterator!=g_ModeTableMap.end(); ++ModeTableIterator)
	{
		cout << "mode:" << ModeTableIterator->first << endl;
		cout << "table:" << ModeTableIterator->second << endl;
	}

	cout << g_ModeTableMap["system"]<< endl;
}

struct datanode
{
	char data[2048];
};

int
main ( int argc, char *argv[] )
{
	datanode *s = new datanode();
	fgets(s->data, 2000, stdin);

	cout << "s:" << s->data << endl;
	return 0;

}				


