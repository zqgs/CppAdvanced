//
// Created by Sea on 2021/9/13.
//

#ifndef EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP
#define EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP

#include <iostream>

//条款39:明智而审慎的使用private继承
//众所周知:public是is-a,假如一个学生(derive)继承人(base),学生将可以实现一部分人的行为，必要时刻会将derive暗自转换为base。
//例1：那么将public换成private会发生什么？
class Cl39_Person{};
class Cl39_Student: private Cl39_Person{};

void Cl39_eat(const Cl39_Person& p){}
void Cl39_study(const Cl39_Student& s){}

void Cl39_test01()
{
    Cl39_Person p;
    Cl39_Student s;
    Cl39_eat(p);
    //Cl39_eat(s);//报错,学生竟然不能吃东西，显然private不是is-a关系。
    //之所以会调用失败，原因有二:
    //1.private继承不会暗自将派生类转化为基类。
    //2.由private base class继承而来的所有成员，在派生类中都会变成private，纵使在base class中原来是public或者protected
}

//private继承意味着:根据某物实现出(D private继承 B意味着D对象根据B对象实现而得，再无它意)
//条款38中的复合在实现域中表现出根据某物实现出的特性。尽可能使用复合，必要时才使用private继承
//何时才是必要使用private继承？
//1.当protected成员和virtual函数牵扯进来的时候。
//2.当空间方面的利害关系足以推翻private继承的支柱时。



//例2:验证一下private继承
class Cl39_Timer{
public:
    explicit Cl39_Timer(int tickFrequency);
    virtual void onTick() const{std::cout<<"Cl39_Timer::onTick\n";}
};
class Cl39_Widget: private Cl39_Timer{
public:
     void doSomething(){
         onTick();
     }
//情况1:重写虚函数
private:
     void onTick() const override {std::cout<<"Cl39_Widget::onTick\n"};
//情况2:不重写虚函数
};

//例3:(发现Cl39的派生类依旧会重写基类的虚函数)。如果不想让派生类重写基类的虚函数,可以尝试复合+public继承
class Cl39_Widget_Exp1{
private:
    //public + 复合
    class WidgetTimer: public Cl39_Timer{
    public:
        void onTick() const override {std::cout<<"Cl39_Widget_Exp1::WidgetTimer::onTick\n";}
    };
    WidgetTimer timer;
};


//空类是否需要内存？
class Cl39_Empty{};//正常来说不使用任何内存
class Cl39_HoldAnInt{
private:
    int x;
    Cl39_Empty e;//应该不需要内存
};
//发现sizeof(Cl39_HoldAnInt)>sizeof(Cl39_Empty).绝大多数编译器王空类中塞了了char,往往空类又达不到1的大小,实际又被放大到了足够存放一个int。

//private继承空间变化又是如何？
class Cl39_HoldAnInt_Exp1: private Cl39_Empty{
private:
    int x;
};
//sizeof(Cl39_HoldAnInt_Exp1) == sizeof(Cl39_Empty)是相等的。事实证明尽量谨慎的使用private继承，尽量使用复合!!!


/*重点记住:
 *  1.Private继承意味着(根据某物实现出)。它通常比复合的级别低。但是当derived class需要访问基类的protected的成员或需要重新
 *定义继承而来的virtual函数时，这么设计也是合理的。
 *  2.和复合不通，private继承可以造成empty base最优化。这对致力于"对象尺寸最小化"的程序库开发而言，可能很重要。
 */

#endif //EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP
