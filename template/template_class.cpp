/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: template_class.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/10/16 01:07:13
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/10/16                  build this moudle  
 ***************************************************************************************/

#ifndef MATRIX_2X2_HPP__
#define MATRIX_2X2_HPP__

using namespace std;
#include <iostream>

/**
    m(11)  m(12)
    m(21)  m(22)
*/

template <typename T>
class Matrix2x2
{
public:
   Matrix2x2(T m11, T m12, T m21, T m22);    //constructor
   Matrix2x2(T m[2][2]);
   Matrix2x2();

   Matrix2x2<T> Add(Matrix2x2 x);
   Matrix2x2<T> Multiply(Matrix2x2 x);
   void Print();
   T m[2][2];
};

template <typename T>
Matrix2x2<T>::Matrix2x2(T _m11, T _m12, T _m21, T _m22)
{
   m[0][0] = _m11;
   m[0][1] = _m12;
   m[1][0] = _m21;
   m[1][1] = _m22;
}

template <typename T>
Matrix2x2<T>::Matrix2x2(T _m[2][2])
{
   m[0][0] = _m[0][0];
   m[0][1] = _m[0][1];
   m[1][0] = _m[1][0];
   m[1][1] = _m[1][1];
}

template <typename T>
Matrix2x2<T>::Matrix2x2()
{
   m[0][0] = 0;
   m[0][1] = 0;
   m[1][0] = 0;
   m[1][1] = 0;
}

template <typename T>
  Matrix2x2<T> Matrix2x2<T>::Add(Matrix2x2 _x)
{
    Matrix2x2<T> sum;
    sum.m[0][0] = m[0][0] + _x.m[0][0];
    sum.m[0][1] = m[0][1] + _x.m[0][1];
    sum.m[1][0] = m[1][0] + _x.m[1][0];
    sum.m[1][1] = m[1][1] + _x.m[1][1];
    return sum;
}

template <typename T>
 Matrix2x2<T> Matrix2x2<T>::Multiply(Matrix2x2 _x)
{
    Matrix2x2<T> sum;
    sum.m[0][0] = m[0][0] * _x.m[0][0] + m[0][1] * _x.m[1][0];
    sum.m[0][1] = m[0][0] * _x.m[0][1] + m[0][1] * _x.m[1][1];
    sum.m[1][0] = m[1][0] * _x.m[0][0] + m[1][1] * _x.m[1][0];
    sum.m[1][1] = m[1][0] * _x.m[0][1] + m[1][1] * _x.m[1][1];
    return sum;
}

template <typename T>
void Matrix2x2<T>::Print()
{
    cout << "|" << m[0][0] << "  " <<  m[0][1] << "|" << endl;
    cout << "|" << m[1][0] << "  " <<  m[1][1] << "|" << endl;
}

#endif
          

