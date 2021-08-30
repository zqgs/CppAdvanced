//
// Created by Sea on 2021/8/25.
//

#ifndef EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP
#define EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP

#include <string>
#include <memory>
//����31:���ļ���ı��������ϵ�������

//����1:��һ��class����΢�޸ģ������class��ص��ļ��������±���
//#include "Date.h"
//#include "Address"
class Cl31_Person
{
public:
    Cl31_Person(const std::string & name/*const Date& birthday,const Address& addr*/);
    std::string name() const;
    std::string birthday() const;
    std::string address() const;

private:
    std::string theName;
    //Date theBirthday;
    //Address theAddress;
};
//�����������Person�����ļ������������ļ�ֱ���γ���һ�ֱ��������ϵ�������Щͷ�ļ������κ�һ�����ı�,
//��ôÿһ������Person class���ļ��͵����±��롣�����������������ϵ��������Ŀ����������ݵ����ѡ�


//��ô���ӿں�ʵ�ֽ�����أ� ��:ǰ����������ǰ��������ÿһ�������������������ڱ����ڼ�֪������Ĵ�С��
//����2:�����������ӣ�������ǰ������ʵ������1
class Cl31_Date;
class Cl31_Address;
class Cl31_PersonExp1
{
public:
    Cl31_PersonExp1(const std::string & name,const Cl31_Date& birthday,const Cl31_Address& addr);
    std::string name() const;
    std::string birthday() const;
    std::string address() const;

private:
    std::string theName;
    //Cl31_Date theBirthday;
    //Cl31_Address theAddress;

};

void Cl31_Test01()
{
    //ͨ��������֪��intӦ�÷�������ڴ�
    int x;
    //����������Ҫ֪��Cl31_Person��Ҫ��������ڴ�ʱ,Ψһ�취����ѯ��Cl31_Person�Ķ���ʽ��
    //��ѯ�ʵ�ǰ������Cl31_Date��Cl31_Addressʱ��Ȼ������ʽ���ԺϷ��Ĳ��г�ʵ�֣����������֪��Ҫ������ٿռ䣿
    Cl31_Person p("LiLi");

    //��һ�ְ취��������ʵ��������һ��ָ�뱳�󣬱���:
    int *y;
    Cl31_Person *p1;
}

//����3:����һ������2��ǰ����������Person�ָ�Ϊ����class��һ���ṩ�ӿڣ�һ������ʵ�ָýӿ�
//Cl31_PersonExp2.h
class Cl31_PersonImpl;
class Cl31_PersonExp2{
public:
    Cl31_PersonExp2(const std::string &Name);
    std::string name() const;
    ~Cl31_PersonExp2(){}
private:
    std::shared_ptr<Cl31_PersonImpl> pImpl;
};
//Cl31_PersonExp2.cpp����Cl31_PersonImpl.h���ڽӿڵ�ʵ��
//���������֮�£�Cl31_PersonExp2�Ľӿ���ȫ��ʵ�ַ��롣������Cl31_PersonImpl�޸��κζ�����Cl31_PersonExp2��������Ҫ���±��룬��
//ʱͨ���ӿ�ʱ�޷�����Cl31_PersonExp2������ʵ�ֵ�,Ҳ�Ͷž���"ȡ����ʵ��"�Ĵ��롣�����"�ӿ���ʵ�ַ���"


//ʵ����ӿڷ���Ĺؼ�:��"������������"�滻"�����������"������������ͷ�ļ��������㡣

/*����������Handle class��Դ����������Ʋ���:
 *  1.���ʹ�ö�������(object references)�����ָ��(object pointers)������ɣ��Ͳ�Ҫʹ����ͨ���󡣿���ֻ��һ����������ʽ�Ͷ����ָ������͵�����
 *��ָ�롣���������ĳ���͵�object(����)������Ҫ�õ������͵Ķ���ʽ��
 *  2.����ܹ���������class����ʽ�滻class����ʽ��ע�⣬������һ�������õ�ĳ����ʱ����ʵ������Ҫ����Ķ��壬��ʹ������ֵ���ݵķ�ʽ���ݸ����͵Ĳ���Ҳ�����
 *  3.Ϊ����ʽ�Ͷ���ʽ�ṩ��ͬ��ͷ�ļ���
 */

//��һ������Handle class�취��:��Person��Ϊһ�������abstract base calss(�������),��Ϊinterface class������class��Ŀ������ϸ����������Ľӿڣ����ͨ������
//��Ա������Ҳû�й��캯����ֻ��һ�����������Լ�һ��pure virtual����(�麯�� or ���麯��),�������������ӿ�

//����4:���Person��д��interface class
class Cl31_PersonExp3{
public:
    virtual ~Cl31_PersonExp3();
    virtual std::string name() const =0;
    virtual std::string birthDate() const =0;
    virtual std::string address() const =0;
};
//interface class�ĵ�����ͨ������һ�����⺯��Ϊ�¶���������ʵ�������Ǹ�����������Ĺ��캯���������ĺ���ͨ����Ϊ"��������"����virtual���캯����
//��Щ����һ�㷵��ָ��ָ��̬������ڴ棬�������ĺ�����������interface class�ڱ�����Ϊstatic
//����5:
class Cl31_RealPerson;
class Cl31_PersonExp4{
public:
//    static std::shared_ptr<Cl31_PersonExp4> create(const std::string& name){
//        return std::shared_ptr<Cl31_PersonExp4>(new Cl31_RealPerson(name));
//    }
};
class Cl31_RealPerson: public Cl31_PersonExp4{
public:
    Cl31_RealPerson(const std::string& name):theName(name){}
    virtual ~Cl31_RealPerson(){}
    std::string name() const;
private:
    std::string theName;
};


/*  handle class�Ĳ���:��Ա��������ͨ��Impl pointerָ��ȡ�ö������ݡ��ǻ�Ϊÿһ�η�������һ�����ԡ�ÿһ������С�ŵ��ڴ�������������Impl pointerָ���
 *��С�����Impl pointerָ������ʼ����ָ��һ����̬�������Impl object�����Ի��ó��ܶ�̬�ڴ��������ö��⿪�����Լ�����bad_alloc�쳣(�ڴ治��)�Ŀ��ܡ�
 *
 *  interface class�Ĳ���:����ÿһ����������virtual�����Ա���Ϊÿ�κ������ø���һ�������Ծ�ĳɱ�(������07)������interface class������Ķ�������ں�һ���麯����
 *���ָ����ܻ����Ӵ��ڶ�������Ҫ���ڴ�����---ʵ��ȡ�����������interface class֮���Ƿ����������麯����Դ��
 */

//������handle class��interface class��һ������inline�������޷���̫�����Ϊ��������30�����˺�������Ϊ�˱�inline��������ͷ�ļ��ڣ�����handle class��interface class
//�����ر�����������ʵ��ϸ�ڵġ�

//��ʵ�ʿ���������ʹ��handle class��interface class����ʵ���������仯����ʹ���ߵĳ����С��������(handle class��interface class)�����ٶȺ�/���С��������ش�
//������class����������֮�²���Ϊ�ؼ�����ô���Ծ�����(����һ����ͨ��)�滻handle class��interface class��

/*�ص��ס:
 *  1.֧��"����������С��"��һ�㹹����:����������ʽ����Ҫ�����ڶ���ʽ�����ڴ˹���������ֶ�handle class��interface class��
 *  2.�����ͷ�ļ�Ӧ����"��ȫ��������ʽ"����ʽ���ڡ��������������Ƿ��漰template������
 */


#endif //EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP
