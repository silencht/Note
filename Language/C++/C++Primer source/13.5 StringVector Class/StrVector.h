#ifndef STRVECTOR
#define STRVECTOR
 
#include<string>
#include<memory>
#include<utility>  //std::pair
#include<algorithm>

class StrVec
{
public:
	//constructor
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string> str_vec); 
    //Big Three
	StrVec(const StrVec&); 
	StrVec& operator=(const StrVec&); 
	~StrVec();
	//member functions
	void pushback(const std::string&);
	void reverse(size_t);
	void resize(size_t, const std::string &str = std::string(""));
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	//iterator
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }

private:
    //创建可以分配string的allocator对象,来获得原始内存 
	static std::allocator<std::string> alloc;   
    //chk_n_alloc保证StrVec至少有容纳一个新元素的空间。如果没有空间添加新元素，它会调用reallocate来分配更多内存
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    //alloc_n_copy会分配内存，并拷贝一个给定范围中的元素
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*); 
    //free会销毁构造的元素并释放内存
	void free();
	void alloc_n_move(size_t);
    //reallocate在内存用完时为StrVec分配新内存
	void reallocate();

	std::string* elements; //指向分配的内存中的首元素
	std::string* first_free; //指向最后一个实际元素之后的位置
	std::string* cap; //指向分配的内存末尾之后的位置
};

std::allocator<std::string> StrVec::alloc;   
void StrVec::free()
{
	if (elements)
	{
		/*for (auto i = first_free; i != elements;)
			alloc.destroy(--i);*/
		std::for_each(elements, first_free,     //this is better since no worry about the order
			[](std::string &s) {alloc.destroy(&s); });
		alloc.deallocate(elements, capacity());
	}
}
 
StrVec::StrVec(std::initializer_list<std::string> str_vec)  //实际上，本来StrVec内部实现就是动态分配管理 应该要分配
{
	auto newdata = alloc_n_copy(str_vec.begin(), str_vec.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::StrVec(const StrVec &v)
{
	auto newdata = alloc_n_copy(v.begin(), v.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::~StrVec()
{
	free();
}
StrVec& StrVec::operator=(const StrVec &v)
{
	auto newdata = alloc_n_copy(v.begin(), v.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}
 
std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
	auto newdata = alloc.allocate(e - b);
	return { newdata,std::uninitialized_copy(b,e,newdata) };
}
void StrVec::alloc_n_move(size_t newcapacity)   //由于需要多次分配内存，所以将其写成独立函数，reallocate只是传参给此函数而已
{
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));  //使用移动构造函数，因为拷贝是不必要的，会释放原来的内存
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	alloc_n_move(newcapacity);
}
void StrVec::pushback(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void StrVec::reverse(size_t newcapacity)
{
	if (newcapacity <= size())
		return;
	alloc_n_move(newcapacity);
}
void StrVec::resize(size_t num, const std::string &str)
{
	if (num > size())
	{
		if (num > capacity())
			alloc_n_move(num);
		for (size_t i = size(); i != num; ++i)
			alloc.construct(first_free++, str);
	}
	else if (num <= size())
	{
		while (first_free != elements + num)
			alloc.destroy(--first_free);
	}
}
#endif 