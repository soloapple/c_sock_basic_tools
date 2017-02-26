/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: multimap.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��02��26�� 12ʱ21��32��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��02��26��                  build this moudle  
 *****************************************************************************/
#include <map>
#include <iostream>

using namespace std;

struct student{  
	char* name;  
	int age;  
	char* city;  
	char* phone;  
};  

int main()  
{  
	student s[]=
	{  
		{"ͯ��",23,"�人","XXX"},  
		{"�ϴ�",23,"�人","XXX"},  
		{"����",23,"�人","XXX"},  
		{"���ϻ�",23,"�人","XXX"},  
		{"����",23,"�人","XXX"},  
		{"������",23,"�人","XXX"}  
	};  

	pair<int,student> p1(4,s[0]);  
	pair<int,student> p2(2,s[1]);  
	pair<int,student> p3(3,s[2]);  
	pair<int,student> p4(4,s[3]);  //��ֵkey��p1��ͬ  
	pair<int,student> p5(5,s[4]);  
	pair<int,student> p6(6,s[5]);  

	multimap<int,student> a;  
	a.insert(p1);  
	a.insert(p2);  
	a.insert(p3);  
	a.insert(p4);  
	a.insert(p5);  
	a.insert(p6);  

	typedef multimap<int,student>::iterator int_multimap;  
	pair<int_multimap,int_multimap> p = a.equal_range(4);  
	int_multimap i = a.find(4);  

	cout << "����keyֵΪ" << i->first << "��ѧ���У�" << a.count(4) << "��," << "   ������:" <<endl;  
	for ( int_multimap k = p.first; k != p.second; k++ )  
	{  
		cout << k->second.name << endl;  
	}  

	cout << "ɾ���ظ���ֵ��ͬѧ" << endl;  
	a.erase(i);  
	cout << "���ڰ���������Ϊ��" << a.size() << ".   ��Ա���£�" <<endl;  

	for ( multimap<int,student>::iterator j=a.begin(); j != a.end(); j++ )  
	{        
		cout<<"The name: "<<j->second.name<<"      "<<"age: "<<j->second.age<<"   "  
			<<"city: "<<j->second.city<<"      "<<"phone: "<<j->second.phone<<endl;  
	}  

	return 0;  
  
