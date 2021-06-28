//
// Created by Sea on 2021/6/1.
//

#ifndef ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H
#define ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H


//线性表模板类
template<class T>
class _List{
public:
    void _Clear();//置空线性表
    bool _IsEmpty();//线性表为空时，返回true
    bool _Append(const T value);//在表尾添加一个元素value，表长度增加1
    virtual bool _Insert(const int pos,const T value){return true;};//在位置pos上插入一个元素，表长度增加1
    virtual bool _Delete(const int p){return true;};//删除位置p上的元素 表长度减1

    bool _GetPos(int &p,T &value);//查找值为value元素并返回其位置
    virtual bool _GetValue(const int p,T &value) {return true;} //把位置p元素值返回到变量value
    bool _setValue(const int p,const T value);//把value修改位置p的元素值
};



//栈的模板类  栈:一种受到规则限制的线性表   意味着可以实现顺序栈 与 链表栈
template <class T>
class _Stack{
public:
    void clear(); //变为空栈
    virtual bool push(const T Item){return true;}//Item入栈，成功返回真，否则返回假
    virtual bool pop(T &Item){return true;}//返回栈顶内容并弹出，成功为真，否则假
    bool top(T & Item);//返回栈顶但不弹出，成功为真，否则假
    bool isEmpty();//若栈已空返回真
    bool isFull();//若栈已满返回真
};


//单链模板类
template <class T>
class Link{
public:
    T data;
    Link<T> * next;
    Link(const T info, Link<T>* nextPoint = nullptr){
        data = info;
        next = nextPoint;
    }
    Link(Link<T>* nextPoint)
    {
        next = nextPoint;
    }
};

//双链表模板类
template <class T>
class dLink{
public:
    T data;
    dLink<T> *prev;
    dLink<T> *next;
    dLink(const T info,dLink<T> *PrevPoint =nullptr,dLink<T> *nextPoint = nullptr){
        data = info;
        prev = PrevPoint;
        next = nextPoint;
    }
    dLink(dLink<T> * PrevPoint = nullptr,dLink<T> *nextPoint = nullptr){
        prev = PrevPoint;
        next = nextPoint;
    }
};





#endif //ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H
