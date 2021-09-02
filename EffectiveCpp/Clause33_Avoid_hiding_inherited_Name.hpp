//
// Created by Sea on 2021/9/1.
//

#ifndef EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP
#define EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP

#include <iostream>
//����33:�������ڼ̳ж���������


//����1:������(�ڲ��������)
int cl33_x;//ȫ�ֱ���(��������)
void Cl33_someFunc(){
    double cl33_x;//�ֲ�����(��������),�ڲ����ƻ������������
    std::cin>>cl33_x;
}
/*---------------------------------------
 *|ȫ��������  int cl33_x               |
 *|                   ______________  |
 *|                  |Cl33_someFunc    |
 *|                  |     double cl33_x |
 *----------------------------------------
 */

//����2:����̳�֮���������仯
class Cl33_Base{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf2(){std::cout<<"Cl33_Base::mf2\n";}
    void mf3(){std::cout<<"Cl33_Base::mf3\n";}
};
class Cl33_Derived:
        public Cl33_Base{
public:
    virtual void mf1(){std::cout<<"Cl33_Derived::mf1\n";}
    void mf4(){mf2();}
};

void Cl33_test01()
{
    Cl33_Derived cl33d;
    cl33d.mf1();
    cl33d.mf3();
    cl33d.mf4();
}
//���������Ʋ��ҹ���:���Ȳ�������Χ������,����class Derived���ǵ����������û�ҵ��ͼ��������ƶ����ң������ֵ�class Base��
//������Ҳ�����������Base��namespace������������ȫ��������


//����3:
class Cl33_BaseExp1{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf1(int ){std::cout<<"Cl33_BaseExp1::mf1(int)\n";}
    virtual void mf2(){std::cout<<"Cl33_BaseExp1::mf2\n";}
    void mf3(){std::cout<<"Cl33_BaseExp1::mf3\n";}
    void mf3(double ){std::cout<<"Cl33_BaseExp1::mf3(int)\n";}
};
class Cl33_DerivedExp1:
        public Cl33_BaseExp1{
public:
    virtual void mf1(){std::cout<<"Cl33_DerivedExp1::mf1\n";}
    void mf3(){std::cout<<"Cl33_DerivedExp1::mf3\n";}
    void mf4(){std::cout<<"Cl33_DerivedExp1::mf4\n";}
};

void Cl33_test02()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp1 cl33dexp1;
    cl33dexp1.mf1();
    //cl33dexp1.mf1(x);���ֵ���ʧ�ܣ���Ȼ���Ҳ����ӻ���̳еĺ���,����������Derived(������)����mf3������һ����Ϊmf3�����Ͳ�ͨ��Base(����)����
    cl33dexp1.mf2();
    cl33dexp1.mf3();
    //cl33dexp1.mf3(y);ͬmf1(int)һ��
    cl33dexp1.mf4();
}
//��ô�������������Ϊ����:��Ϊ�˷�ֹ�ڳ�����Ӧ�ÿ���ڽ����µ�������ʱ�����ӻ���̳����غ�����
//��˼��:�������غ����Ǽ̳е�������ģ����Ǳ������ˡ���ʵ��,�������ʹ��public�̳��ֲ��̳���Щ���غ�������Ȼ��Υ��������31��is-a��ϵ�ġ�

//����4:�������3�Ļ������غ�����������ͬ��������������
class Cl33_BaseExp2{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf1(int ){std::cout<<"Cl33_BaseExp2::mf1(int)\n";}
    virtual void mf2(){std::cout<<"Cl33_BaseExp2::mf2\n";}
    void mf3(){std::cout<<"Cl33_BaseExp2::mf3\n";}
    void mf3(double ){std::cout<<"Cl33_BaseExp2::mf3(int)\n";}
};
class Cl33_DerivedExp2:
        public Cl33_BaseExp2{
public:
    using Cl33_BaseExp2::mf1;//��Base class����Ϊmf1��mf3�����ж���������Derived�������ڿɼ�(��public)
    using Cl33_BaseExp2::mf3;
    virtual void mf1(){std::cout<<"Cl33_DerivedExp2::mf1\n";}
    void mf3(){std::cout<<"Cl33_DerivedExp2::mf3\n";}
    void mf4(){std::cout<<"Cl33_DerivedExp2::mf4\n";}
};

void Cl33_test03()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp2 cl33dexp1;
    cl33dexp1.mf1();
    cl33dexp1.mf1(x);//�ɹ�
    cl33dexp1.mf2();
    cl33dexp1.mf3();
    cl33dexp1.mf3(y);//�ɹ�
    cl33dexp1.mf4();
}

//����4:���̳й�ϵ��privateʱ���ֻᷢ��ʲô�£�
class Cl33_BaseExp3{
public:
    virtual void mf1() =0;
    virtual void mf1(int){std::cout<<"Cl33_BaseExp3::mf1(int)\n";}
};
class Cl33_DerivedExp:
        private Cl33_BaseExp3{
public:
    //ʹ��using�û������غ������������б�¶
    //using Cl33_BaseExp3::mf1;
    //virtual void mf1(){std::cout<<"Cl33_DerivedExp::mf1()\n";}

    //������usingʱ Ӧ����ô���û������غ����أ�
    virtual void mf1(){Cl33_BaseExp3::mf1(1);}//inlineת������
};

void Cl33_test04()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp cl33dexp1;
    cl33dexp1.mf1();
   // cl33dexp1.mf1(x);//û��ʹ��usingsʱʧ��,��Ϊ���غ������ܱ��̳�
}

//inlineת����������һ����;��Ϊ��Щ��֧��using����ʽ���Ͼɱ��������ٵ���һ����·�����̳ж��õ����ƻ����������������ڡ�
/*�ص��ס:
 *  1.derived classes�ڵ����ƻ�����base classes�ڵ����ơ�(�������غ����Ǽ̳е�������ģ����Ǳ������ˡ����Կ���������û���̳�һ��)
 *  2.Ϊ�����û��౻���ڵ��������֣���������using����ʽ��ת��������
 */


#endif //EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP
