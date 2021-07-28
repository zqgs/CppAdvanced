//
// Created by Sea on 2021/7/27.
//

#ifndef EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP
#define EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP

#include <iostream>

//条款24:若所有参数皆需要类型转换，请为此采用non-member函数

//直接看例子:
class Rational{
public:
    Rational(int _Numerator =0,int _Denominator =1):num(_Numerator),dem(_Denominator){}//允许构造隐式转换
    //分子分母得访问函数
    int numerator()const{return num;}
    int demerator()const{return dem;}

    //面向对象守则
    const Rational operator*(const Rational& rhs)const;
private:
    int num;
    int dem;
};

//如果想支持算数运算如加法、乘法等，但不确定是否该由member函数、non-member或non-member friend函数来实现。

//面向对象守则:在class中实现
const Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(rhs.num*this->num,rhs.dem*this->dem);
}

void Cl24_test01()
{
    //根据面向对象规则设计出来，可以这样使用
    Rational oneEighth(1,8);
    Rational oneHalf(1,2);
    Rational result = oneEighth*oneHalf;
    result = result * oneEighth;
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";

    //可能还不满足以上操作，希望支持混合运算。
    result = result * 2;//正确！！
    //思考:result = result * 2 此操作为什么会成功？
    //因为Rational的构造并没有声明explicit,说明此构造是支持隐式转换的相当于result = result * Rational(2),第二个参数缺省默认为1
    //由于Rational有operator*加上支持隐式转换，result = result * 2所以成功了。


    //result = 2 * result;//错误！！
    //思考:result = 2 * result  此操作为什么会报错？
    //因为操作符相关操作都会索引操作符函数operator，当2去索引operator*时索引失败，所以就会报错。
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";


    //思考:为什么会出现一个成功(result = result * 2)和一个失败(result = 2 * result)的情况？
    //因为只有当参数被列于参数列内，这个参数才是隐式类型转换的合格参与者。地位相当于"被调用的成员所
    //隶属的那个对象"-----即this对象的那个隐喻参数绝不是隐式转换合格的参与者。所以才会出现上面的情况。
}

//如果想强行然Rational支持混合运算怎么办？我们只需要将operator*声明为non-member函数即可。
class RationalExp1{
public:
    RationalExp1(int _Numerator =0,int _Denominator =1):num(_Numerator),dem(_Denominator){}//允许构造隐式转换
    //分子分母得访问函数
    int numerator()const{return num;}
    int demerator()const{return dem;}
private:
    int num;
    int dem;
};

//在class外实现 non-member
const RationalExp1 operator*(const RationalExp1& lhs,const RationalExp1& rhs)
{
    return RationalExp1(rhs.numerator()*lhs.numerator(),rhs.demerator()*lhs.demerator());
}

void Cl24_test02()
{
    RationalExp1 oneFourth(1,4);
    RationalExp1 result = oneFourth * 2;//正确
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";
    result = 2 * result;//正确
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";
}

//关于上面的operator* non-member函数是否应该成为RationalExp1的友元函数呢？
//答案:其实不然，友元是提高访问权限降低封装性的一种做法。当现有的函数能够访问到的资源能够满足使用需求时，没有必要将
//其声明为class的友元函数.

/*重点记住:
 * 1.如果你需要为某个函数的所有参数(包括this指针所指向的隐喻参数)进行类型转换，那么这个函数必须是个non-member
 */

#endif //EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP
