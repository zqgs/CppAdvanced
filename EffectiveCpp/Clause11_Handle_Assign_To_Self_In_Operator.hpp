//
// Created by Sea on 2021/7/14.
//

#ifndef EFFECTIVECPP_CLAUSE11_HANDLE_ASSIGN_TO_SELF_IN_OPERATOR_HPP
#define EFFECTIVECPP_CLAUSE11_HANDLE_ASSIGN_TO_SELF_IN_OPERATOR_HPP


//条款11:在operator=中处理自我赋值
//对象的自我赋值行为
/*
    class  Clause11_Widget{};
    Clause11_Widget w;
    w = w;

    //潜在的自我赋值
    a[i] = a[j];//如果i = j，这就是自我赋值
    *px = *py;//恰好px和py指向的是同一个东西，这就是自我赋值

    //两个对象只要来自同一个继承体系，基类的指针或引用就有可能指向一个派生类对象
    class Base{...};
    class Derived:public Base{...};
    void doSomething(const Base &rb,Derived *pd);//此时的ref和point就有可能是来自同一个对象

*/
//处理自我赋值异常安全问题
class BitMapp{
public:
    BitMapp& operator=(const BitMapp &mp)
    {
        *this =mp;
        return *this;
    }
};
class  Clause11_Widget{
    void swap(Clause11_Widget& rhs)
    {
        BitMapp *pbTemp = this->pb;
        this->pb = rhs.pb;
        rhs.pb = pbTemp;
    }
public:
    Clause11_Widget& operator=(const Clause11_Widget &rhs)
    {
        //例子一://假设此时rhs与this同指一个对象
        delete pb;//释放pb有风险
        pb = new BitMapp(*rhs.pb);//此处rhs.pb有可能已经被释放,缺乏自我赋值安全性

        //例子二:采用证同测试
        if(this==&rhs) return *this;
        delete pb;
        pb = new BitMapp(*rhs.pb);//如果此时BitMapp构造抛出异常，此时pb可能会变成野指针，缺乏异常安全性

        //例子三:令赋值操作符具备异常安全性其自动获得自动赋值安全性
        BitMapp* pOrig = pb;
        pb = new BitMapp(*rhs.pb);
        delete pOrig;

        //例子四:采用copy and swap技术
        Clause11_Widget temp(rhs);//值传递生成副本
        swap(temp);

        return *this;
    }

private:
    BitMapp *pb;
};

/*重点记住:
 * 确保当对象自我赋值时operator=有良好行为。其中技术包括比较"来源对象"和"目标对象"的地址、精心周到的语句顺序、以及copy-and=swap
 * 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。
 */



#endif //EFFECTIVECPP_CLAUSE11_HANDLE_ASSIGN_TO_SELF_IN_OPERATOR_HPP
