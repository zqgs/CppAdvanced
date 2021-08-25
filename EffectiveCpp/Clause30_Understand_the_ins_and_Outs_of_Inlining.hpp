//
// Created by Sea on 2021/8/23.
//

#ifndef EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP
#define EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP

#include <iostream>
#include <string>
//条款30:透彻了解inlining的里里外外

//inline函数:编译器最佳优化机制通常被设计用来浓缩"不含函数调用"的代码
//inline函数背后的整体观念是，将"对此函数的每一个调用"，都以函数本体替换。像极了#define,但后果就是增加目标码的大小(代码膨胀)


//inline的使用:隐喻声明和显式声明
//例子1:
class Cl30_Person{
public:
    int age(){return theAge;} //隐喻声明:被定义于class定义式内
private:
    int theAge;
};

//显式声明:inline关键字
template <typename T>
inline const T& CL30_max(const T& a,const T& b)
{
    return a < b ? b : a;
}

//不要误以为template function必须是inline函数
//C++非托管代码使用inline函数绝大多数情况都在编译过程中进行inlining。因为将一个"函数调用"替换为"被调用的函数本体"，编译器必须知道函数长什么样子。
//C++托管代码(CLI:公共语言基础支持),该种环境可以在运行期完成inlining。CLI是例外，inlining在绝大数C++程序中都是编译期的行为

//template通常被声明在头文件内,当它一旦被使用，编译器会将它具现化。注意:template的具现化与inlining无关。应该根据函数情况决定template function是否需要inline

//  大部分编译器拒绝过于复杂的函数(比如内含循环或者递归)inlining。对于所有virtual函数(除非是最单调的)的调用也会使inline落空，virtual意味着"等待",直
//到运行期才决定调用哪个函数，inline意味着"执行前，先将调用动作替换为被调用函数的本体"，当编译器不知道virtual将会调用哪个函数时，就能解释为什
//么inline函数会落空了


//例子2:以下情况会有可能导致inline失效
inline void f(){}
void (*pf)() = f;
void Cl30_test01()
{
    f();//正常调用，这个调用将被inline
    pf();//这个调用或许不被inline，因为它通过函数指针完成调用
}


//例子3:为什么构造函数和析构函数不适合inlining
class Cl30_Base{
public:
    Cl30_Base(){}
private:
    std::string bm1,bm2;
};
class Cl30_Derived: public Cl30_Base{
public:
    Cl30_Derived();//看似这个构造是空的，但这个构造里面不一定是空的
private:
    std::string dm1,dm2,dm3;
};

/*  了解一下C++的"对象被创建和被销毁时发生了什么事"?
 *答:当使用new,动态创建的对象被其构造函数自动初始化;当使用delete,对应的析构函数会被调用。当创建一个对象，其每一个基类及成员变量都会被
 *自动构造(构造行为由基类发生至派生类结束);当销毁一个对象，反向程序的析构行为也会自动发生(析构行为由派生类发生至基类结束)。如果此时构造
 *期间有一个异常被抛出,那么已构造完成的部分将会被销毁。
 */

//以下就是Cl30_Derived构造内部发生的事
Cl30_Derived::Cl30_Derived()
{
    //伪代码实现
    //Cl30_Base::Cl30_Base(); 初始化基类成分,调用基类构造

    try{
        dm1.std::string::string();  //试图尝试构造dm1
    }
    catch (...) {
        //抛出异常
        Cl30_Base::~Cl30_Base();//销毁基类成分
        throw ;                          //传播该异常
    }

    try{
        dm2.std::string::string();  //试图尝试构造dm2
    }
    catch (...) {
        //抛出异常
        dm1.std::string::~string();//销毁dm1
        Cl30_Base::~Cl30_Base();//销毁基类成分
        throw ;                           //传播该异常
    }

    try{
        dm3.std::string::string();  //试图尝试构造dm3
    }
    catch (...) {
        //抛出异常
        dm1.std::string::~string();//销毁dm1
        dm2.std::string::~string();//销毁dm2
        Cl30_Base::~Cl30_Base();//销毁基类成分
        throw ;                           //传播该异常
    }
    //以上这段代码大致描述的派生构造内发生的事,事实上编译会以更精致复杂的做法来处理异常。但也能准确反应除派生类空白构造函数内产生的行为
}

/*重点记住:
 *  1.将大多数inline限制在小型、被频繁调用的函数身上。可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，
 *使程序的速度提升机会最大化。
 *  2.不要只因为function template出现在头文件，就将他门声明为inline
 */




#endif //EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP
