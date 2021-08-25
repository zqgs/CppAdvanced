//
// Created by Sea on 2021/8/23.
//

#ifndef EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP
#define EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP

#include <iostream>
#include <string>
//����30:͸���˽�inlining����������

//inline����:����������Ż�����ͨ�����������Ũ��"������������"�Ĵ���
//inline�����������������ǣ���"�Դ˺�����ÿһ������"�����Ժ��������滻������#define,�������������Ŀ����Ĵ�С(��������)


//inline��ʹ��:������������ʽ����
//����1:
class Cl30_Person{
public:
    int age(){return theAge;} //��������:��������class����ʽ��
private:
    int theAge;
};

//��ʽ����:inline�ؼ���
template <typename T>
inline const T& CL30_max(const T& a,const T& b)
{
    return a < b ? b : a;
}

//��Ҫ����Ϊtemplate function������inline����
//C++���йܴ���ʹ��inline�����������������ڱ�������н���inlining����Ϊ��һ��"��������"�滻Ϊ"�����õĺ�������"������������֪��������ʲô���ӡ�
//C++�йܴ���(CLI:�������Ի���֧��),���ֻ������������������inlining��CLI�����⣬inlining�ھ�����C++�����ж��Ǳ����ڵ���Ϊ

//templateͨ����������ͷ�ļ���,����һ����ʹ�ã��������Ὣ�����ֻ���ע��:template�ľ��ֻ���inlining�޹ء�Ӧ�ø��ݺ����������template function�Ƿ���Ҫinline

//  �󲿷ֱ������ܾ����ڸ��ӵĺ���(�����ں�ѭ�����ߵݹ�)inlining����������virtual����(�����������)�ĵ���Ҳ��ʹinline��գ�virtual��ζ��"�ȴ�",ֱ
//�������ڲž��������ĸ�������inline��ζ��"ִ��ǰ���Ƚ����ö����滻Ϊ�����ú����ı���"������������֪��virtual��������ĸ�����ʱ�����ܽ���Ϊʲ
//ôinline�����������


//����2:����������п��ܵ���inlineʧЧ
inline void f(){}
void (*pf)() = f;
void Cl30_test01()
{
    f();//�������ã�������ý���inline
    pf();//������û�����inline����Ϊ��ͨ������ָ����ɵ���
}


//����3:Ϊʲô���캯���������������ʺ�inlining
class Cl30_Base{
public:
    Cl30_Base(){}
private:
    std::string bm1,bm2;
};
class Cl30_Derived: public Cl30_Base{
public:
    Cl30_Derived();//������������ǿյģ�������������治һ���ǿյ�
private:
    std::string dm1,dm2,dm3;
};

/*  �˽�һ��C++��"���󱻴����ͱ�����ʱ������ʲô��"?
 *��:��ʹ��new,��̬�����Ķ����乹�캯���Զ���ʼ��;��ʹ��delete,��Ӧ�����������ᱻ���á�������һ��������ÿһ�����༰��Ա�������ᱻ
 *�Զ�����(������Ϊ�ɻ��෢�������������);������һ�����󣬷�������������ΪҲ���Զ�����(������Ϊ�������෢�����������)�������ʱ����
 *�ڼ���һ���쳣���׳�,��ô�ѹ�����ɵĲ��ֽ��ᱻ���١�
 */

//���¾���Cl30_Derived�����ڲ���������
Cl30_Derived::Cl30_Derived()
{
    //α����ʵ��
    //Cl30_Base::Cl30_Base(); ��ʼ������ɷ�,���û��๹��

    try{
        dm1.std::string::string();  //��ͼ���Թ���dm1
    }
    catch (...) {
        //�׳��쳣
        Cl30_Base::~Cl30_Base();//���ٻ���ɷ�
        throw ;                          //�������쳣
    }

    try{
        dm2.std::string::string();  //��ͼ���Թ���dm2
    }
    catch (...) {
        //�׳��쳣
        dm1.std::string::~string();//����dm1
        Cl30_Base::~Cl30_Base();//���ٻ���ɷ�
        throw ;                           //�������쳣
    }

    try{
        dm3.std::string::string();  //��ͼ���Թ���dm3
    }
    catch (...) {
        //�׳��쳣
        dm1.std::string::~string();//����dm1
        dm2.std::string::~string();//����dm2
        Cl30_Base::~Cl30_Base();//���ٻ���ɷ�
        throw ;                           //�������쳣
    }
    //������δ���������������������ڷ�������,��ʵ�ϱ�����Ը����¸��ӵ������������쳣����Ҳ��׼ȷ��Ӧ��������հ׹��캯���ڲ�������Ϊ
}

/*�ص��ס:
 *  1.�������inline������С�͡���Ƶ�����õĺ������ϡ���ʹ�պ�ĵ��Թ��̺Ͷ��������������ף�Ҳ��ʹǱ�ڵĴ�������������С����
 *ʹ������ٶ�����������󻯡�
 *  2.��Ҫֻ��Ϊfunction template������ͷ�ļ����ͽ���������Ϊinline
 */




#endif //EFFECTIVECPP_CLAUSE30_UNDERSTAND_THE_INS_AND_OUTS_OF_INLINING_HPP
