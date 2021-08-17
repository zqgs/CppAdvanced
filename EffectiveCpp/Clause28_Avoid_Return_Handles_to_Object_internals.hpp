//
// Created by Sea on 2021/8/17.
//

#ifndef EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP
#define EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP

#include <memory>
#include <iostream>
//条款28:避免返回handles指向对象内部成分


//直接来看一个错误示例1：
//有一个类表示点坐标
class Cl28_Point{
public:
    Cl28_Point(){}
    Cl28_Point(int x,int y):_x(x),_y(y){
        std::cout<<"Cl28_Point:X->"<<_x<<"\n";
        std::cout<<"Cl28_Point:Y->"<<_x<<"\n";
    }
    ~Cl28_Point(){}

    void setX(int value){_x = value;std::cout<<"Cl28_Point:X->"<<_x<<"\n";}
    void setY(int value){_y = value;std::cout<<"Cl28_Point:Y->"<<_y<<"\n";}
private:
    int _x;
    int _y;
};

//有一个结构体表示矩形
struct Cl28_RectData{
    Cl28_RectData(Cl28_Point u,Cl28_Point l):ulhc(u),lrhc(l){}
    Cl28_Point ulhc;//左上角
    Cl28_Point lrhc;//右下角
};
//构造一个矩形类
class Cl28_Rectangle{
public:
    Cl28_Rectangle(Cl28_Point u,Cl28_Point l){
        pData = std::make_shared<Cl28_RectData>(u,l);
    }
    Cl28_Point& upperLet() const{return pData->ulhc;}
    Cl28_Point& lowerRighe() const{return pData->lrhc;}
private:
    std::shared_ptr<Cl28_RectData> pData;
};
//调用这个矩形类
void Cl28_test01()
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_Rectangle rec(coord1,coord2);
    rec.upperLet().setX(50);//强行修改内部的值。这里的rec是const不可变的，却被强行修改了内部数据
}
//上面的例子产生了两个问题:
//1.成员变量的封装性最多只等于"返回其reference"的函数访问级别。虽然ulhc和lrhc都被声明未private，实际上是public，因为public函数传出了它们的引用
//2.如果const成员函数传出一个reference，且所指数据与对象和自身有关联，而它又被存储于对象之外，那么这个函数调用者可以修改这个数据

//上面发生的事情都是由于"成员函数返回reference"。如果返回的是指针或迭代器，相同的情况依旧发生。引用、指针、迭代器都是所谓的"handles",返回一个代表
//内部数据的handle的同时，也会"降低对象封装性"。

//消除上面产生的问题示例2:只需要返回类型加上const即可
class Cl28_RectangleExp1{
public:
    Cl28_RectangleExp1(Cl28_Point u,Cl28_Point l){
        pData = std::make_shared<Cl28_RectData>(u,l);
    }
    const Cl28_Point& upperLet() const{return pData->ulhc;}
    const Cl28_Point& lowerRighe() const{return pData->lrhc;}
private:
    std::shared_ptr<Cl28_RectData> pData;
};
void Cl28_test02()
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_RectangleExp1 rec(coord1,coord2);
    //rec.upperLet().setX(50);//强行修改内部的值，编译器直接报错
}
//即便如此upperLet和lowerRighe还是返回了指向内部的handles。可能会导致多个指针指向同一个handle，当某一个handle被释放后，导致"dangling handle"(空句柄:
// 所指的东西不复存在，最常见的来源就是函数返回值)

//来看一个示例3：
class Cl28_GUIObject{};
const Cl28_RectangleExp1 boundingBox(const Cl28_GUIObject& obj)
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_RectangleExp1 rec(coord1,coord2);
    return rec;
    //返回一个Cl28_RectangleExp1副本,当语句结束后，rec将被销毁，间接导致Point析构
}
void Cl28_test03()
{
    Cl28_GUIObject * pgo;
    //pUpperLeft可能会变成空句柄，后续再继续调用会引起内存泄漏
    const Cl28_Point* pUpperLeft = &(boundingBox(*pgo).upperLet());
}

//并不意味着不能返回handle。有时候必须那么做。例如:operator[]就允许获取string和vertor的个别元素，这些数据会随着容器的销毁而销毁

/*重点记住:
 * 1.避免返回handle(包括reference、指针、迭代器)指向对象内部。这个条款可增加封装性，帮助const成员函数的行为更像const，
 * 并把空句柄(dangling handle)的可能性降到最低.
 */



#endif //EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP
