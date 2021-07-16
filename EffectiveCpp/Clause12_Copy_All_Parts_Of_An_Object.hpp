//
// Created by Sea on 2021/7/15.
//

#ifndef EFFECTIVECPP_CLAUSE12_COPY_ALL_PARTS_OF_AN_OBJECT_HPP
#define EFFECTIVECPP_CLAUSE12_COPY_ALL_PARTS_OF_AN_OBJECT_HPP

#include <iostream>

//条款12:赋值对象时勿忘其每一个成分
//普通赋值
void LogCall(const std::string &funName){
    std::cout<<funName.c_str()<<std::endl;
}
//例子1:完整的copy赋值
class Customer {
public:
    Customer(const Customer &rhs):name(rhs.name){
        LogCall("Customer copy constructor");
    }
    Customer& operator=(const Customer &rhs)
    {
        LogCall("Cust copy assignment operator");
        name = rhs.name;
        return *this;
    }

private:
    std::string name;
};

//例子2：现在加入日期
class Date{};
class CustomerExp1{
public:
    CustomerExp1(){}
    CustomerExp1(const CustomerExp1 &rhs):name(rhs.name){
        LogCall("CustomerExp1 copy constructor");
    }
    CustomerExp1& operator=(const CustomerExp1 &rhs)
    {
        LogCall("CustomerExp1 copy assignment operator");
        name = rhs.name;
        return *this;
    }
private:
    Date lastTransaction;
    std::string name;
};
//发生继承
class PriorityCustomerExp1: public CustomerExp1{
public:
    //错误示例 不完全拷贝，只实现自身的拷贝
    /*
    PriorityCustomerExp1(const PriorityCustomerExp1 & rhs):priority(rhs.priority){
        LogCall("PriorityCustomerExp1 copy constructor");
    }
    PriorityCustomerExp1& operator=(const PriorityCustomerExp1& rhs){
        LogCall("PriorityCustomerExp1 copy constructor");
        this->priority = rhs.priority;
        return *this;
    }
     */

    //正确示例 调用基类赋值函数 实现完全拷贝
    PriorityCustomerExp1(const PriorityCustomerExp1 & rhs):
    CustomerExp1(rhs),
    priority(rhs.priority)
    {
        LogCall("PriorityCustomerExp1 copy constructor");
    }
    PriorityCustomerExp1& operator=(const PriorityCustomerExp1& rhs)
    {
        LogCall("PriorityCustomerExp1 copy constructor");
        this->priority = rhs.priority;
        CustomerExp1::operator=(rhs);//调用基类成分赋值
        return *this;
    }
private:
    int priority;
};

/*重点记住:
 * Copying函数应该确保复制"对象内的所有成员变量"及"所有base class成分"。
 * 不要尝试以某个copying函数实现另一个copying函数。应该将共同机能放进第三个函数中，并由两个copying函数共同调用。
 */


#endif //EFFECTIVECPP_CLAUSE12_COPY_ALL_PARTS_OF_AN_OBJECT_HPP
