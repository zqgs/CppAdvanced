//
// Created by Sea on 2021/9/22.
//

#ifndef EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP
#define EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP

#include <iostream>
#include <memory>
//条款44:将参数无关的代码抽离template


//例子1:template代码膨胀
template <typename T,std::size_t n>
class Cl44_SquareMatrix{
public:
    void invert(){std::cout<<"SquareMatrix::invert\n";}//求逆矩阵
};
void Cl44_test01()
{
    Cl44_SquareMatrix<int,5> sm1;
    sm1.invert();
    Cl44_SquareMatrix<double,10> sm2;
    sm2.invert();
    //除了5和10不同之外，两个函数的其他部分是完全一样的。
}

//例子2:怎么解决例子1的代码膨胀问题。答:提取公共部分
template <typename T>
class Cl44_SquareMatrixBase{
public:
    void invert(std::size_t n){std::cout<<"Cl44_SquareMatrixBase::invert:size:"<<n<<"\n";}//求逆矩阵
};

template <typename T,std::size_t n>
class Cl44_SquareMatrix_Exp1:
        private Cl44_SquareMatrixBase<T>//这里的基类是为了帮助派生类实现，不是为了表现is-a关系
{
public:
    void invert(){this->invert(n);}
private:
    using Cl44_SquareMatrixBase<T>::invert;
};

void Cl44_test02()
{
    Cl44_SquareMatrix_Exp1<int,5> sm1;
    sm1.invert();
}

//例子3:例子2解决了代码膨胀的问题，却不知道怎么操作数据。
template<typename T>
class Cl44_SquareMatrixBase_Exp1{
public:
    Cl44_SquareMatrixBase_Exp1(std::size_t n,T* pMem):size(n),pData(pMem){}
    void setDataPtr(T* ptr){pData = ptr;}
    void invert(){std::cout<<"Cl44_SquareMatrixBase::invert:size:"<<size<<"\n";}//求逆矩阵
private:
   //如果使用数组自身不需要分配内存，但对象自身可能非常大。所以使用智能指针，把数据放入heap
   std::size_t size;
    T* pData;
};
template <typename T,std::size_t n>
class Cl44_SquareMatrix_Exp2:
        private Cl44_SquareMatrixBase_Exp1<T>//这里的基类是为了帮助派生类实现，不是为了表现is-a关系
{
public:
    Cl44_SquareMatrix_Exp2():Cl44_SquareMatrixBase_Exp1<T>(n,0),pData(new T[n*n]){this->setDataPtr(pData.get());}
    void invert(){Cl44_SquareMatrixBase_Exp1<T>::invert();}
private:
    std::shared_ptr<T> pData;
};
void Cl44_test03()
{
    Cl44_SquareMatrix_Exp2<int,5> sm1;
    sm1.invert();
}

//Working Set:是指一个在"虚内存环境"下执行的进程而言，其所使用的那一组内存页。

/*重点记住:
 *  1.Template生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系。
 *  2.因非类型模板参数造成的代码膨胀，往往可以消除。做法是以函数函数或class成员变量替换template参数
 *  3.因类型参数而造成的代码膨胀，往往可降低。做法是让带有完全相同二进制表示的具现类型共享实现码。
 */

#endif //EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP
