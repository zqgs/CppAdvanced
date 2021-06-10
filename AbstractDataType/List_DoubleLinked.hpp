//
// Created by 曾庆国 on 2021/6/3.
//

#ifndef ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
#define ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
#include <iostream>
#include "Template_LinearTable.h"



template <class T>
class DoubleLinkList:public _List<T>{
private:
    dLink<T> *head;
    dLink<T> *tail;
public:
    dLink<T> *getPos(const int i);
    DoubleLinkList(){
        head = new dLink<T>();
        tail = new dLink<T>();

        head->next = tail;
        tail->prev = head;
    }
    ~DoubleLinkList(){
        //逐一遍历 挨个删除 最后删除头尾节点
    }

    bool _Insert(const int index,const T value) override;//在位置pos上插入一个元素，表长度增加1
    bool _Delete(const int p) override;//删除位置p上的元素 表长度减1
    bool _GetValue(const int p,T &value) override;
};

template <class T>
dLink<T>* DoubleLinkList<T>::getPos(const int i) {

    //获取指定节点的指针 - 通过遍历法
    int count =0;
    if(i==-1)
        return head;
    dLink<T> *p = head->next;

    while(p!=nullptr && count<i)
    {
        std::cout<<"count:"<<count<<"\n";
        p = p->next;
        count++;
    }
    return p;
}

template <class T>
bool DoubleLinkList<T>::_Insert(const int index, const T value) {
    dLink<T> *p,*q;
    if((p=getPos(index-1))== nullptr){
        std::cout<<"insert Link fail\n";
        return false;
    }

    q = new dLink<T>();
    q->next = p;
    q->prev = p->prev;
    p->prev->next = q;
    p->prev = q;
    q->data = value;
    return true;
}

template <class T>
bool DoubleLinkList<T>::_Delete(const int pos) {
    //寻找节点
    dLink<T>*p,*LinkPoint;
    LinkPoint= getPos(pos-1);

    if(LinkPoint== nullptr
       || LinkPoint == head
       || LinkPoint == tail)
        return false;
    //printf("Link data：%d\n",LinkPoint->data);
    //已找到该节点 - 开始执行删除操作
    LinkPoint->prev->next = LinkPoint->next;
    LinkPoint->next->prev = LinkPoint->prev;


    //置空指针
    LinkPoint->next = nullptr;
    LinkPoint->prev = nullptr;
    //释放节点
    delete LinkPoint;
    LinkPoint= nullptr;
    return true;
}



template <class T>
bool DoubleLinkList<T>::_GetValue(const int p, T &value) {
    dLink<T>* LinkPoint = getPos(p-1);
    if(LinkPoint== nullptr
       || LinkPoint == head
       || LinkPoint == tail)
        return false;

    value = LinkPoint->data;
    return true;
}
#endif //ABSTRACTDATATYPE_DOUBLELINKED_LIST_HPP
