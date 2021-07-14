//
// Created by Sea on 2021/7/14.
//

#ifndef EFFECTIVECPP_CLAUSE10_HAVE_OPERATORS_RETURN_REF_TO_P_THIS_HPP
#define EFFECTIVECPP_CLAUSE10_HAVE_OPERATORS_RETURN_REF_TO_P_THIS_HPP

#include <iostream>

//条款10:令赋值操作符(operator=)返回一个reference to *this

//想实现连锁赋值，赋值操作符须返回一个引用
//例子:
void Example_Clause10()
{
    int x,y,z;
    //如果对象想实现类似的连锁赋值，赋值操作符须返回引用
    x=y=z=15;
}


class Clause10_Widget{
public:
    Clause10_Widget():x(0){}
    Clause10_Widget(int ints):x(ints){}
    //=号赋值操作符
    Clause10_Widget& operator=(const Clause10_Widget& rhs){
        this->x = rhs.x;
        return *this;//返回this的引用
    }
    //+=赋值操作符
    Clause10_Widget& operator+=(const Clause10_Widget& rhs){
        this->x = this->x + rhs.x;
        return *this;
    }

    int x;
};

void Call_Clause10_Widget()
{
    Clause10_Widget cw1,cw2,cw3;
    cw1 = cw2 = cw3 = 15;//连锁赋值
    std::cout<<"cw1:"<<cw1.x<<std::endl;
    std::cout<<"cw2:"<<cw2.x<<std::endl;
    std::cout<<"cw3:"<<cw3.x<<std::endl;

    Clause10_Widget cw4(1);
    cw4+=cw1;
    std::cout<<"cw4:"<<cw4.x<<std::endl;
}



#endif //EFFECTIVECPP_CLAUSE10_HAVE_OPERATORS_RETURN_REF_TO_P_THIS_HPP
