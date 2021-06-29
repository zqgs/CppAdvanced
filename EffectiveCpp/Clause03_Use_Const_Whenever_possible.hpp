//
// Created by Sea on 2021/6/29.
//

#ifndef EFFECTIVECPP_CLAUSE03_USE_CONST_WHENEVER_POSSIBLE_HPP
#define EFFECTIVECPP_CLAUSE03_USE_CONST_WHENEVER_POSSIBLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
//条款03:尽可能使用const
/*const它允许你指定一个语义约束(不该被改动的对象)，编译器会强制实施这项约束。它允许你告诉编译器和其他人某值
 * 应该保持不变。只是确定了该值不可改变，那么应该明确的展示出来从而获得编译器的襄助，确保这项约束不被违反。
 *
 * const可以修饰classes外部global或namespace作用域中的常量，可以修饰文件、函数、或区块作用域中声明为static
 * 的对象，也可以修饰classes内部的staic和non-static成员变量，对于指针也可以指出指针自身、指针所指物，或者
 * 两者都(或者不)是const。
 */


//<非const表示可被修改>
/*关键字const出现在星号右边表示指针(addr)本身不可被修改
 *关键字const出现在星号左边表示指针所指的数据不可被修改
 *关键字const出现在星号两边表示指针本身和指针指向的数据均不可被修改
 */
char greeting[]="hello world";
char *p1 = greeting;//non-const pointer,non-const data:指针本身非const,指针所指数据非const。
const char* p2 = greeting;//non-const pointer,const data:指针本身非const,指针所指数据const
char* const p3 = greeting;//const-pointer,non-const data:指针本身const，指针所指数据const
const char* const p4 = greeting;//const-pointer,const data:指针本身const,指针所指数据const


//STL迭代器
/*STL迭代器是以指针为根据塑造而来，迭代器的作用像是T*指针。声明迭代器为const就像声明指针为const一样(T* const),
 *表示这个迭代器不得指向不同的东西，但是所指的数据的值是可以改变的。如果迭代器所指向的数据不可改变(const T*)，
 * 那么需要将迭代器声明为const_iterator
 */

std::vector<int> vec;
std::vector<int>::iterator iter = vec.begin();
//正确操作:*iter1 = 10;
//正确操作:++iter1; //相当于T*

const std::vector<int>::iterator iter1 = vec.begin();
//正确操作:*iter1 = 10;
//错误操作:++iter1; //相当于T* const

std::vector<int>::const_iterator iter2 = vec.begin();
//错误操作:*iter1 = 10;//相当于const T*
//正确操作:++iter1;


//const在函数声明时的应用
//在一个函数声明式内，const可以和函数返回值、各个参数、函数自身产生关联
//令函数返回一个常量值，可以降低客户错误而造成意外
class Rational{
    //const Rational operator*(const Rational& lhs,const Rational &rhs){
        //错误使用
        /*Ratioal a,b,c;
         *....
         *(a*b) = c;//在a*b的结果上调用了operator=
         *
        */
   //}
};

//const参数应用:如果有需要改动参数或loacl(局部)对象，否则须声明为const，可以避免“==”被写成“=”的意外

//const成员函数应用:为了确认该成员函数可作用于const对象身上
/*第一:它们使class接口比较容易被理解。得知哪个函数可以改动对象而哪个函数不行是很重要的
 *第二:他们使“操作const对象”成为可能。
 *const成员函数可用来处理取得（并经修饰而成）的const对象
*/

