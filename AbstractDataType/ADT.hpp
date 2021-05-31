//
// Created by Sea on 2021/5/31.
//

#ifndef ABSTRACTDATATYPE_ADT_HPP
#define ABSTRACTDATATYPE_ADT_HPP

/*
 数据结构及其算法学习--抽象数据类型ADT
 数据结构分为：逻辑、运算、存储(抽象数据类型忽略数据的存储)
 1.逻辑结构:数据对象及其关系
 2.运算:数据操作
*/

//逻辑结构的体现
template <class T>
class _Stack{
public:
    bool pop(T &Item);//出栈
    bool push(const T& Item);//入栈
    //...等等操作
    void clear();
};
//运算则是对数据进行操作-->也就是函数的实现


#endif //ABSTRACTDATATYPE_ADT_HPP
