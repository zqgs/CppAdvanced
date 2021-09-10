//
// Created by Sea on 2021/9/10.
//

#ifndef EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP
#define EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP

#include <iostream>
//条款37：绝不重新定义继承而来的缺省参数值
//直接看例子1:只能够继承两种函数:virtual和non-virtual(不可被派生类重写),讨论继承一个带有缺省参数值的virtual
class Cl37_Shape{
public:
    enum ShapeColor{Red,Green,Blue};
    virtual void draw(ShapeColor color = Red)const =0;
};
//派生类1:
class Cl37_Rectangle: public Cl37_Shape{
public:
    //注意:赋予不同的缺省参数值。
    void draw(ShapeColor color = Green)const override{
        std::cout<<"Cl37_Rectangle::color:"<<color<<std::endl;
    }
};
class  Cl37_Circle: public Cl37_Shape{
public:
    void draw(ShapeColor color) const override{
        std::cout<<"Cl37_Circle::color:"<<color<<std::endl;
        /*  如果这么重写这个函数，调用者以对象调用此函数，一定要指定参数值。
         *因为静态绑定下这么函数并不从Base继承缺省参数值
         *  但如果以指针(Reference)调用此函数，可以不指定参数值
         *因为动态绑定下这个函数会从Base继承缺省参数值
        */
    }
};

void Cl37_test01()
{
    //动态绑定:从Base继承缺省参数值
    Cl37_Shape* ps;
    Cl37_Shape* ps1 = new Cl37_Rectangle();
    delete ps1;
    Cl37_Shape* pr = new Cl37_Circle();
    pr->draw();
    delete pr;
    //静态绑定:并不从Base继承缺省参数值
    Cl37_Rectangle cPs;
    cPs.draw();

    Cl37_Circle cPr;
    cPr.draw(Cl37_Shape::Green);

    //上面因绑定方式不一样，函数的缺省值就会发生变化。出现这样的情况，完全是因为C++为了执行速度和编译器的实现上做了取舍。
}

//例子2:如果我们试图老老实实的继承基类的缺省参数值，又会发生什么？
class Cl37_Rectangle_Exp1: public Cl37_Shape{
public:
    //发现代码重复，还带着相依性。如果Shape内的缺省参数值改变了，所有重复给定缺省参数值的那些派生类也要跟着改变。
    void draw(ShapeColor color = Red)const override{
        std::cout<<"Cl37_Rectangle_Exp1::color:"<<color<<std::endl;
    }
};

//例子3:为了解决例子2和例子1的问题，采用条款35中的NVI(non-virtual-interface)设计手法
class Cl37_Shape_Nvi{
public:
    enum ShapeColor{Red,Green,Blue};
    void draw(ShapeColor color = Red) const{
        std::cout<<"Cl37_Shape_Nvi::draw"<<std::endl;
        doDraw(color);
    }

private:
    virtual void doDraw(ShapeColor color)const =0;
};

class Cl37_Rectangle_Nvi: public Cl37_Shape_Nvi{
private:
    void doDraw(ShapeColor color)const override
    {
        std::cout<<"Cl37_Rectangle_Nvi::color:"<<color<<std::endl;
    }
};
class Cl37_Circle_Nvi: public Cl37_Shape_Nvi{
private:
    void doDraw(ShapeColor color)const override
    {
        std::cout<<"Cl37_Circle_Nvi::color:"<<color<<std::endl;
    }
};

void Cl37_test02()
{
    //无论是静态绑定还是动态绑定,传什么色就是什么色，如果不传就是基类色
    Cl37_Shape_Nvi* ps;
    Cl37_Shape_Nvi* ps1 = new Cl37_Rectangle_Nvi();
    delete ps1;
    Cl37_Shape_Nvi* pr = new Cl37_Circle_Nvi();
    pr->draw();
    delete pr;

    Cl37_Rectangle_Nvi cPs;
    cPs.draw();

    Cl37_Circle_Nvi cPr;
    cPr.draw(Cl37_Shape_Nvi::Green);
}

/*重点记住:
 *  1.绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，
 * 而virtual函数是唯一应该覆写的东西却是动态绑定
 */




#endif //EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP
