#ifndef STRVECTOR_H
#define STRVECTOR_H

#include <memory>
#include <string>
#include <initializer_list>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string>);
    //Big Five
    StrVec(const StrVec&); //拷贝构造函数
    StrVec& operator=(const StrVec&); //拷贝赋值运算符
    StrVec(StrVec&&) NOEXCEPT; //移动构造函数
    StrVec& operator=(StrVec&&)NOEXCEPT; //移动赋值运算符
    ~StrVec(); //析构函数

    //添加新元素（首先检查是否还有空间容纳新元素）
    void push_back(const std::string&);
    //size成员返回当前真正在使用的元素的数目
    size_t size() const { return first_free - elements; }
    //capacity成员返回StrVec可以保存的元素的数量
    size_t capacity() const { return cap - elements; }
    //begin和end成员分别返回指向首元素和最后一个构造的元素之后位置的指针
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

    std::string& at(size_t pos) { return *(elements + pos); }
    const std::string& at(size_t pos) const { return *(elements + pos); }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const std::string&);

private:
    //alloc_n_copy会分配一段与给定范围匹配的内存，并拷贝该给定范围中的元素至新内存
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    //free会销毁构造的元素并释放内存
    void free();
    //chk_n_alloc保证 StrVec至少有容纳一个新元素的空间。如果没有空间添加新元素，其会调用reallocate来分配更多内存
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    //reallocate在内存用完时为 StrVec分配新内存
    void reallocate();
    //分配新内存时，使用移动构造的方式来移动元素，提高性能
    void alloc_n_move(size_t new_cap);
    void range_initialize(const std::string*, const std::string*);

private:
    std::string *elements; //指向分配的内存中的首元素
    std::string *first_free; //指向最后一个构造元素之后的位置，即第一个空闲元素的指针
    std::string *cap; //指向分配的内存末尾之后的位置
    static std::allocator<std::string> alloc; //alloc成员会分配未构造的原始内存
};

#endif
