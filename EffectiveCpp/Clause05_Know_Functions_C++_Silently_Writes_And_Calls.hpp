//
// Created by Sea on 2021/7/6.
//

#ifndef EFFECTIVECPP_CLAUSE05_KNOW_FUNCTIONS_C__SILENTLY_WRITES_AND_CALLS_HPP
#define EFFECTIVECPP_CLAUSE05_KNOW_FUNCTIONS_C__SILENTLY_WRITES_AND_CALLS_HPP

#include <string>

//条款05:了解C++默默编写并调用了哪些函数
//Empty Class(空类):会默认产生default构造函数、Copy构造函数、析构函数、拷贝赋值操作符等

//class Empty{};等价于
class Empty{
public:
    Empty(){}//默认构造函数
    Empty(const Empty& rhs){}//拷贝构造函数
    ~Empty(){}//析构函数
    Empty& operator=(const Empty&rhs){}//拷贝赋值操作符
};
//当这些函数被需要时就会被编译器创建
//如:Empty e1;(创建默认构造、析构函数) Empty e2(e1);//拷贝构造函数  e2=e1;拷贝赋值



//当声明了构造函数后，编译器不再创建默认构造函数
template <class T>
class NamedObject{
public:
    NamedObject(const char* name,const T& value);
    NamedObject(const std::string& name,const T& value);

    //未声明copy构造与copy赋值操作符--编译器会自动创建
    //例:NamedObject<int> no1("hello world",2);
    //NamedObject<int> no2(no1);//调用默认拷贝构造函数
private:
    std::string nameValue;
    T objectValue;
};

//如果base classes将copy赋值操作符声明为private，编译器将拒绝为其派生类生成拷贝赋值操作符

/*重点记住:
 * 编译器可以暗自为class创建默认构造函数、拷贝构造函数、拷贝赋值操作函数以及析构函数
 */





#endif //EFFECTIVECPP_CLAUSE05_KNOW_FUNCTIONS_C__SILENTLY_WRITES_AND_CALLS_HPP
