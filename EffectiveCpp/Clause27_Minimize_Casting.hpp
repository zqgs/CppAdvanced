//
// Created by Sea on 2021/8/2.
//

#ifndef EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP
#define EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP

#include <iostream>
#include <vector>
#include <memory>
//条款27:尽量少做转型动作

//C++规则的设计目标之一是:保证"类型错误"绝不可能发生。

//旧式转型(类C风格)：T(expression)、(T)expression
//新式转型:const_cast<T>(expression)、dynamic_cast<T)(expression)、reinterpret_cast<T>(expression)、static_cast<T>(expression)
/*新式转型解析：
 * const_cast通常被用来去除带const的常量。C++中唯一有此能力的C++style的转型操作符
 * dynamic_cast主要用来执行"向下安全转型"，也就是用来决定某个对象是否归属继承体系中的某个类型。旧式转型无法执行的动作，
 *唯一可能耗费巨大的成本的转型动作
 * reinterpret_cast意图执行低级转型，实际动作取决于编译器，意味着不可移植。例如将pointer to int转型为int等
 * static_cast用来强迫隐式转换，例如将non-const对象转为const对象，将基类指针转为派生类指针等。
 */

/*旧式转型仍然合法，但新式转型更受欢迎:
 * 1.它们很容易在代码中被辨识出来，因而得以简化"找出类型系统在哪个地点被破坏"的过程。
 * 2.各种转型动作的目标越窄，编译器越有可能诊断出错误的运用。例如:打算去掉常量的const，除非使用const_cast否则无法通过编译
 */


//例子1:使用旧式转型的时机
class Cl27_Widget{
public:
    explicit Cl27_Widget(int size){}
};
void Cl27_doSomeWork(const Cl27_Widget& w){}
void Cl27_test01()
{
    //旧式转型
    Cl27_doSomeWork(Cl27_Widget(15));

    //新式转型
    Cl27_doSomeWork(static_cast<Cl27_Widget>(15));
}

//例子2:隐式转换带来的弊端.然而我们并不知道问题所在
class Cl27_Base{};
class Cl27_Derived: public Cl27_Base{};

void Cl27_test02()
{
    Cl27_Derived d;
    Cl27_Base* pb = &d;    //隐式转换
    //有时候以上两个指针的值并不相同，运行期会有一个偏移量施行与Cl27_Derived身上，用以取得正确的Base指针
    //不要妄想将对象地址转型为char*指针，然后在它们身上进行指针算术，几乎总会导致程序的不明确行为

    //注意:偏移量只是有时需要，对象的布局方式和它们的地址计算方式随编译器的变化而变化，所以指针对象的布局设计的转型在
    //某一平台行得通，其他平台并不一定行得通。
}

//例子3:假设应用框架要求derived类的virtual函数代码的第一个动作先调用基类对应的函数，以下实现为什么会有问题
class Cl27_Window{
public:
    virtual void onResize(){std::cout<<"Cl27_Window::onResize is runing\n";}
};

class Cl27_SpecialWindow: public Cl27_Window{
public:
    virtual void onResize(){
        //错误做法
        //static_cast<Cl27_Window>(*this).onResize();//不可行，为什么？答:因为调用的并非基类的原始对象，而是编译器构造出的副本，当某一时刻如果基类发生改变，此时派生类完全不知。

        //正确做法
        Cl27_Window::onResize();//直接调用基类原始对象，当基类发生变化，派生类也会跟随变化

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }
};
void Cl27_test03()
{
    Cl27_SpecialWindow csw;
    csw.onResize();
}

/*dynamic_cast的使用成本:
 *  在N层深的单继承体系内的某个对象执行dynamic_cast，每一次可能都会耗用N次的strcmp调用，用以比较class名称。
 * 深度或多重继承成本更高。
 *  之所以需要dynamic_cast，通常是想在一个派生类的对象中执行派生类操作函数，手上却只能一个base指针或者引用，
 * 这时就需要dynamic_cast来处理这个对象。
 */

//想要避免通过基类指针操作派生类对象有两个一般性做法:
// 一、使用容器并在其中存储指向派生类指针的对象(通常是智能指针)
//例子:4 假设Cl27_Window/Cl27_SpecialWindow继承体系中只有Cl27_SpecialWindow才能支持闪烁效果
class Cl27_SpecialWindowExp1: public Cl27_Window{
public:
    virtual void onResize(){
        //错误做法
        //static_cast<Cl27_Window>(*this).onResize();//不可行，为什么？答:因为调用的并非基类的原始对象，而是编译器构造出的副本，当某一时刻如果基类发生改变，此时派生类完全不知。

        //正确做法
        Cl27_Window::onResize();//直接调用基类原始对象，当基类发生变化，派生类也会跟随变化

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }

