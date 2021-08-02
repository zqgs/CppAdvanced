//
// Created by Sea on 2021/7/29.
//

#ifndef EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP
#define EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP


#include <string>
#include <stdexcept>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

/*�ڳ����ʵ�ֹ����У���ҪС��ʹ�ö���:
 * 1.���綨������������Ч���ϵ����ӡ�
 * 2.����ʹ��ת��(casts)���ܵ��´����������ά����������΢���ѽ�Ĵ���
 * 3.���ض���"�ڲ����"���ܻ��ƻ���װ���������������յľ��
 * 4.δ�����쳣�����ĳ������ܵ�����Դй©�����ݰܻ���
 * 5.�������ĵ�inlining���������������
 * 6.�������(coupling)����ܵ������˲�������߳�����ʱ��(build time)
 */


//����26:�����ܵ��Ӻ��������ʽ�ĳ���ʱ��
//ע:ֻҪ�����˱����������ʹ���һ�����캯����������������ô������Ŀ����������������ʽʱ����
//ô����ó��ܹ���ɱ�������������뿪������ʱ����ó��������ɱ���

//����1����ǰ��������
std::string Cl26_EncryptPassword(const std::string& Password)
{
    using namespace std;
    string _encrypted;
    //�׳��쳣
    if(Password.length()<5)
        throw logic_error("password is too short");
    _encrypted = Password+"123456";
    return _encrypted;
}
void Cl26_test01()
{
    Cl26_EncryptPassword("1352");
}
//����2��ֱ��ʹ��ǰ��������
std::string Cl26_EncryptPasswordExp1(const std::string& Password)
{
    using namespace std;
    //�׳��쳣
    if(Password.length()<5)
        throw logic_error("password is too short");
    string _encrypted;
    _encrypted = Password+"123456";
    return _encrypted;
}
void Cl26_test02()
{
    Cl26_EncryptPassword("1352");
}

//����3:��Ȼ��2�������Ǳ���_encrypted�õ�ֵ��ͨ����ֵ��������ȡ���ġ�����4�ᵽ:����ʱָ����ֵ��ͨ����ֵЧ�ʸ���
void encrypt(std::string& s)
{
    //�׳��쳣
    if(s.length()<5)
        throw std::logic_error("password is too short");
    s+="123456";
}
std::string Cl26_EncryptPasswordExp2(const std::string& Password)
{
    using namespace std;
    string _encrypted(Password);//���ӱ������壬ֱ���ܹ�������ֵʵ��Ϊֹ
    encrypt(_encrypted);
    return _encrypted;
}

//����������ѭ���е�Ӧ��
class Cl26_Widget{};
void Cl26_test03()
{
    //���һ:Cl26_Widget���ں�1������+1����������+n����ֵ����
    //�����:Cl26_Widget���ں�n������+n����������

    //�÷�1
    Cl26_Widget w1;
    for (int i = 0; i < 10; ++i) {
        //w1=i;
    }

    //�÷�2
    for (int i = 0; i < 10; ++i) {
        Cl26_Widget w2;
        //w2=i;
    }
   //w1���������w2���Ǹ���,��ʱ�Գ���Ŀ�����Ժ���ά������ɳ�ͻ��
   //1.����֪���÷�1�ĸ�ֵ�ɱ���"����+����"�ĳɱ��ͣ������ʹ���÷�1��������ʹ���÷�2
   //2.������ڴ���Ĵ���Ч�ʸ߶����в��֣�����Ӧ��ʹ���÷�2
}

/*�ص��ס:
 * 1.�����ܵ��Ӻ��������ʽ�ĳ��֡������������ӳ���������Ȳ����Ƴ���Ч��
 */




#endif //EFFECTIVECPP_CLAUSE26_DELAY_THE_APPEARANCE_OF_THE_VARIABLE_DEFINITION_FORMULA_AS_LONG_AS_POSSIBLE_HPP
