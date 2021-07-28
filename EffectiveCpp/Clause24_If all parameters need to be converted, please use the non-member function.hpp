//
// Created by Sea on 2021/7/27.
//

#ifndef EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP
#define EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP

#include <iostream>

//����24:�����в�������Ҫ����ת������Ϊ�˲���non-member����

//ֱ�ӿ�����:
class Rational{
public:
    Rational(int _Numerator =0,int _Denominator =1):num(_Numerator),dem(_Denominator){}//��������ʽת��
    //���ӷ�ĸ�÷��ʺ���
    int numerator()const{return num;}
    int demerator()const{return dem;}

    //�����������
    const Rational operator*(const Rational& rhs)const;
private:
    int num;
    int dem;
};

//�����֧������������ӷ����˷��ȣ�����ȷ���Ƿ����member������non-member��non-member friend������ʵ�֡�

//�����������:��class��ʵ��
const Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(rhs.num*this->num,rhs.dem*this->dem);
}

void Cl24_test01()
{
    //����������������Ƴ�������������ʹ��
    Rational oneEighth(1,8);
    Rational oneHalf(1,2);
    Rational result = oneEighth*oneHalf;
    result = result * oneEighth;
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";

    //���ܻ����������ϲ�����ϣ��֧�ֻ�����㡣
    result = result * 2;//��ȷ����
    //˼��:result = result * 2 �˲���Ϊʲô��ɹ���
    //��ΪRational�Ĺ��첢û������explicit,˵���˹�����֧����ʽת�����൱��result = result * Rational(2),�ڶ�������ȱʡĬ��Ϊ1
    //����Rational��operator*����֧����ʽת����result = result * 2���Գɹ��ˡ�


    //result = 2 * result;//���󣡣�
    //˼��:result = 2 * result  �˲���Ϊʲô�ᱨ��
    //��Ϊ��������ز���������������������operator����2ȥ����operator*ʱ����ʧ�ܣ����Ծͻᱨ��
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";


    //˼��:Ϊʲô�����һ���ɹ�(result = result * 2)��һ��ʧ��(result = 2 * result)�������
    //��Ϊֻ�е����������ڲ������ڣ��������������ʽ����ת���ĺϸ�����ߡ���λ�൱��"�����õĳ�Ա��
    //�������Ǹ�����"-----��this������Ǹ�����������������ʽת���ϸ�Ĳ����ߡ����ԲŻ��������������
}

//�����ǿ��ȻRational֧�ֻ��������ô�죿����ֻ��Ҫ��operator*����Ϊnon-member�������ɡ�
class RationalExp1{
public:
    RationalExp1(int _Numerator =0,int _Denominator =1):num(_Numerator),dem(_Denominator){}//��������ʽת��
    //���ӷ�ĸ�÷��ʺ���
    int numerator()const{return num;}
    int demerator()const{return dem;}
private:
    int num;
    int dem;
};

//��class��ʵ�� non-member
const RationalExp1 operator*(const RationalExp1& lhs,const RationalExp1& rhs)
{
    return RationalExp1(rhs.numerator()*lhs.numerator(),rhs.demerator()*lhs.demerator());
}

void Cl24_test02()
{
    RationalExp1 oneFourth(1,4);
    RationalExp1 result = oneFourth * 2;//��ȷ
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";
    result = 2 * result;//��ȷ
    std::cout<<result.numerator()<<"/"<<result.demerator()<<"\n";
}

//���������operator* non-member�����Ƿ�Ӧ�ó�ΪRationalExp1����Ԫ�����أ�
//��:��ʵ��Ȼ����Ԫ����߷���Ȩ�޽��ͷ�װ�Ե�һ�������������еĺ����ܹ����ʵ�����Դ�ܹ�����ʹ������ʱ��û�б�Ҫ��
//������Ϊclass����Ԫ����.

/*�ص��ס:
 * 1.�������ҪΪĳ�����������в���(����thisָ����ָ�����������)��������ת������ô������������Ǹ�non-member
 */

#endif //EFFECTIVECPP_CLAUSE24_IF_ALL_PARAMETERS_NEED_TO_BE_CONVERTED_PLEASE_USE_THE_NON_MEMBER_FUNCTION_HPP
