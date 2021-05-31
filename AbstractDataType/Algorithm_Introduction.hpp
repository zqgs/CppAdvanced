//
// Created by Sea on 2021/5/31.
//

#ifndef ABSTRACTDATATYPE_ALGORITHM_INTRODUCTION_HPP
#define ABSTRACTDATATYPE_ALGORITHM_INTRODUCTION_HPP
#include <iostream>

/*
基本算法分类
 1.穷举法：顺序查找key值
 2.回溯、搜索：八皇后、树和图遍历（能进则进，不能进则换，不能换则退）
 3.递归分治：二分找key值（最优子结构、子结构不能重复）、快速排序、归并排序
 4.贪心法:Huffman编码树、最短Dijkstra算法、最小生成树Prim算法
 5.动态规划：最短路Floyd算法
*/

//例子:顺序查找Key值
template <class Type>
class Item{
private:
    Type key;
public:
    Item(Type value):key(value){}
    Type getKey(){return key;}
    void setKey(Type k){key=k;}
};
#include <vector>

template <class Type>
int SeqSerch(std::vector<Item<Type>> datalist,int length,Type k)
{
    int i = length;
    datalist[0].setKey(k);

    while(datalist[i].getKey()!=k){
        std::cout<<"Algorithm_Introduction getKey:"<<i<<"\n";
        i--;
    }
    return i;
}

//高效递归分治：二分法 已排序，后二分查找
template <class Type>
int BinSerch(std::vector<Item<Type>> datalist,int length,int k)
{
    int low =1,high=length,mid;
    while(low<=high)
    {
        mid=(low+high)/2;//中间值
        if(k<datalist[mid].getKey())//左边
        {
            high = mid-1;
        }
        else if(k>datalist[mid].getKey())//右边
        {
            low = mid+1;
        }
        else//相等
            return mid;
    }
    return 0;//未找到
}

//Example 设计算法:原始数组0 1 2 3 4  右移两位后 3 4 0 1 2
template <class Type>
void Design(std::vector<Item<Type>> &dateList, int ArrayLength,int k)
{
    Type ArrayTemp[ArrayLength];
    //数组长度
    int Length =ArrayLength;
    for (int i = 0; i < Length; ++i) {
        //计算当前i+k后的地址
        int rem = (i+k)%Length;
        ArrayTemp[rem] = dateList[i].getKey();
    }
    dateList.clear();
    for (int i = 0; i < Length; ++i)
        dateList.push_back(ArrayTemp[i]);
}

#endif //ABSTRACTDATATYPE_ALGORITHM_INTRODUCTION_HPP
