//
// Created by Sea on 2021/7/16.
//

#ifndef EFFECTIVECPP_CLAUSE14_CAREFULLY_ABOUT_COPYING_IN_MANAG_CLASS_HPP
#define EFFECTIVECPP_CLAUSE14_CAREFULLY_ABOUT_COPYING_IN_MANAG_CLASS_HPP

#include <mutex>
#include <memory>
//条款14:在资源管理类中小心copying行为


//条款13引入了RAII概念，并描述了auto_ptr与shared_ptr如果将RAII概念在heap-based(基于堆空间)资源上
//当我们要管理的资源不在堆空间(heap-based)时，我们需要手动编写一个资源管理类

//例子:利用RAII实现一个自动管理的互斥器
void _clause14_Lock(std::mutex *pm){
    pm->lock();
}
void _clause14_UnLock(std::mutex *pm){
    pm->unlock();
}

//常规RAII资源管理实现
class Clause14_Lock
{
public:
    explicit Clause14_Lock(std::mutex* pm):
    mutexPtr(pm){
        _clause14_Lock(mutexPtr);
    }
    ~Clause14_Lock(){
        _clause14_UnLock(mutexPtr);
    }
    //条款06：若不想使用编译器自动生成的函数，就应该明确的拒绝
    //该类默认实现拷贝构造和拷贝赋值操作符
    //该类无法阻止被复制，复制后的资源该如何正确的使用？？
    //明确知道，该类不需要复制行为，我们应该拒绝。
private:
    std::mutex *mutexPtr;
};


//如何解决RAII对象被复制的问题,处理办法如下:

//1.禁止拷贝后的RAII资源管理类
namespace clause14
{
    //拒绝类的复制行为
    class UnCopyAble{
    protected:
        UnCopyAble(){}
        ~UnCopyAble(){}
    private:
        //明确拒绝拷贝构造和赋值操作符
        UnCopyAble(const UnCopyAble&);
        UnCopyAble& operator=(const UnCopyAble &);
    };
}

class Clause14_LockExp:
        private clause14::UnCopyAble
{
public:
    explicit Clause14_LockExp(std::mutex* pm):
    mutexPtr(pm){
            _clause14_Lock(mutexPtr);
    }
    ~Clause14_LockExp(){
        _clause14_UnLock(mutexPtr);
    }
    //此时已经确保了该类不会被复制，保证了该类不会因调用失误而产生不明确的行为
private:
    std::mutex *mutexPtr;
};

/*2.对底层资源使用"引用计数法"，可以使用shared_ptr来完成这件事，但是shared_ptr的工作机能是当引用
 * 计数为0时，资源会被释放(也就是执行删除器deleter)。此时我们需要指定删除器，不要让它析构时调用默
 * 认的删除器。
 */
class Clause14_LockExp1
{
public:
    explicit Clause14_LockExp1(std::mutex* pm):
            mutexPtr(pm,_clause14_UnLock)//指定删除器_clause14_UnLock
    {
        _clause14_Lock(mutexPtr.get());
    }
    //不再需要析构函数
private:
    std::shared_ptr<std::mutex> mutexPtr;
};


//3.复制底部资源。既然调用者想复制，那就索性让他复制。遵循<条款12:赋值对象时勿忘其每一个成分>完成复制确保该资源进行了深度拷贝。
//深度拷贝解析:某些字符串类型有堆内存与指针构成，当这个字符串被复制时，不论是指针还是指针所指的内存都会被制作出一个"副本"，此时该字符串的复制行为称为"深度拷贝"

//4.转移底部资源的使用权。正如auto_ptr奉行的复制意义。

/*重点记住:
 * 1.复制RAII对象必须一并复制它所管理的资源，资源的复制行为决定RAII对象的复制行为。
 * 2.常见的RAII class copying行为：抑制copying、施行引用计数法。
 */



#endif //EFFECTIVECPP_CLAUSE14_CAREFULLY_ABOUT_COPYING_IN_MANAG_CLASS_HPP
