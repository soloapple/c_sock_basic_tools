#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;

queue <int> q;

typedef struct __mystructdemo
{
	int num;
}mystructdemo, *pmystructdemo;

queue <pmystructdemo> structqueue;

void test_int_queue()
{
	int n;
	cin >> n;

	for(int i=0; i<n; i++)
	{
		q.push(i+1);
	}
	
	cout << "!!--1" << endl;

	while(!q.empty())
	{
		cout << q.front() << " " << endl;
		q.pop();

		if(!q.empty())
			q.push(q.front());

		if(!q.empty())
			q.pop();
	}

	cout << "!!--2" << endl;
}

void test_struct_queue()
{
	int n;
	cin >> n;

	for(int i=0; i<n; i++)
	{
		pmystructdemo pmt = new mystructdemo;
		pmt->num = i;
		structqueue.push(pmt);
	}
	
	cout << "!!--1" << endl;

	while(!structqueue.empty())
	{
		cout << structqueue.front()->num << " " << endl;
		delete structqueue.front();
		structqueue.pop();
	}

	cout << "!!--2" << endl;
}

int main()   
{
	test_struct_queue();
	
	return 0;
}
