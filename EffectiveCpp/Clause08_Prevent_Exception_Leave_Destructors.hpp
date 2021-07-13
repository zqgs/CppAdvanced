//
// Created by Sea on 2021/7/13.
//

#ifndef EFFECTIVECPP_CLAUSE08_PREVENT_EXCEPTION_LEAVE_DESTRUCTORS_HPP
#define EFFECTIVECPP_CLAUSE08_PREVENT_EXCEPTION_LEAVE_DESTRUCTORS_HPP

#include <iostream>

//条款08:别让异常逃离析构函数

//例子:
class DBConnecttion{
public:
    DBConnecttion(){}
    ~DBConnecttion(){}
    //static DBConnecttion create(){};
    void close();
};

//为了确保数据库能每次使用结束后被关闭
class DBConn{
public:
    DBConn();
    ~DBConn(){
        //阻止异常传播
        try {
            db.close();
        }
        catch (...) {
            //制作运转记录，记下对close的调用失败
            std::abort();//终止程序

            //或吞下close调用发生的异常(会导致程序的明确行为)
            //...不做任何处理

            //异常阻止异常的传播方法均不是最佳
        }
    }
private:
    DBConnecttion db;
};

//为了阻止异常传播，可以将转移close的使用权
class DBConnExp{
public:
    DBConnExp():closed(false){}
    ~DBConnExp(){
        if(!closed)
        {
            try {
                db.close();
            }
            catch (...) {
                std::abort();
            }
        }
    }
    //提供对外关闭数据库的函数
    void close(){
        db.close();
        closed = true;
    }
private:
    bool closed;
    DBConnecttion db;
};


//客户调用
void CallDB()
{
    //构造
    DBConn dbc();
    //....
    //dbc执行析构DBConnecttion::close被自动调用
    //如果析构DBConnecttion::close调用异常，DBConn会传播该异常。
}

/*重点记住:
 * 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们或结束程序。
 * 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那个应该提供一个普通函数来执行该操作
 */


#endif //EFFECTIVECPP_CLAUSE08_PREVENT_EXCEPTION_LEAVE_DESTRUCTORS_HPP
