//
// Created by Sea on 2021/6/2.
//

#ifndef ABSTRACTDATATYPE_LINKED_LIST_HPP
#define ABSTRACTDATATYPE_LINKED_LIST_HPP
#include "Linear_TableTemplate.h"

//节点
template <class T>
class Link{
    T data;
    Link<T> * next;
    Link(const T info,const Link<T>* nextPoint = nullptr){
        data = info;
        next = nextPoint;
    }
    Link(const Link<T>* nextPoint)
    {
        next = nextPoint;
    }
};


//单链表定义  继承至线性表模板
template <class T>
class  linkList: public _List<T>
{
    //单链特有属性
private:
    Link<T> *head,*tail;//单链表的头、尾指针
    Link<T> *getPos(const int pos);//第pos个元素的指针
public:
    linkList(int s);
    ~linkList();

};

template <class T>
Link<T>* linkList<T>::getPos(const int pos) {
    //获取指定节点的指针 - 通过遍历法
    int count =0;
    if(pos==-1)
        return head;
    linkList<T> *p = head->next;
}


#endif //ABSTRACTDATATYPE_LINKED_LIST_HPP
