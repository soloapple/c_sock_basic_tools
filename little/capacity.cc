/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: capacity.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年06月08日 23时44分02秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年06月08日                  build this moudle  
 *****************************************************************************/
#include <iostream>  
#include <vector>  
using namespace std;  
   
int main()  
{  
    vector<int> ivec;  

    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  

//添加10个元素  
    for(int i = 0; i < 10; ++i)  
    {  
        ivec.push_back(i);  
        cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
    }  

//将容量用完  
    while(ivec.size() != ivec.capacity())  
        ivec.push_back(0);  

    //添加1个元素  
    cout<<"size = capacity. insert one element\n";  
    ivec.push_back(0);  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    ivec.reserve(100);  
    cout<<"reserve capacity 100\n";  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    //将容量用完  
    while(ivec.size() != ivec.capacity())  
        ivec.push_back(42);  
        //添加1个元素  

    cout<<"size = capacity. insert one element\n";  
    ivec.push_back(0);  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    return 0;  
}  
