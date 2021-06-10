//
// Created by Sea on 2021/6/4.
//

#ifndef ABSTRACTDATATYPE_ARRAY_BASED_STACK_HPP
#define ABSTRACTDATATYPE_ARRAY_BASED_STACK_HPP
#include "Template_LinearTable.h"

#include <iostream>
//顺序栈实现
template <class T>
class Array_Stack:_Stack<T>
{
private:
    T *Stack;
    int iMaxSize;
    int iTop;//栈顶
public:
    Array_Stack(const int size)
    {
        Stack = new T[size];
        iMaxSize = size;
        iTop = -1;
    }
    bool push(const T Item) override;//Item入栈，成功返回真，否则返回假
    bool pop(T &Item) override;//返回栈顶内容并弹出，成功为真，否则假
};

//弹栈
template <class T>
bool Array_Stack<T>::pop(T &Item) {
    if(iTop==-1)
    {
        std::cout<<"Stack size is null\n";
        return false;
    }
    Item = Stack[iTop--];
    std::cout<<"iTop:"<<iTop<<"\n";
}

//压栈
template <class T>
bool Array_Stack<T>::push(const T Item) {
    if(iTop==iMaxSize-1)
    {
        std::cout<<"Stack size is full\n";
        return false;
    }
    Stack[++iTop] = Item;
    return true;
}

#endif //ABSTRACTDATATYPE_ARRAY_BASED_STACK_HPP
