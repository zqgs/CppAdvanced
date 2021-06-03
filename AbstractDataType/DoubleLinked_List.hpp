//
// Created by 曾庆国 on 2021/6/3.
//

#ifndef ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
#define ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
#include <iostream>
#include "Linear_TableTemplate.h"

//双链表节点定义
template <class T>
class Link{
public:
    T data;
    Link<T> *prev;
    Link<T> *next;
    Link(const T info,Link<T> *PrevPoint =nullptr,Link<T> *nextPoint = nullptr){
        data = info;
        prev = PrevPoint;
        next = nextPoint;
    }
    Link(Link<T> * PrevPoint = nullptr,Link<T> *nextPoint = nullptr){
        prev = PrevPoint;
        next = nextPoint;
    }
};

template <class T>
class DoubleLinkList:public _List<T>{
private:
    Link<T> *head;
    Link<T> *tail;
public:
    Link<T> *getPos(const int i);
};

template <class T>
Link<T>* DoubleLinkList<T>::getPos(const int i) {
    return nullptr;
}


#endif //ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
