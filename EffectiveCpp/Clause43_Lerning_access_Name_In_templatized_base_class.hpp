//
// Created by Sea on 2021/9/16.
//

#ifndef EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
#define EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP

#include <string>
#include <iostream>
//条款43:学习处理模块化基类内的名称

//例子1:
class Cl43_CompanyA{
public:
    void sendClearText(const std::string& msg){std::cout<<"Cl43_CompanyA::sendClearText\n";}
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyA::sendEncrypted\n";}
};
class Cl43_CompanyB{
public:
    void sendClearText(const std::string& msg){std::cout<<"Cl43_CompanyB::sendEncrypted\n";}
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyB::sendEncrypted\n";}
};
class Cl43_MsgInfo{};

template<typename Company>
class Cl43_MsgSender{
public:
    void sendClear(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Company c;
        c.sendClearText(msg);
    }
    void sendSecret(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Company c;
        c.sendEncrypted(msg);
    }
};
void Cl43_Test01()
{
    Cl43_MsgSender<Cl43_CompanyA> cMsgSend;
    Cl43_MsgInfo cMsg;
    cMsgSend.sendClear(cMsg);
}

//例子2:派生自模板类，能访问到基类的成员函数吗？
template<typename Company>
class Cl43_LoggingMsgSender: public Cl43_MsgSender<Company>{
public:
    void sendClearMsg(const Cl43_MsgInfo& info)
    {
        //sendClear(info);//报错。
        //  答案显而易见，派生自模板类，不能访问到基类的成员函数。主要因为编译器遇到class template Cl43_LoggingMsgSender时
        //并不知道它继承了什么样的class
    }
};

//例子3:来看一个更加详细的例子，深度阐明为什么派生自模板类，不能访问到基类的成员函数。
class Cl43_CompanyZ
{
public:
    //不提供sendClearText版本
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyZ::sendEncrypted\n";}
};
template <>//全特化版本，当template实参为Cl43_CompanyZ时,再也没有其他template参数可提供变化。
class Cl43_MsgSender<Cl43_CompanyZ>{
public:
    //仅提供sendSecret
    void sendSecret(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Cl43_CompanyZ c;
        c.sendEncrypted(msg);
    }
};
void Cl43_Test02()
{
    Cl43_MsgSender<Cl43_CompanyA> cMsgSend;
    Cl43_MsgInfo cMsg;
    cMsgSend.sendClear(cMsg);//一如既往。成功
    cMsgSend.sendSecret(cMsg);//一如既往。成功

    Cl43_MsgSender<Cl43_CompanyZ> cMsgSendz;
    //cMsgSendz.sendClear(cMsg);//失败。针对Cl43_CompanyZ已经特化。
    cMsgSendz.sendSecret(cMsg);//成功。调用特化版本
}

//例子4:再次考虑派生类调用基类成员函数的情况。
template<typename Company>
class Cl43_LoggingMsgSender_Exp1: public Cl43_MsgSender<Company>{
public:
    void sendClearMsg(const Cl43_MsgInfo& info)
    {
        //sendClear(info);//依旧报错。不仅搜索不到sendClear，当Company==Cl43_CompanyZ时的特化版本根本不提供这个函数。这就是为什么C++拒绝调用的原因
        //为了不让C++的调用行为失效，方法有三:
        //方法一:使用this指针
        this->sendClear(info);//成立，假设sendClear被继承。
        //方法2:使用using声明式。这里并不是基类名称被派生类名称遮掩，而是编译器不进入基类的作用域查找。
        //using Cl43_MsgSender<Company>::sendClear;
        //sendClear(info);
        //方法3:明白指出要调用得函数在base内(这种做法不好，如果被调用的是virtual函数，明确资格修饰会关闭virtual函数的绑定行为)
        //Cl43_MsgSender<Company>::sendClear(info);
    }
};

//  从名称可视点角度来看，上述的解法做的事情都相同:对编译器承诺base class template的任何特化版本都将支持一般(泛化)版本所提供的接口。
//如果承诺最终未被实现出来，那么编译器在解析的时候，最终会给你一个错误，那个错误是编译器调用动作无法通过编译。

//  根本而言，面对指涉"base class members"的无效references编译器的诊断时间可能发生再早期(当解析派生类定义式时)，也可能发生在晚期(当
//那些template被特定的template实参具现化时)。

/*重点记住:
 *  1.可在derived class template内通过"this->"指涉base class templates内的成员名称，或由一个明确指出"base class 资格修饰符"完成。
 */


//拓展:全特化与偏特化
//全特化:全特化一般用于处理有特殊要求的类或者函数，此时的泛型模板无法处理这种情况。
//对于类的全特化
template<typename T>
class Cl43_A{
public:
    bool cmp(const T& t1,const T& t2){
        return t1 == t2;
    }
};
//全特化版本
template <>
class Cl43_A<char*>{
public:
    bool cmp(const char* t1,const char* t2)
    {
        while (*t1 != '\0' && *t2 != '\0')
        {
            if(*t1 != *t2)
                return false;
            ++t1;
            ++t2;
        }
        return true;
    }
};
void Cl43_Test03()
{
    Cl43_A<int> cmp;
    std::cout<<cmp.cmp(1,2)<<std::endl;
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    Cl43_A<char*> cmp1;
    std::cout<<"c1 ? c2:"<<cmp1.cmp(c1,c2)<<"\n";
    std::cout<<"c1 ? c3:"<<cmp1.cmp(c1,c3)<<"\n";
    std::cout<<"c2 ? c3:"<<cmp1.cmp(c2,c3)<<"\n";
}

//对于函数的全特化
template <typename  T1,typename T2>
bool Cl43_cmp(T1& t1,T2& t2)
{
    return t1 == t2;
}
template<>
bool Cl43_cmp(char* &p1,char* &p2)
{
    auto ptr1 = p1,ptr2 = p2;
    while (*ptr1 != '\0' && *ptr2 != '\0')
    {
        if(*ptr1 != *ptr2)
            return false;
        ++ptr1;
        ++ptr2;
    }
    return true;
}

void Cl43_Test04()
{
    int a = 1,b=2;
    std::cout<<Cl43_cmp(a,b)<<std::endl;
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    std::cout<<"c1 ? c2:"<<Cl43_cmp(c1,c2)<<"\n";
    std::cout<<"c1 ? c3:"<<Cl43_cmp(c1,c3)<<"\n";
    std::cout<<"c2 ? c3:"<<Cl43_cmp(c2,c3)<<"\n";
}

//对于类的偏特化:
template <typename T,typename T1>
class Cl43_A1{
public:
    Cl43_A1() = default;
    Cl43_A1(const T1& n){
        std::cout<<"n:"<<n<<"\n";
    }
    bool cmp(const T& t1,const T& t2){
        return t1 == t2;
    }
};

//偏特化版本
template<typename  T>
class Cl43_A1<char*,T>{
public:
    Cl43_A1() = default;
    Cl43_A1(T& n){
        std::cout<<"n:"<<n<<"\n";
    }
    bool cmp(const char* t1,const char* t2){
        while (*t1 != '\0' && *t2 != '\0')
        {
            if(*t1 != *t2)
                return false;
            ++t1;
            ++t2;
        }
        return true;
    }
};

void Cl43_Test05()
{
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    Cl43_A1<int,char*>cc(c1);
    std::cout<<"1 == 2?:"<<cc.cmp(1,2)<<"\n";

    Cl43_A1<char*,char*> cc2(c2);
    std::cout<<"c1 == c3?:"<<cc2.cmp(c1,c3)<<"\n";
    std::cout<<"c2 == c3?:"<<cc2.cmp(c2,c3)<<"\n";
}
//函数没有偏特化，只有函数重载！！！














#endif //EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
