//
// Created by Sea on 2021/8/31.
//

#ifndef EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP
#define EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP

#include <iostream>
#include <string>
#include <assert.h>
//条款32:确定public继承塑模出is-a关系

//如果class Derived以public形式继承class Base,那么编译器就会认为每一个类型Derived的对象同时也是类型为Base的对象
//众所周知每个学生(Derived)都是人(Base),但每个人并不都是学生。

//例子1：
class Cl32_Bird{
public:
    virtual void fly();//鸟可以飞
};
class Cl32_Penguin://企鹅是一种鸟,但继承了鸟的飞行属性，当它被意外使用的飞行,是不合理的
        public Cl32_Bird{
};

//例子2:
class Cl32_Bird_exp1{
    //未声明fly函数
};
class Cl32_FlyingBird: //飞鸟
        public Cl32_Bird_exp1{
public:
    virtual void fly();
};
class Cl32_Penguin_exp1:
        public Cl32_FlyingBird{
    //此继承体系更符合常理,但并不是完全能适应所有场景.如果当前系统只关心飞行之外的事，那么例子1的双继承体系就完全能够胜任。
};

//例子3:所有鸟都会飞，但企鹅会飞是错误的。以下是运行期才会侦测
void Cl32_error(const std::string& errMsg ){std::cout<<errMsg<<std::endl;}
class Cl32_Penguin_exp2:
        public Cl32_Bird{
public:
    virtual void fly(){Cl32_error("Attempt to make a penguin fly");}
};

//例子4:或者更极端，直接不定义fly函数 以下是编译期会侦测。尽可能把错误的侦测提前至编译期，等到系统正式发布，运行期侦测可能会带来诸多麻烦
class Cl32_Penguin_exp3:
        public Cl32_Bird_exp1{
    //不定义fly函数,直接拒绝调用者有使用的想法
};


//例子5:C++public继承,看一个矩形和正方形的故事
class Cl32_Rectangle{
public:
    virtual void setHeight(int newHeight){theHeight = newHeight;}
    virtual void setWidth(int newWidth){theWidth = newWidth;}
    virtual int height()const {return theHeight;}
    virtual int width() const{return theWidth;}
private:
    int theHeight ;
    int theWidth;
};

class Cl32_Square:
        public Cl32_Rectangle{
public:
    Cl32_Square(){}
    ~Cl32_Square(){}
};
void makeBigger(Cl32_Rectangle& r){
    int oldHeight = r.height();
    r.setWidth(r.width()+10);
    assert(r.height() == oldHeight);
}

void Cl32_test01(){
    Cl32_Square s;
    s.setWidth(10);
    s.setHeight(10);
    std::cout<<"s.width():"<<s.width()<<"\n";
    std::cout<<"s.height():"<<s.height()<<"\n";
    assert(s.width()==s.height());
    makeBigger(s);//改变宽高
    assert(s.width()==s.height());//意外的是正方形的宽高竟然不等
}

//C++public继承主张:能够施行于base class对象身上的每件事情，也可以施行于derived class身上。往往这样的主张C++编译器不会报错，但程序并不一定运行正确。


/*重点记住:
 *  1."public继承"意味着is-a。适用于base classes身上的每一件事情一定适用于derived class身上。因为每一个derived class对象都是一个
 *base class对象。
 */


#endif //EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP
