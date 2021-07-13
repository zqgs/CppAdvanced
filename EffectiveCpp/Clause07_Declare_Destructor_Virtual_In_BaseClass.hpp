//
// Created by Sea on 2021/7/9.
//

#ifndef EFFECTIVECPP_CLAUSE07_DECLARE_DESTRUCTOR_VIRTUAL_IN_BASECLASS_HPP
#define EFFECTIVECPP_CLAUSE07_DECLARE_DESTRUCTOR_VIRTUAL_IN_BASECLASS_HPP

#include <iostream>
#include <string.h>
//条款07：为多态基类声明virtual析构函数
//C++多态(工厂模式实现):
class Timekeeper{
public:
    Timekeeper(){}
    virtual ~Timekeeper(){ std::cout<<"Timekeeper:析构已完成"<<std::endl;}
    virtual void Timer(){std::cout<<"Timekeeper::Timer\n";}
};
//原子钟
class AtomicClock: public Timekeeper{
    void Timer() override {std::cout<<"AtomicClock::Timer\n";}
public:
    AtomicClock(){
        p = new char[8];
        memcpy(p,"hello",strlen("hello"));
        std::cout<<"AtomicClock:p构造已完成,值:"<<p<<std::endl;
    }
    ~AtomicClock(){
        delete p;
        p= nullptr;
        std::cout<<"AtomicClock:p析构已完成"<<std::endl;
    }
private:
    char *p;
};
//水钟
class WaterClock: public Timekeeper{void Timer() override {std::cout<<"WaterClock::Timer\n";}};
//腕表
class WristWatch: public Timekeeper{};
//工厂模式调用 -->C++多态
void factory()
{
    Timekeeper *tk = dynamic_cast<Timekeeper*>(new AtomicClock());
    tk->Timer();

    //释放资源,依赖客户执行delete动作，基本上就带有某种错误倾向
    //此处只执行了基类析构，并不会执行派生类析构
    //如果在派生类析构做了资源释放，可能会引发内存泄漏。
    //解决办法:将基类的析构设为virtual函数.析构顺序是有派生类开始，基类结束
    delete tk;
}

//virtual函数的目的:允许派生类的实现得以客制化。
//如果一个类不含virtual，通常表示它不想被用来当作基类。如果不是基类使用虚析构函数通常会很糟糕
//当class内至少含一个virtual函数时，才为该class声明virtual析构函数

//当一个类没有任何纯虚函数时，又想该类是抽象<abstract>的。可以将析构声明为纯虚函数
class AWOV{
public:
    virtual ~AWOV() = 0;//给基类一个虚析构函数，该规则只适用于带多态性质的基类上
};
AWOV::~AWOV()
{
    //<需为纯虚函数提供一份定义,因为最终该析构会被执行>
}


/*深入理解虚函数的继承-->继承 = 复制
 *————————————————————————————————————————————————————————————————————————————————————————————————————————
 *|                                          Timekeeper
 *|———————————————————————————————————————————————————————————————————————————————————————————————————————
 *|                                         +Timer():void
 *————————————————————————————————————————————————————————————————————————————————————————————————————————
 *                                                ||继
 *                                                ||承
 *—————————————————————————————————————————————————————————————————————————————————————————————————————————
 *| WristWatch(无虚函数继承)                               WaterClock、AtomicClock(虚函数继承)
 *|—————————————————————————————————————————————————————|——————————————————————————————————————————————————
 *|+Timer1():void(复制了Timekeeper::Timer产生了新的地址)   +Time():void(还是使用了Timekeeper::Timer的地址)
 *——————————————————————————————————————————————————————————————————————————————————————————————————————————
 *无虚函数继承继承的虚函数表:|Timekeeper::Timer()|WristWatch::Timer()——————>此时有两个虚函数地址(地址相互无关联)
 *——————————————————————————————————————————————————————————————————————————————————————————————————————————
 *虚函数继承继承的虚函数表:WristWatch::Timer()————————>此时Timekeeper/WristWatch共用一个虚函数地址(地址相互关联)
 *——————————————————————————————————————————————————————————————————————————————————————————————————————————
 */


/*重点记住:
 * 带多态性质的基类应该声明一个virtual析构函数。如果class带有任何的virtual函数，它就应该拥有一个virtual析构函数
 * classes的设计目的如果不是作为基类使用，或不是为了具备多态性，就不该声明virtual函数
 */



#endif //EFFECTIVECPP_CLAUSE07_DECLARE_DESTRUCTOR_VIRTUAL_IN_BASECLASS_HPP
