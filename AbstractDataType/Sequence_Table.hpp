//
// Created by Sea on 2021/6/1.
//

#ifndef ABSTRACTDATATYPE_SEQUENCE_TABLE_HPP
#define ABSTRACTDATATYPE_SEQUENCE_TABLE_HPP

#include "Linear_TableTemplate.h"
//顺序表结构定义 - 继承线性表
template <class T>
class arrList: public _List<T>{
private:
    T *aList;//存储顺序表的实例
    int maxSize;//顺序表实例的最大长度
    int curLen;//顺序表实例的当前长度
    int position;//当前处理位置
public:
    arrList(const int size){
        maxSize = size;
        aList = new T[maxSize]();//加()默认申请时初始化，不加()申请时不会自动初始化
        curLen = position =0;
    }
    T & operator[](T i) const
    {
        if( i > maxSize )
        {
            //当传入的index大于数组的长度，则返回第一个元素
            return aList[0];
        }
        return aList[i];
    }
    ~arrList(){
        if(aList)
            delete aList;
    }
    bool _Insert(const int pos,const T value);
    bool _Delete(const int pos);
};
template <class T>
bool arrList<T>::_Delete(const int pos) {
    /*线性表删除过程*/
    //1.检查顺序表是否为空
    if(curLen<=0)
        return false;

    //2.检查删除位置是否合法
    if(pos>curLen-1||pos<0)
        return false;

    for(int i=pos;i<curLen-1;i++)
        aList[i] = aList[i+1];
    curLen--;
    return true;
}

template <class T>
bool arrList<T>::_Insert(const int pos, const T value) {
    /*线性表插入过程*/
    //1.检查线性表是否溢出
    if(pos>=maxSize){
        std::cout<<"The list is overFlow\n";
        return false;
    }

    //2.检查插入位置是否合法
    if(pos<0 || pos>curLen){
        std::cout<<"Insertion point is illegal\n";
        return false;
    }

    //3.先将插入位置往后的数据全部后移1位
    for(int i=curLen;i<pos;i--)
        aList[i+1] = aList[i];
    aList[pos] = value;
    curLen++;
    return true;
}



#endif //ABSTRACTDATATYPE_SEQUENCE_TABLE_HPP
