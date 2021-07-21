//
// Created by Sea on 2021/7/21.
//

#ifndef EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP
#define EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP

#include <iostream>
//����21:���뷵�ض���ʱ������ͼ������reference

//С֪ʶ:
// 1.friend�Ķ�������������أ������޶���һ������Ϊconst������
// 2.���������������뽫������Ϊ��Ԫ����

//��1:���������Ǵ����
class Cl21_Rational{
public:
    Cl21_Rational(int numerator,int denominator):n(numerator),d(denominator){}
    //����1.��ʱret�Ǿֲ������ں���������ɺ��ѱ��ͷţ������ͼ���ʣ���ô�ͻᷢ���쳣(Stackջ�ռ�)
    /*
     friend const Cl21_Rational& operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
     {
         Cl21_Rational ret(lhs.n*rhs.n,lhs.d*rhs.d);
         return ret;
     }*/
    //����2.����һ��heap�ڵ�ָ��(Heap�ѿռ�)
    /*
    friend const Cl21_Rational* operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
    {
        //һ��Ҫ�ǵüǵõ���delete�����ָ�������������ã���ô���������Եġ�
        Cl21_Rational *ret = new Cl21_Rational(lhs.n*rhs.n,lhs.d*rhs.d);
        return ret;
    }*/
    //����3.����һ����̬����(��̬�洢��)
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
    //��ȷ����,�����Ĵ�����һ��������һ�����죬ʹ��inline���������͹�������ĳɱ�
    friend inline const Cl21_Rational operator*(const Cl21_Rational& lhs,const Cl21_Rational &rhs)
    {
        return Cl21_Rational(lhs.n*rhs.n,lhs.d*rhs.d);
    }

private:
    int n,d;//���Ӻͷ�ĸ
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
    //���� a,b,c,d��������޸�ֵ��operator==��Զ������true�����Ƿ���reference static�������һ����
    //ret��static,���Ǳ����õ�,a*bȷʵ�޸���ret,��c*d�޸�ret��ͬʱҲ���ǵ���a*b�������ֵ������operator==��Զ������true��
}


/*�ص��ס:
 * 1.���Բ�Ҫ����ָ�������ָ��һ���ֲ�ջ����򷵻�����ָ��һ�����ڶ��󣬻򷵻�ָ�������
 *ָ��һ���ֲ�ջ��������п���ͬʱ��Ҫ��������Ķ�������04�ڵ��̻߳����к�����reference
 *ָ��һ��loacl static����
 */
#endif //EFFECTIVECPP_CLAUSE21_DON_T_TRY_RETURN_A_REF_WHEN_MUST_RETURN_OBJ_HPP