//C++重载机制:两个成员函数如果只是常量性不同，可以被重载
class TextBlock{
public:
    TextBlock(std::string str):text(str){}
    const char& operator[](std::size_t position) const{
        std::cout<<"const operator[] is calling\n";
        return text[position];
    }
    char &operator[](std::size_t position){
        std::cout<<"non-const operator[] is calling\n";
        return text[position];
    }
private:
    std::string text;
};
void callTextBlock(){
    //TextBlock的operator[]可以如下使用:
    TextBlock tb("world");
    std::cout<<"tb[0]:"<<tb[0]<<"\n";

    const TextBlock ctb("Hello");
    std::cout<<"ctb[0]:"<<ctb[0]<<"\n";


    //只要重载operator[]并对不同的版本给与不同的返回类型，就可以令const和non-const获得不同的处理
    /*std::cout<<tb[0] //OK 读一个non-const TextBlock
     *tb[0]='x';//OK 写一个non-const TextBlock
     *std::cout<<ctb[0] //OK 读一个const TextBlock
     *ctb[0]='x';//NG 写一个const TextBlock
    */
    //由于non-const operator[]返回值类型是reference to char,而不是char,如果operator[]返回值只是char，则tb[0]='x'无法通过编译
}
//真实程序中const对象大多用于passed-by-pointer-to-const(const指针传递)或passed-by-reference-to-const(const引用传递)
void print(const TextBlock &ctb){
    std::cout<<"ctb[1]:"<<ctb[1]<<"\n";//调用的是const operator[]
}

//对于常量性定义有两种:bitwise constness/logical constness
/*C++对常量性的定义属于bitwise constness:成员函数在不更改对象的任何成员变量时才可以说是const，也就是说
 *它不更改对象内的任何一个bit。这样容易侦测违反点:编译器只需要寻找成员变量的赋值动作。C++const成员函数
 *不可以更改对象内任何non-static成员变量。
 */

class CTextBlock{
    enum {length = 8};
public:
    CTextBlock(){
        pText = new char[length];
        textLength = length;
        lengthIsValid = true;
    }
    std::size_t Length() const;
private:
    char *pText;
    //这两个变量不能在const成员函数中完成赋值
    std::size_t textLength;
    bool lengthIsValid;

    //const相关的摆动场:mutable
    mutable std::size_t  m_textLength;
    mutable bool  m_lengthIsValid;
};

std::size_t CTextBlock::Length() const{
    if(!lengthIsValid){
        //赋值失败 违反了bitwise constness约束
        //textLength = strlen(pText);
        //lengthIsValid = true;

        //此时如果要强行赋值，需要将变量定义为mutable
        m_textLength = strlen(pText);
        m_lengthIsValid  = true;
    }
    return textLength;
}

//在const和non-const成员函数中避免重复
//错误例子
class Error_TextBlock{
public:
    const char& operator[](std::size_t position)const{
        //...重复代码片段1
        //...重复代码片段2
        //...重复代码片段n
        return text[position];
    }
    char& operator[](std::size_t position){
        //...重复代码片段1
        //...重复代码片段2
        //...重复代码片段n
        return text[position];
    }
    //以上除了重复代码片段外 还会产生而外的程序开销，例如:函数调用、两次return语句等
private:
    std::string text;
};

//正确例子 实现operato[]的机能一次并使用它两次，也就是说必须令其中一个调用另一个
class Success_TextBlock{
public:
    Success_TextBlock(std::string str):text(str){}
    const char& operator[](std::size_t position) const{
        //...代码片段1
        //...代码片段2
        //...代码片段n
        std::cout<<"const operator[] is calling\n";
        return text[position];
    }
    char & operator[](std::size_t position){
        //强制将non-const对象转成const对象
        const Success_TextBlock cst = static_cast<const Success_TextBlock&>(*this);

        //调用const成员函数
        const char cha = cst[position];

        //再次转成非const返回
        return const_cast<char&>(cha);
    }
private:
    std::string text;
};
void print(const Success_TextBlock &hs){
    std::cout<<hs[0]<<"\n";
}

/*重点记住:
 * 1.将某些东西声明为const可帮助编译器侦测出错误的用法。const可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体
 * 2.编译器强制实施bitwise constness,但编写程序时应该使用“概念上的常量性(logical constness--mutable关键字可打破const的局限)”
 * 3.当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本避免代码重复
 */

#endif //EFFECTIVECPP_CLAUSE03_USE_CONST_WHENEVER_POSSIBLE_HPP
