//
// Created by Sea on 2021/7/16.
//

#ifndef EFFECTIVECPP_CLAUSE13_USE_OBJECT_TO_MANAGE_RESOURCES_HPP
#define EFFECTIVECPP_CLAUSE13_USE_OBJECT_TO_MANAGE_RESOURCES_HPP

#include <memory>

//条款13:以对象管理资源

//多态(工厂模式)引发资源释放问题
class Investment{};

Investment * CreateInvestment(){return new Investment();}
void Clause13_fun01(){
    Investment *pInv = CreateInvestment();
    //...执行一些操作 有可能无意中触发了return
    delete pInv;//并不是所有的情况下 都能保证pInv被释放
}

//为了确保资源及时的释放，C++11引入智能指针:auto_ptr
void Clause13_fun02(){
    std::auto_ptr<Investment> pInv(CreateInvestment());
    //...执行一些操作 即使无意中触发了return，在return执行前会调用auto_ptr的析构
}

/*以对象管理资源关键思路:
 * 1.获得资源后立刻放进管理对象内。通常"以对象管理资源"的概念被称为资源获取即初始化(RAII)
 * 2.管理对象运用析构函数确保资源被释放。不论程序控制流如何离开区块，一旦对象被销毁(比如:当前对象离开了作用域)
 * 其析构函数自然会被调用。(注意:条款8声明。如果有不确定异常的操作，应开放该操作给调用者，不要在析构内抛出异常)
 */


/*auto_ptr的使用规范：
 * 别让多个auto_ptr指向同一对象。auto_ptrs:若通过copy构造函数或拷贝赋值操作符复制它们
 * 它们会变成null，而复制所得的指针将取得资源的唯一拥有权。
 */
//举例:
void Clause13_fun03(){
    std::auto_ptr<Investment> pInv(CreateInvestment());//pInv指向CreateInvestment返回的对象
    std::auto_ptr<Investment> pInv2(pInv);//pIv2取得指针使用权，pInv被设为null
    pInv = pInv2;//pInv取得指针使用权，pInv2被设为null
}
//auto_ptr弊端:受auto_ptrs管理的资源必须绝对没有一个以上的auto_ptr时指向它。意味着auto_ptr并非是管理动态分配的资源的做法
//例子:STL容器要求其元素发挥正常的复制行为，因此这些容器容不得auto_ptr

//引入RCSP(引用计数型智能指针)来代替auto_ptr,RCSP的行为类似于垃圾回收.弊端:无法打破环状引用

void Clause13_fun04(){
    std::shared_ptr<Investment> pInv(CreateInvestment());//pInv指向CreateInvestment返回的对象
    //...执行一些操作 即使无意中触发了return，在return执行前会调用shared_ptr的析构
}
void Clause13_fun05() {
    std::shared_ptr<Investment> pInv(CreateInvestment());//pInv指向CreateInvestment返回的对象
    std::shared_ptr<Investment> pInv2(pInv);//pInv与pInv2都指向CreateInvestment返回的对象
    pInv = pInv2;//pInv与pInv2都指向CreateInvestment返回的对象

    //当离开作用域时pInv与pInv2同时被销毁
}

//注意:最好不要用动态分配而得的array使用在auto_ptr或shared_ptr身上


/*重点记住:
 * 1.为了防止资源泄漏，如非必要情况，请使用RAII对象，它们在构造函数中获得资源并在析构中释放资源。
 * 2.两个常用的RAII类分别时share_ptr和auto_ptr。share_ptr通常比较时较好的选择，因为其copy行为比较直观，
 * 若选择auto_ptr复制动作会使被复制的对象指向null
 */


#endif //EFFECTIVECPP_CLAUSE13_USE_OBJECT_TO_MANAGE_RESOURCES_HPP
