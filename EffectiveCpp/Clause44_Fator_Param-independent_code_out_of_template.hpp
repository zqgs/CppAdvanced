//
// Created by Sea on 2021/9/22.
//

#ifndef EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP
#define EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP

#include <iostream>
#include <memory>
//����44:�������޹صĴ������template


//����1:template��������
template <typename T,std::size_t n>
class Cl44_SquareMatrix{
public:
    void invert(){std::cout<<"SquareMatrix::invert\n";}//�������
};
void Cl44_test01()
{
    Cl44_SquareMatrix<int,5> sm1;
    sm1.invert();
    Cl44_SquareMatrix<double,10> sm2;
    sm2.invert();
    //����5��10��֮ͬ�⣬����������������������ȫһ���ġ�
}

//����2:��ô�������1�Ĵ����������⡣��:��ȡ��������
template <typename T>
class Cl44_SquareMatrixBase{
public:
    void invert(std::size_t n){std::cout<<"Cl44_SquareMatrixBase::invert:size:"<<n<<"\n";}//�������
};

template <typename T,std::size_t n>
class Cl44_SquareMatrix_Exp1:
        private Cl44_SquareMatrixBase<T>//����Ļ�����Ϊ�˰���������ʵ�֣�����Ϊ�˱���is-a��ϵ
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

//����3:����2����˴������͵����⣬ȴ��֪����ô�������ݡ�
template<typename T>
class Cl44_SquareMatrixBase_Exp1{
public:
    Cl44_SquareMatrixBase_Exp1(std::size_t n,T* pMem):size(n),pData(pMem){}
    void setDataPtr(T* ptr){pData = ptr;}
    void invert(){std::cout<<"Cl44_SquareMatrixBase::invert:size:"<<size<<"\n";}//�������
private:
   //���ʹ������������Ҫ�����ڴ棬������������ܷǳ�������ʹ������ָ�룬�����ݷ���heap
   std::size_t size;
    T* pData;
};
template <typename T,std::size_t n>
class Cl44_SquareMatrix_Exp2:
        private Cl44_SquareMatrixBase_Exp1<T>//����Ļ�����Ϊ�˰���������ʵ�֣�����Ϊ�˱���is-a��ϵ
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

//Working Set:��ָһ����"���ڴ滷��"��ִ�еĽ��̶��ԣ�����ʹ�õ���һ���ڴ�ҳ��

/*�ص��ס:
 *  1.Template���ɶ��classes�Ͷ�������������κ�template���붼������ĳ��������͵�template��������������ϵ��
 *  2.�������ģ�������ɵĴ������ͣ����������������������Ժ���������class��Ա�����滻template����
 *  3.�����Ͳ�������ɵĴ������ͣ������ɽ��͡��������ô�����ȫ��ͬ�����Ʊ�ʾ�ľ������͹���ʵ���롣
 */

#endif //EFFECTIVECPP_CLAUSE44_FATOR_PARAM_INDEPENDENT_CODE_OUT_OF_TEMPLATE_HPP
