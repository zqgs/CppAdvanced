//
// Created by Sea on 2021/7/13.
//

#ifndef EFFECTIVECPP_CLAUSE09_NEVER_CALL_VIRTUAL_DURING_CONSTRUCT_OR_CESTRUCT_HPP
#define EFFECTIVECPP_CLAUSE09_NEVER_CALL_VIRTUAL_DURING_CONSTRUCT_OR_CESTRUCT_HPP

#include <iostream>
#include <string>
//条款09:绝不再构造和析构过程钟调用virtual函数
//知识点1:派生类对象内得基类成分回在派生类自身成分被构造之前先构造妥当
//知识点2:基类构造期间virtual不会下降到派生类阶层。"在基类构造期间，virtual函数不是virtual函数"

//举例 由基类向下调用
class Transaction{
public:
    //构造内调用虚函数
    Transaction(){logTransaction();}
    virtual void logTransaction() const = 0;
};
void Transaction::logTransaction() const
{
    std::cout<<"Transaction::logTransaction\n";
}

class BuyTransaction: public Transaction{
public:
    virtual void logTransaction() const;
};
void BuyTransaction::logTransaction() const {
    std::cout<<"BuyTransaction::logTransaction\n";
}
void ErrCallTransaction(){
    BuyTransaction b;
    //当实例化一个BuyTransaction对象时，首先触发基类的构造，当基类被构造出来时，才会触发派生类构造。
    //当基类还在构造时，虚函数还没被触发继承(复制)行为。此时虚函数只是个普通的基类函数
    //所以此时b构造调用的函数是基类的成员函数(Transaction::logTransaction)，而非派生类的函数(BuyTransaction::logTransaction)
}


//举例 由派生类向上调用
class TransactionExp{
public:
    explicit TransactionExp(const std::string & logInfo);
    void logTransaction(const std::string & logInfo) const
    {
        std::cout<<"LogInfo:"<<logInfo<<std::endl;
    }
};
TransactionExp::TransactionExp(const std::string &logInfo) {
    logTransaction(logInfo);
}

class BuyTransactionExp: public TransactionExp
{
public:
    BuyTransactionExp(const std::string &Info):
            TransactionExp(createLogString(Info)){
    }
private:
    static std::string createLogString(const std::string &Info){
        return "createLogString:"+Info;
    }
};
void ErrCallTransactionExp(){
    //BuyTransactionExp b("error!!!!");
    TransactionExp *t = dynamic_cast<TransactionExp *>(new BuyTransactionExp("OK!"));
}

/*重点记住:
 * 在构造期间不要调用virtual函数，因为这个类(相对当前执行构造函数和析构函数的类)调用从不下降至派生类
 */

#endif //EFFECTIVECPP_CLAUSE09_NEVER_CALL_VIRTUAL_DURING_CONSTRUCT_OR_CESTRUCT_HPP
