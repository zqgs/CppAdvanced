//
// Created by 曾庆国 on 2021/7/19.
//

#ifndef EFFECTIVECPP_CLAUSE17_NEWED_OBJECT_IN_SMART_POINTERS_HPP
#define EFFECTIVECPP_CLAUSE17_NEWED_OBJECT_IN_SMART_POINTERS_HPP

#include <memory>
#include <iostream>
//条款17：以独立语句将newed对象置入智能指针

//C++对函数的参数处理顺序不固定
//错误例子:
class Cl17_Widget{};
int priority(){
    return 0;
}
void processWidget(std::shared_ptr<Cl17_Widget> pw,int pro){
    std::cout<<"processWidget\n";
}
void Cl17_Test01()
{
    //此处std::shared_ptr<Cl17_Widget>(new Cl17_Widget)的执行顺序
    //1.执行 new Cl17_Widget
    //2.执行shared_ptr的构造函数
    processWidget(std::shared_ptr<Cl17_Widget>(new Cl17_Widget),priority());

    //在processWidget执行前，编译器创建代码
    //1.调用priority
    //2.执行"new Widget"
    //3.调用shared_ptr的构造函数
    //编译器是以怎样的次序完成以上这些事？（答案：不固定）

    //如果最终是这样的顺序：（new一定先于智能指针执行，但不一定晚于priority被执行）
    //1.执行"new Widget"
    //2.调用priority
    //3.调用shared_ptr的构造函数
    //如果priority发生异常，导致智能指针赋值失败。此刻new产生的指针变成了野指针，发生了内存泄漏
}

//正确调用
void Cl17_Test02()
{
    std::shared_ptr<Cl17_Widget> pw(new Cl17_Widget);
    processWidget(pw,priority());
}


/*重点记住:
 * 以独立语句将newed对象存储于智能指针内。如果不这样做，一定异常被抛出,有可能导致难以察觉的资源泄漏。
 */


#endif //EFFECTIVECPP_CLAUSE17_NEWED_OBJECT_IN_SMART_POINTERS_HPP
