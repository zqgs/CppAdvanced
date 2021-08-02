//
// Created by Sea on 2021/7/29.
//

#ifndef EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP
#define EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP


#include <string>
#include <stdexcept>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

/*在程序的实现过程中，需要小心使用东西:
 * 1.过早定义变量可能造成效率上的拖延。
 * 2.过度使用转型(casts)可能导致代码变慢又难维护，又招来微妙难解的错误。
 * 3.返回对象"内部句柄"可能会破坏封装并留给调用者悬空的句柄
 * 4.未考虑异常带来的冲击则可能导致资源泄漏和数据败坏。
 * 5.过度热心地inlining可能引起代码膨胀
 * 6.过度耦合(coupling)则可能导致让人不满意的冗长创建时间(build time)
 */


//条款26:尽可能的延后变量定义式的出现时间
//注:只要定义了变量而其类型带有一个构造函数和析构函数，那么当程序的控制流到达变量定义式时，那
//么必须得承受构造成本，当这个变量离开作用域时，便得承受析构成本。

//例子1：提前声明变量
std::string Cl26_EncryptPassword(const std::string& Password)
{
    using namespace std;
    string _encrypted;
    //抛出异常
    if(Password.length()<5)
        throw logic_error("password is too short");
    _encrypted = Password+"123456";
    return _encrypted;
}
void Cl26_test01()
{
    Cl26_EncryptPassword("1352");
}
//例子2：直至使用前声明变量
std::string Cl26_EncryptPasswordExp1(const std::string& Password)
{
    using namespace std;
    //抛出异常
    if(Password.length()<5)
        throw logic_error("password is too short");
    string _encrypted;
    _encrypted = Password+"123456";
    return _encrypted;
}
void Cl26_test02()
{
    Cl26_EncryptPassword("1352");
}

//例子3:虽然例2不错，但是变量_encrypted拿到值是通过赋值操作符获取到的。条款4提到:构造时指定初值比通过赋值效率更高
void encrypt(std::string& s)
{
    //抛出异常
    if(s.length()<5)
        throw std::logic_error("password is too short");
    s+="123456";
}
std::string Cl26_EncryptPasswordExp2(const std::string& Password)
{
    using namespace std;
    string _encrypted(Password);//拖延变量定义，直到能够给它初值实参为止
    encrypt(_encrypted);
    return _encrypted;
}

//考虑以下在循环中的应用
class Cl26_Widget{};
void Cl26_test03()
{
    //情况一:Cl26_Widget中内含1个构造+1个析构函数+n个赋值操作
    //情况二:Cl26_Widget中内含n个构造+n个析构函数

    //用法1
    Cl26_Widget w1;
    for (int i = 0; i < 10; ++i) {
        //w1=i;
    }

    //用法2
    for (int i = 0; i < 10; ++i) {
        Cl26_Widget w2;
        //w2=i;
    }
   //w1的作用域比w2覆盖更广,有时对程序的可理解性和易维护性造成冲突。
   //1.除非知道用法1的赋值成本比"构造+析构"的成本低，则可以使用用法1，否则则使用用法2
   //2.如果正在处理的代码效率高度敏感部分，否则应该使用用法2
}

/*重点记住:
 * 1.尽可能的延后变量定义式的出现。这样做可增加程序的清晰度并改善程序效率
 */




#endif //EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP
