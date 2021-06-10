//
// Created by Sea on 2021/6/10.
//

#ifndef ABSTRACTDATATYPE_STACK_LINK_BASED_HPP
#define ABSTRACTDATATYPE_STACK_LINK_BASED_HPP
#include "Template_LinearTable.h"

#include <iostream>

//链式栈
template <class T>
class lnkStack: public _Stack<T>
{
private:
    //栈顶指针
    Link<T> *top;
    //存放的元素个数
    int iSize;
public:
    lnkStack(){iSize = 0;}
    bool push(const T Item) override;
    bool pop(T &Item) override;
};

//压栈
template <class T>
bool lnkStack<T>::push(const T Item) {
    Link<T> *lk = new Link<T>(Item,top);
    if(lk)
    {
        top = lk;
        iSize++;
        return true;
    }
    return false;
}
//弹栈
template <class T>
bool lnkStack<T>::pop(T &Item)
{
    if(iSize==0)
        return false;
    Link<T> *lk = top;
    Item = top->data;
    top = top->next;

    delete lk;
    lk = nullptr;

    iSize --;
    return true;
}


#endif //ABSTRACTDATATYPE_STACK_LINK_BASED_HPP
