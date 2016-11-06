/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_static_member.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 04:02:06
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/


#include <iostream>

using namespace std;

template <class T> 
class XYZ
{
public:
    void putPri();
    static T ipub;
private:
    static T ipri;
};

template <class T> 
void XYZ<T>::putPri()
{
    cout << ipri++ << endl;
}

// 静态成员初始化:
template <class T> T XYZ<T>::ipub = 1;
template <class T> T XYZ<T>::ipri = 1.2;

main()
{
    XYZ<int> aaa;
    XYZ<float> bbb;

    aaa.putPri();
    cout << aaa.ipub << endl;
    bbb.putPri();
}


