//
// Created by Sea on 2021/9/15.
//

#ifndef EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP
#define EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP

#include <iostream>
//����41:�˽���ʽ�ӿںͱ�������̬

//����1:�˽���ʾ�ӿں���ʽ�ӿ�
class Cl41_Widget{
public:
    virtual void
    Show() =0;
    virtual
    ~Cl41_Widget(){}
};

class Cl41_ScWin: public Cl41_Widget{
public:
     void
     Show() override
     {std::cout<<"Cl41_ScWin::Show\n";}
};
class Cl41_BcWin: public Cl41_Widget{
public:
    void Show()
    override
    {std::cout<<"Cl41_BcWin::Show\n";}
};

//����ʱ��̬������virtual������ʵ��
void
Cl41_test01()
{

    Cl41_Widget*p1 = new Cl41_ScWin();
    Cl41_Widget*p2 = new Cl41_BcWin();
    p1->Show();
    p2->Show();
    delete p1;
    delete p2;
}

//����ʱ��̬:ͨ��ģ����ֻ��ͺ������ؽ���ʵ��
template<typename T>
void
Cl41_DoProcessing(T& w)
{
    w.Show();
}
void
Cl41_test02()
{
    Cl41_ScWin sc1;
    Cl41_ScWin sc2;
    Cl41_BcWin bc1;

    Cl41_DoProcessing(sc1);
    Cl41_DoProcessing(sc2);
    Cl41_DoProcessing(bc1);
}

/*  �����ڶ�̬������ڶ�̬��ȱ��:
 *�����ڶ�̬�ŵ�:
 * 1.OO����е���Ҫ����,�Կ͹������ֱ����ʶ��
 * 2.�ܹ�����ͬһ���̳���ϵ�µ����༯�ϡ�
 *�����ڶ�̬��ȱ��:
 * 1.�����ڽ����麯���󶨣�����˳������п���
 * 2.�Ӵ����̳в�Σ��Խӿڵ��޸�����Ӱ����̳в��
 * 3.�����麯���������ڲ�ȷ�������Ա������޷����麯�������Ż���
 * 4.�麯����ָ����������������Ҳ����һ���麯��������������Ȼ����Դ���ġ�
 *�����ڶ�̬�ŵ�:
 * 1.���ͱ�̵����֣�ʹ��C++ӵ�з��ͱ�̺�STL��ǿ���
 * 2.�ڱ�������ɶ�̬���������Ч��
 * 3.���к�ǿ�������Ժ�������ԣ������������Ϳ���ģ��ƫ�ػ���ȫ�ػ�������
 *�����ڶ�̬ȱ��:
 * 1.����ɶ��Խ��ͣ�����������Ѷ�����
 * 2.�޷�ʵ��ģ�������룬�����������ʱ�򣬻Ἣ������ӱ���ʱ��
 * 3.�޷��������ʶ��󼯺ϡ�
 */

/*�ص��ס:
 *  1.classes��template��֧�ֽӿںͶ�̬��
 *  2.����classes���Խӿ�ʱ��ʽ�ģ��Ժ���ǩ��Ϊ���ġ���̬����ͨ��virtual���������������ڡ�
 *  3.����template�������ԣ��ӿ�����ʽ�ģ�������Ч���ʽʵ�֡���̬����ͨ��template���ֻ��ͺ���
 *���ؽ��������ڱ����ڡ�
 */



#endif //EFFECTIVECPP_CLAUSE41_UNDERSTAND_IMPLICIT_INTERFACE_AND_COMPILE_TIME_POLYMORPHISM_HPP
