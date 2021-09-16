//
// Created by Sea on 2021/9/15.
//

#ifndef EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP
#define EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP

#include <iostream>
//条款41:了解隐式接口和编译器多态

//例子1:了解显示接口和隐式接口
class Cl41_Widget{
public:
    virtual void
    Show() =0;
    virtual
    ~Cl41_Widget(){}
};

class Cl41_ScWin: public Cl41_Widget{
public:
     void
     Show() override
     {std::cout<<"Cl41_ScWin::Show\n";}
};
class Cl41_BcWin: public Cl41_Widget{
public:
    void Show()
    override
    {std::cout<<"Cl41_BcWin::Show\n";}
};

//运行时多态：依赖virtual函数来实现
void
Cl41_test01()
{

    Cl41_Widget*p1 = new Cl41_ScWin();
    Cl41_Widget*p2 = new Cl41_BcWin();
    p1->Show();
    p2->Show();
    delete p1;
    delete p2;
}

//编译时多态:通过模板具现化和函数重载解析实现
template<typename T>
void
Cl41_DoProcessing(T& w)
{
    w.Show();
}
void
Cl41_test02()
{
    Cl41_ScWin sc1;
    Cl41_ScWin sc2;
    Cl41_BcWin bc1;

    Cl41_DoProcessing(sc1);
    Cl41_DoProcessing(sc2);
    Cl41_DoProcessing(bc1);
}

/*  运行期多态与编译期多态优缺点:
 *运行期多态优点:
 * 1.OO设计中的重要特性,对客观世界的直觉认识。
 * 2.能够处理同一个继承体系下的异类集合。
 *运行期多态的缺点:
 * 1.运行期进行虚函数绑定，提高了程序运行开销
 * 2.庞大的类继承层次，对接口的修改容易影响类继承层次
 * 3.由于虚函数在运行期才确定，所以编译器无法对虚函数进行优化。
 * 4.虚函数表指针增大对象体积，类也多了一张虚函数表，这是理所当然的资源消耗。
 *编译期多态优点:
 * 1.泛型编程的体现，使得C++拥有泛型编程和STL的强大库
 * 2.在编译期完成多态，提高运行效率
 * 3.具有很强的适配性和松耦合性，对于特殊类型可由模板偏特化和全特化来处理
 *编译期多态缺点:
 * 1.程序可读性降低，代码调试困难度增加
 * 2.无法实现模板分离编译，当工程量大的时候，会极大的增加编译时间
 * 3.无法处理异质对象集合。
 */

/*重点记住:
 *  1.classes和template都支持接口和多态。
 *  2.对于classes而言接口时显式的，以函数签名为中心。多态则是通过virtual函数发生于运行期。
 *  3.对于template参数而言，接口是隐式的，基于有效表达式实现。多态则是通过template具现化和函数
 *重载解析发生于编译期。
 */



#endif //EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP
