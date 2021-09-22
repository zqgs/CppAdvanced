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
        using Cl43_MsgSender<Company>::sendClear;
        sendClear(info);
        //方法3:明白指出要调用得函数在base内(这种做法不好，如果被调用的是virtual函数，明确资格修饰会关闭virtual函数的绑定行为)
        Cl43_MsgSender<Company>::sendClear(info);
    }
};

//  从名称可视点角度来看，上述的解法做的事情都相同:对编译器承诺base class template的任何特化版本都将支持一般(泛化)版本所提供的接口。
//如果承诺最终未被实现出来，那么编译器在解析的时候，最终会给你一个错误，那个错误是编译器调用动作无法通过编译。

//  根本而言，面对指涉"base class members"的无效references编译器的诊断时间可能发生再早期(当解析派生类定义式时)，也可能发生在晚期(当
//那些template被特定的template实参具现化时)。

/*重点记住:
 *  1.可在derived class template内通过"this->"指涉base class templates内的成员名称，或由一个明确指出"base class 资格修饰符"完成。
 */



#endif //EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
