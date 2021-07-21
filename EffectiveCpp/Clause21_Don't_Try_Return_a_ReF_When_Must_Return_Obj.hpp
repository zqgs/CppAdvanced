//
// Created by Sea on 2021/7/21.
//

#ifndef EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP
#define EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP

#include <iostream>
//条款21:必须返回对象时，别试图返回其reference

//小知识:
// 1.friend的二次运算符的重载，可以限定第一个参数为const的类型
// 2.类内声明操作符须将其声明为友元函数

//例1:返回引用是错误的
class Cl21_Rational{
public:
    Cl21_Rational(int numerator,int denominator):n(numerator),d(denominator){}
    //错误1.此时ret是局部对象，在函数调用完成后已被释放，如果试图访问，那么就会发生异常(Stack栈空间)
    /*
     friend const Cl21_Rational& operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
     {
         Cl21_Rational ret(lhs.n*rhs.n,lhs.d*rhs.d);
         return ret;
     }*/
    //错误2.返回一个heap内的指针(Heap堆空间)
    /*
    friend const Cl21_Rational* operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
    {
        //一定要记得记得调用delete，如果指望调用者来调用，那么将是灾难性的。
        Cl21_Rational *ret = new Cl21_Rational(lhs.n*rhs.n,lhs.d*rhs.d);
        return ret;
    }*/
    //错误3.返回一个静态对象(静态存储区)
/*    friend const Cl21_Rational& operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
    {
        static Cl21_Rational ret(lhs.n*rhs.n,lhs.d*rhs.d);
        return ret;
    }*/
    friend bool operator==(const Cl21_Rational& lhs,const Cl21_Rational &rhs){
        if(lhs.d==rhs.d&&lhs.n==lhs.n)
            return true;
        return false;
    }
    //正确调用,付出的代价是一个析构和一个构造，使用inline降低析构和构造带来的成本
    friend inline const Cl21_Rational operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
    {
        return Cl21_Rational(lhs.n*rhs.n,lhs.d*rhs.d);
    }

private:
    int n,d;//分子和分母
};


void Cl21_Test01()
{
    Cl21_Rational a(1,2),b(1,3),c(1,4),d(1,5);
    if((a*b)==(c*d)){
        std::cout<<"a*b = c*d\n";
    }
    else{
        std::cout<<"a*b != c*d\n";
    }
    //发现 a,b,c,d无论如何修改值，operator==永远都返回true，正是返回reference static造成了这一现象。
    //ret是static,它是被共用的,a*b确实修改了ret,但c*d修改ret的同时也覆盖掉了a*b计算出的值，所以operator==永远都返回true。
}


/*重点记住:
 * 1.绝对不要返回指针或引用指向一个局部栈对象或返回引用指向一个堆内对象，或返回指针或引用
 *指向一个局部栈对象而且有可能同时需要多个这样的对象。条款04在单线程环境中合理返回reference
 *指针一个loacl static对象。
 */
#endif //EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP
