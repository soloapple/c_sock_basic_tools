/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: a.cpp
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/08/16 17:32:09
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/08/16                  build this moudle  
***************************************************************************************/
#include <iostream>
using namespace std;

template<unsigned M, unsigned N> 
void add() 
{ 
  cout<< M+N << endl; 
} 
  
// 指针 
template<const char* C> 
void func1(const char* str) 
{ 
  cout << C << " " << str << endl; 
} 
  
// 引用 
template<char (&R)[9]> 
void func2(const char* str) 
{ 
  cout << R << " " << str << endl; 
} 
  
// 函数指针 
template<void (*f)(const char*)> 
void func3(const char* c) 
{ 
  f(c); 
} 
  
void print(const char* c) { cout << c << endl;} 
char arr[9] = "template";  // 全局变量，具有静态生存期 
  
int main() 
{ 
  add<10, 20>(); 
  func1<arr>("pointer"); 
  func2<arr>("reference"); 
  func3<print>("template function pointer"); 
  return 0; 
}
