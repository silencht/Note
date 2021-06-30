#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__

class complex; 
complex&
  __doapl (complex* ths, const complex& r);
complex&
  __doami (complex* ths, const complex& r);
complex&
  __doaml (complex* ths, const complex& r);

/*
- 什么是一个好的类？
  1.数据一定要放到 private 里面
  2.参数尽可能以 reference 来传 (而不以 value 来传)。要不要加 const ,看状况
  3.返回值也尽可能以 reference 来传
  4.成员函数应该要加 const 的就要加
  5.构造函数要尽量采用初始化列表来进行值的初始化
- 什么时候返回值不该以 reference 来传？
  返回的对象作用域不可以是局部的。比如若以 return by reference 方式来返回函数内部定义的一个局部对象，
  尽管语法都是合理的，但随着程序执行到函数后花括号时，此对象的生命期也随之终结，继而被销毁，对象的本体都已经“死掉”了，
  那么返回这个对象的引用又有何意义呢？
- 一般情况下操作符重载可以根据需要设计成员函数或者非成员函数形式，但是有例外：
  如 << 操作符，只推荐使用非成员函数形式。为什么？
  因为 cout按照习惯一般作为 << 运算符的左侧运算对象。如果当一个重载的运算符<<是成员函数时，this会绑定到左侧运算对象(即cout)。
  然而，当我们把运算符定义成成员函数时，其左侧运算对象必须是重载 <<运算符成员函数所属类的一个对象。cout明显不属于这个类的对象；
  而当将其定义为非成员函数后，左侧运算对象可以传递给参数列表第一个参数，因此左侧运算对象的数据类型可以随意定义(这里定义为ostream& os)，
  此时就可以满足 cout为左侧运算对象的习惯了。
*/
class complex
{
public:
  complex (double r = 0, double i = 0): re (r), im (i) { } //构造函数：数据初始化尽量放到初始化列表
  complex& operator += (const complex&);
  complex& operator -= (const complex&);
  complex& operator *= (const complex&);
  complex& operator /= (const complex&); //参数以 reference 来传，加了 const ，说明只希望读该引用，而不允许写
  double real () const { return re; } //成员函数 不加 const:有可能对数据进行修改 ; 加 const:不会对成员函数进行修改
  double imag () const { return im; }
private:
  double re, im;

  friend complex& __doapl (complex *, const complex&);
  friend complex& __doami (complex *, const complex&);
  friend complex& __doaml (complex *, const complex&);
};



inline complex& //返回参数 complex& 说明最后函数以 by reference形式来接收 return返回的对象（value）。
__doapl (complex* ths, const complex& r) //名称含义：do assignment plus (operator) 即：做 +=
{
  ths->re += r.re;
  ths->im += r.im;
  return *ths; //ths指向调用对象的，*ths解引用之后，即返回对象本身（一个 value）
}
 
inline complex&
complex::operator += (const complex& r) //操作符重载-1：成员函数类型。参数列表里实际隐含了指向 实际调用该操作符的对象 的 this指针
{
  return __doapl (this, r);
}

inline complex&
__doami (complex* ths, const complex& r)
{
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}
 
inline complex&
complex::operator -= (const complex& r)
{
  return __doami (this, r);
}
 
inline complex&
__doaml (complex* ths, const complex& r)
{
  double f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}

inline complex&
complex::operator *= (const complex& r)
{
  return __doaml (this, r);
}
 
inline double
imag (const complex& x)
{
  return x.imag ();
}

inline double
real (const complex& x)
{
  return x.real ();
}

/*
- 操作符重载-2：非成员函数类型。
- 为了对付 client的三种可能用法（若还要其他类型，还要继续续写重载），这里应该开发三个重载函数：
  1.c2 = c1 + c2; 即 复数 + 复数
  2.c2 = c1 + 5;  即 复数 + double
  3.c2 = 7 + c1;  即 double + 复数
- 另外，+=返回complex&引用的原因是相加完的值赋给了左侧的调用者，而 + 运算符相加完后没有位置可放，只能返回函数内
最后结果的拷贝副本。如果返回引用，那么随着函数执行的结束，引用所指向结果的那块内存随之销毁，引用也就失去了意义。
- 返回值： typename()，本质是一个临时对象，因此不可以以 by reference 的方式返回它
*/
inline complex
operator + (const complex& x, const complex& y)
{
  return complex (real (x) + real (y), imag (x) + imag (y));
}

inline complex
operator + (const complex& x, double y)
{
  return complex (real (x) + y, imag (x));
}

inline complex
operator + (double x, const complex& y)
{
  return complex (x + real (y), imag (y));
}

inline complex
operator - (const complex& x, const complex& y)
{
  return complex (real (x) - real (y), imag (x) - imag (y));
}

inline complex
operator - (const complex& x, double y)
{
  return complex (real (x) - y, imag (x));
}

inline complex
operator - (double x, const complex& y)
{
  return complex (x - real (y), - imag (y));
}

inline complex
operator * (const complex& x, const complex& y)
{
  return complex (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

inline complex
operator * (const complex& x, double y)
{
  return complex (real (x) * y, imag (x) * y);
}

inline complex
operator * (double x, const complex& y)
{
  return complex (x * real (y), x * imag (y));
}

complex
operator / (const complex& x, double y)
{
  return complex (real (x) / y, imag (x) / y);
}

inline complex //侯捷老师说，这里实际 by reference 返回值（即 complex&）更好
operator + (const complex& x)
{
  return x;
}

inline complex
operator - (const complex& x)
{
  return complex (-real (x), -imag (x));
}

/*
- 操作符重载-2：非成员函数类型。
- ==的三个重载函数：
  1.c1 == c2;
  2.c1 = 5;
  3.3 = c1;  
*/
inline bool
operator == (const complex& x, const complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const complex& y)
{
  return x == real (y) && imag (y) == 0;
}

inline bool
operator != (const complex& x, const complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const complex& y)
{
  return x != real (y) || imag (y) != 0;
}

#include <cmath>

inline complex
polar (double r, double t)
{
  return complex (r * cos (t), r * sin (t));
}

inline complex
conj (const complex& x) //共轭复数
{
  return complex (real (x), -imag (x));
}

inline double
norm (const complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}

#endif   //__MYCOMPLEX__




