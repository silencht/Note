#ifndef __MYSTRING__
#define __MYSTRING__

   /*
      new:先分配 memory,再调用 constructor。new代码会被编译器（一般情况下）转换为三步,例如：
      new代码： 
         Complex *pc = new Complex(1,2);
      转化为：
      1.void * mem = operator new( sizeof(Complex) ); //实际 operator new 操作内部调用 malloc(n)
      2.pc = static_cast<Complex*>(mem); //转型并赋给 pc
      3.pc->Complex::Complex(1,2); //构造函数

      delete:先调用 deconstructor，再释放 memory。delete代码会被编译器转为 4.5.两步，例如：
      代码： 
         String* ps = new String("Hello"); 
         delete ps;
      转化为：
      首先：（本头文件所定义的）String类型是一个指向字符串内存空间的一个字符指针。
      1.new创建一个字符指针大小的空间;
      2.将该空间的地址转型并赋值给 ps;
      3.ps(一个 String对象指针)调用 (String的)构造函数，该构造函数又 new了一个6char大小(5个字符和一个结束符)的空间
        并将地址赋值给 ps所指对象的 m_data 成员;
      4.String::~String(ps); //调用析构函数，释放 ps所指对象的 m_data成员所指的(6char大小的)空间。
        其中，array new 一定要搭配 array delete使用，因为如果 delete不加[]，那么只会唤起一次 deconstructor,
        在 class with pointer members情形下,会造成除首元素指针外的其他指针不调用析构函数,从而引起内存泄漏;
      5.operator delete(ps); //释放内存(实际内部调用free(ps)函数 )，释放 ps本身所占的空间;

   */

class String
{
public:                                 
   String(const char* cstr = 0);                    
   String(const String& str);  //接受参数类型为自身相同类型：拷贝构造          
   String& operator=(const String& str);  //操作符重载，接受参数类型为自身相同类型：拷贝赋值
   ~String(); //析构函数   拷贝构造+拷贝赋值+析构函数 在技术书籍中又称为 Big Three
   char* get_c_str() const { return m_data; } //得到 c风格字符串
private:
   char* m_data;
};

#include <cstring>

inline
String::String(const char* cstr)
{
   if (cstr) {
      m_data = new char[strlen(cstr)+1]; //为字符串开辟内存空间，其中的+1是为字符串尾部结束符'\0'预留位置
      strcpy(m_data, cstr);
   }
   else {   
      m_data = new char[1];
      *m_data = '\0';
   }
}

inline
String::~String()
{
   delete[] m_data; //释放动态分配的内存，否则会造成内存泄漏
}

inline
String& String::operator=(const String& str)
{
   /*
     检测自我赋值，若无此判断，在发生自己给自己(都指向都一个对象的指针(无论它们名字相同与否))赋值的情况下,
     直接 delete[]左值内存之后,因为要给左值赋值的右值同样指向了这块内存,相当于提前将右值的内存释放
   */
   if (this == &str) 
      return *this;

   delete[] m_data;
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
   return *this;

   //由 <<C++ Primer 5th>> 13.2.1节启发，本函数体代码或许还可以这么写：
   /*
   auto m_data_extra = new char[ strlen(str.m_data) + 1 ]; //拷贝一份右值的副本,先为副本申请一个相同大小的空间
   strcpy(m_data_extra, str.m_data); //将右值的内容拷贝至副本空间中
   delete[] m_data; //释放左值内存
   m_data = new char[ strlen(str.m_data) + 1 ]; //再为左值申请一份相同大小的空间
   strcpy(m_data, m_data_extra); //将右值原来保存的副本拷贝给左值
   return *this; //返回本对象
   */
}

inline
String::String(const String& str)
{
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
}

#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const String& str)
{
   os << str.get_c_str();
   return os;
}

#endif
