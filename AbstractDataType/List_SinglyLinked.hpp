//
// Created by Sea on 2021/6/2.
//

#ifndef ABSTRACTDATATYPE_LINKED_LIST_HPP
#define ABSTRACTDATATYPE_LINKED_LIST_HPP
#include "Template_LinearTable.h"

#include <iostream>

//单链表定义  继承至线性表模板
template <class T>
class  linkList: public _List<T>
{
    //单链特有属性
private:
    Link<T> *head ,*tail;//单链表的头、尾指针
    Link<T> *getPos(const int pos);//第pos个元素的指针
public:
    linkList(int s){
        tail = new Link<T>(nullptr);
        head = new Link<T>(tail);
    }
    ~linkList(){}

     bool _Insert(const int index,const T value) override;//在位置pos上插入一个元素，表长度增加1
     bool _GetValue(const int p,T &value) override;
};

template <class T>
Link<T>* linkList<T>::getPos(const int pos) {
    //获取指定节点的指针 - 通过遍历法
    int count =0;
    if(pos==-1)
        return head;
    Link<T> *p = head->next;
    while(p!=nullptr && count<pos)
    {
        p = p->next;
        count++;
    }
    return p;
}
template <class T>
bool linkList<T>::_Insert(const int index, const T value) {
    Link<T> *p,*q;
    if((p=getPos(index-1))== nullptr){
        std::cout<<"insert Link fail\n";
        return false;
    }
    q = new Link<T>(value,p->next);
    p->next = q;
    //if(p==tail)
    //   tail =q;
    return true;
}

template <class T>
bool linkList<T>::_GetValue(const int p, T &value) {
    Link<T>* LinkPoint = getPos(p);
    if(LinkPoint== nullptr
       || LinkPoint == head
       || LinkPoint == tail)
        return false;

    value = LinkPoint->data;
    return true;
}
#endif //ABSTRACTDATATYPE_LINKED_LIST_HPP