    void blink(){  std::cout<<"Cl27_SpecialWindowExp1::blink is runing\n";}
};
void Cl27_test04()
{
    //错误做法
    typedef std::vector<std::shared_ptr<Cl27_Window>> VPM;
    VPM winPtrs;

    for(VPM::iterator iter = winPtrs.begin();
            iter!=winPtrs.end();iter++)
    {
        if(Cl27_SpecialWindowExp1* psw = dynamic_cast<Cl27_SpecialWindowExp1*>(iter->get())){
            psw->blink();
        }
    }

    //建议做法:参考第二点的实现
    for(VPM::iterator iter = winPtrs.begin();
        iter!=winPtrs.end();iter++)
    {
        //*(iter)->blink(); //这种做法就不能用同一容器内存储指针"指向所有可能的各种派生类"
    }
}
// 二、通过基类接口处理"所有可能的各种window派生类"
class Cl27_WindowExperience{
public:
    virtual void onResize(){std::cout<<"Cl27_Window::onResize is runing\n";}
    virtual void blink(){
        //缺省 只派生提供接口作用
    }
};
class Cl27_SpecialWindowExperience: public Cl27_WindowExperience{
public:
    virtual void onResize(){
        //错误做法
        //static_cast<Cl27_Window>(*this).onResize();//不可行，为什么？答:因为调用的并非基类的原始对象，而是编译器构造出的副本，当某一时刻如果基类发生改变，此时派生类完全不知。

        //正确做法
        Cl27_WindowExperience::onResize();//直接调用基类原始对象，当基类发生变化，派生类也会跟随变化

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }
    void blink(){  std::cout<<"Cl27_SpecialWindowExperience::blink is runing\n";}
};

void Cl27_test05()
{
    //获得一个基类指针
    std::shared_ptr<Cl27_WindowExperience> scwe(new Cl27_SpecialWindowExperience()); //触发隐式转换: Cl27_SpecialWindowExperience->Cl27_WindowExperience
    scwe->blink();//得到派生类执行结果
}

//无论是做法一还是做法二-------使用"类型安全容器"或将"virtual函数往继承体系上方移动"-------但并非绝对，许多情况下应提供一个dynamic_cast替代方案
////例子:5 避免连串的使用dynamic_cast:
class Cl27_WindowExp1{ virtual void onResize(){}};
class Cl27_SpecialWindowExp2 : public Cl27_WindowExp1{};
class Cl27_SpecialWindowExp3 : public Cl27_WindowExp1{};
class Cl27_SpecialWindowExp4 : public Cl27_WindowExp1{};
void Cl27_test06()
{
    //错误做法
    typedef std::vector<std::shared_ptr<Cl27_WindowExp1>> VPM;
    VPM winPtrs;

    for(VPM::iterator iter = winPtrs.begin();
        iter!=winPtrs.end();iter++)
    {
        if(Cl27_SpecialWindowExp2* psw = dynamic_cast<Cl27_SpecialWindowExp2*>(iter->get())){
            //...
        }
        else if(Cl27_SpecialWindowExp3* psw = dynamic_cast<Cl27_SpecialWindowExp3*>(iter->get())){
            //...
        }
        else if(Cl27_SpecialWindowExp4* psw = dynamic_cast<Cl27_SpecialWindowExp4*>(iter->get())){
            //...
        }
    }

    //以上产生的代码又大又慢，而且基础不稳，每次继承体系有所改变，这类代码必须检阅是否需要修改。一旦加入新的派生类，或许就需要判断增加新的分支
    //这样的代码总是以"基于虚函数调用"的东西取而代之
    //优良的C++代码很少使用转型，使用的时候把它隐藏在某个函数内，函数的接口会保护调用者不受函数内部的动作影响
}

/*重点记住:
 * 1.如果可以，尽量避免转型，特别是在注重效率的代码中避免使用dynamic_cast.如果有设计需要转型动作，试着发展无需转型的替代设计
 * 2.如果转型是必要的，试着将它隐藏在某个函数背后。
 * 3.宁可使用C++style的转型，不要使用旧式转型。前者容易分辨且分工比较明确
 */





#endif //EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP
