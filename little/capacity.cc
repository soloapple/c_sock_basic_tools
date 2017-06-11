/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: capacity.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��06��08�� 23ʱ44��02��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��06��08��                  build this moudle  
 *****************************************************************************/
#include <iostream>  
#include <vector>  
using namespace std;  
   
int main()  
{  
    vector<int> ivec;  

    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  

//���10��Ԫ��  
    for(int i = 0; i < 10; ++i)  
    {  
        ivec.push_back(i);  
        cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
    }  

//����������  
    while(ivec.size() != ivec.capacity())  
        ivec.push_back(0);  

    //���1��Ԫ��  
    cout<<"size = capacity. insert one element\n";  
    ivec.push_back(0);  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    ivec.reserve(100);  
    cout<<"reserve capacity 100\n";  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    //����������  
    while(ivec.size() != ivec.capacity())  
        ivec.push_back(42);  
        //���1��Ԫ��  

    cout<<"size = capacity. insert one element\n";  
    ivec.push_back(0);  
    cout<<"capacity:"<<ivec.capacity()<<"  size:"<<ivec.size()<<endl;  
   
    return 0;  
}  
