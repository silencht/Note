#include "string.h"
#include <iostream>

using namespace std;

int main()
{
  /*class with pointer members 必须有 copy constructor 和 copy assignment operator
    不然采用编译器默认的按位拷贝会造成浅拷贝。例如:若没有拷贝赋值的话，s2=s1;这条语句的结果是将s1的指针变量
    [m_data]内的值赋给了s2的指针变量[m_data],此时s2也指向了"hello"这块内存,"world"这块内存没有指针再指向
    它(造成内存泄漏)
  */
  String s1("hello"); 
  String s2("world");

  String s3(s2);
  cout << s3 << endl;
  
  s3 = s1;
  cout << s3 << endl;     
  cout << s2 << endl;  
  cout << s1 << endl;      
}
