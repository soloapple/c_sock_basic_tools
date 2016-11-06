/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_class_main.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 01:20:10
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/


#include <iostream>

#include "template_class.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    Matrix2x2<int> X(1,2,3,4);
    Matrix2x2<int> Y(5,6,7,8);

    cout << "X:" << endl;
    X.Print();

    cout << "Y:" << endl;
    Y.Print();

    Matrix2x2<int> A = X.Add(Y);
    cout << "A:" << endl;
    A.Print();

    Matrix2x2<int> B = X.Multiply(Y);
    cout << "B:" << endl;
    B.Print();
}
          


