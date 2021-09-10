//
// Created by Sea on 2021/9/9.
//

#ifndef EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP
#define EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP

#include <iostream>

//����36:�������¶���̳ж�����non-virtual����

//ֱ�ӿ�����,��1:
class Cl36_B{
public:
    void mf(){std::cout<<"Cl36_B::mf\n";}
};
class Cl36_D: public Cl36_B{};


void Cl36_test01()
{
    Cl36_D x;
    Cl36_B* pB = &x;
    pB->mf();

    Cl36_D *pD = &x;
    pD->mf();
    //��ʱpB��pD���ֳ�����ͬ����Ϊ
}

//��2:��������������Լ�����Ϊ����ôtest01�����������ֳ�����Ϊ���ܾͲ���������
class Cl36_D1: public Cl36_B{
public:
    void mf(){std::cout<<"Cl36_D1::mf\n";}
};
void Cl36_test02()
{
    Cl36_D1 x;
    Cl36_B* pB = &x;
    pB->mf();//���õ��ǻ���

    Cl36_D1 *pD = &x;
    pD->mf();//���õ���������
    //��ʱpB��pD���ֳ��˲���ͬ����Ϊ������������ԭ����non-virtual���Ǿ�̬�󶨡�(virtual���Ƕ�̬��)
    //��̬��:pB��Զ����Cl36_B�İ汾��pD��Զ����Cl36_D1�İ汾��
    //��̬��:������pD��pB�������Cl36_D1�İ汾��
}


/*�۵�һ:����32����public�̳���ζ��is-a��ϵ��
 *�۵��:����34����class������һ��non-virtual��Ϊ���ཨ����һ������������������ԡ�
 *  ����������۵�ʩ������1��Cl36_B��Cl36_D�Լ�non-virtual��Ա����B::mf���ϣ���ôҪע��:
 *1.������B�����ÿһ���£�Ҳ������D������Ϊÿ��D������һ��B����
 *2.B��derived classesһ����̳�mf�Ľӿں�ʵ�֣���Ϊmf��B��һ��non-virtual
 *  ע��:������ĺ���������Ϊnon-virtualʱ��ζ�Ų�ϣ�������������¶��塣
 */

/*�ص��ס:
 *  1.���Բ�Ҫ���¶���̳ж�����non-virtual����
 */

#endif //EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP
