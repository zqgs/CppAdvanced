//
// Created by Sea on 2021/9/16.
//

#ifndef EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
#define EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP

#include <string>
#include <iostream>
//����43:ѧϰ����ģ�黯�����ڵ�����

//����1:
class Cl43_CompanyA{
public:
    void sendClearText(const std::string& msg){std::cout<<"Cl43_CompanyA::sendClearText\n";}
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyA::sendEncrypted\n";}
};
class Cl43_CompanyB{
public:
    void sendClearText(const std::string& msg){std::cout<<"Cl43_CompanyB::sendEncrypted\n";}
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyB::sendEncrypted\n";}
};
class Cl43_MsgInfo{};

template<typename Company>
class Cl43_MsgSender{
public:
    void sendClear(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Company c;
        c.sendClearText(msg);
    }
    void sendSecret(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Company c;
        c.sendEncrypted(msg);
    }
};
void Cl43_Test01()
{
    Cl43_MsgSender<Cl43_CompanyA> cMsgSend;
    Cl43_MsgInfo cMsg;
    cMsgSend.sendClear(cMsg);
}

//����2:������ģ���࣬�ܷ��ʵ�����ĳ�Ա������
template<typename Company>
class Cl43_LoggingMsgSender: public Cl43_MsgSender<Company>{
public:
    void sendClearMsg(const Cl43_MsgInfo& info)
    {
        //sendClear(info);//����
        //  ���Զ��׼���������ģ���࣬���ܷ��ʵ�����ĳ�Ա��������Ҫ��Ϊ����������class template Cl43_LoggingMsgSenderʱ
        //����֪�����̳���ʲô����class
    }
};

//����3:����һ��������ϸ�����ӣ���Ȳ���Ϊʲô������ģ���࣬���ܷ��ʵ�����ĳ�Ա������
class Cl43_CompanyZ
{
public:
    //���ṩsendClearText�汾
    void sendEncrypted(const std::string& msg){std::cout<<"Cl43_CompanyZ::sendEncrypted\n";}
};
template <>//ȫ�ػ��汾����templateʵ��ΪCl43_CompanyZʱ,��Ҳû������template�������ṩ�仯��
class Cl43_MsgSender<Cl43_CompanyZ>{
public:
    //���ṩsendSecret
    void sendSecret(const Cl43_MsgInfo& info)
    {
        std::string msg;
        Cl43_CompanyZ c;
        c.sendEncrypted(msg);
    }
};
void Cl43_Test02()
{
    Cl43_MsgSender<Cl43_CompanyA> cMsgSend;
    Cl43_MsgInfo cMsg;
    cMsgSend.sendClear(cMsg);//һ��������ɹ�
    cMsgSend.sendSecret(cMsg);//һ��������ɹ�

    Cl43_MsgSender<Cl43_CompanyZ> cMsgSendz;
    //cMsgSendz.sendClear(cMsg);//ʧ�ܡ����Cl43_CompanyZ�Ѿ��ػ���
    cMsgSendz.sendSecret(cMsg);//�ɹ��������ػ��汾
}

//����4:�ٴο�����������û����Ա�����������
template<typename Company>
class Cl43_LoggingMsgSender_Exp1: public Cl43_MsgSender<Company>{
public:
    void sendClearMsg(const Cl43_MsgInfo& info)
    {
        //sendClear(info);//���ɱ���������������sendClear����Company==Cl43_CompanyZʱ���ػ��汾�������ṩ��������������ΪʲôC++�ܾ����õ�ԭ��
        //Ϊ�˲���C++�ĵ�����ΪʧЧ����������:
        //����һ:ʹ��thisָ��
        this->sendClear(info);//����������sendClear���̳С�
        //����2:ʹ��using����ʽ�����ﲢ���ǻ������Ʊ��������������ڣ����Ǳ�����������������������ҡ�
        //using Cl43_MsgSender<Company>::sendClear;
        //sendClear(info);
        //����3:����ָ��Ҫ���õú�����base��(�����������ã���������õ���virtual��������ȷ�ʸ����λ�ر�virtual�����İ���Ϊ)
        //Cl43_MsgSender<Company>::sendClear(info);
    }
};

//  �����ƿ��ӵ�Ƕ������������Ľⷨ�������鶼��ͬ:�Ա�������ŵbase class template���κ��ػ��汾����֧��һ��(����)�汾���ṩ�Ľӿڡ�
//�����ŵ����δ��ʵ�ֳ�������ô�������ڽ�����ʱ�����ջ����һ�������Ǹ������Ǳ��������ö����޷�ͨ�����롣

//  �������ԣ����ָ��"base class members"����Чreferences�����������ʱ����ܷ���������(�����������ඨ��ʽʱ)��Ҳ���ܷ���������(��
//��Щtemplate���ض���templateʵ�ξ��ֻ�ʱ)��

/*�ص��ס:
 *  1.����derived class template��ͨ��"this->"ָ��base class templates�ڵĳ�Ա���ƣ�����һ����ȷָ��"base class �ʸ����η�"��ɡ�
 */


//��չ:ȫ�ػ���ƫ�ػ�
//ȫ�ػ�:ȫ�ػ�һ�����ڴ���������Ҫ�������ߺ�������ʱ�ķ���ģ���޷��������������
//�������ȫ�ػ�
template<typename T>
class Cl43_A{
public:
    bool cmp(const T& t1,const T& t2){
        return t1 == t2;
    }
};
//ȫ�ػ��汾
template <>
class Cl43_A<char*>{
public:
    bool cmp(const char* t1,const char* t2)
    {
        while (*t1 != '\0' && *t2 != '\0')
        {
            if(*t1 != *t2)
                return false;
            ++t1;
            ++t2;
        }
        return true;
    }
};
void Cl43_Test03()
{
    Cl43_A<int> cmp;
    std::cout<<cmp.cmp(1,2)<<std::endl;
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    Cl43_A<char*> cmp1;
    std::cout<<"c1 ? c2:"<<cmp1.cmp(c1,c2)<<"\n";
    std::cout<<"c1 ? c3:"<<cmp1.cmp(c1,c3)<<"\n";
    std::cout<<"c2 ? c3:"<<cmp1.cmp(c2,c3)<<"\n";
}

//���ں�����ȫ�ػ�
template <typename  T1,typename T2>
bool Cl43_cmp(T1& t1,T2& t2)
{
    return t1 == t2;
}
template<>
bool Cl43_cmp(char* &p1,char* &p2)
{
    auto ptr1 = p1,ptr2 = p2;
    while (*ptr1 != '\0' && *ptr2 != '\0')
    {
        if(*ptr1 != *ptr2)
            return false;
        ++ptr1;
        ++ptr2;
    }
    return true;
}

void Cl43_Test04()
{
    int a = 1,b=2;
    std::cout<<Cl43_cmp(a,b)<<std::endl;
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    std::cout<<"c1 ? c2:"<<Cl43_cmp(c1,c2)<<"\n";
    std::cout<<"c1 ? c3:"<<Cl43_cmp(c1,c3)<<"\n";
    std::cout<<"c2 ? c3:"<<Cl43_cmp(c2,c3)<<"\n";
}

//�������ƫ�ػ�:
template <typename T,typename T1>
class Cl43_A1{
public:
    Cl43_A1() = default;
    Cl43_A1(const T1& n){
        std::cout<<"n:"<<n<<"\n";
    }
    bool cmp(const T& t1,const T& t2){
        return t1 == t2;
    }
};

//ƫ�ػ��汾
template<typename  T>
class Cl43_A1<char*,T>{
public:
    Cl43_A1() = default;
    Cl43_A1(T& n){
        std::cout<<"n:"<<n<<"\n";
    }
    bool cmp(const char* t1,const char* t2){
        while (*t1 != '\0' && *t2 != '\0')
        {
            if(*t1 != *t2)
                return false;
            ++t1;
            ++t2;
        }
        return true;
    }
};

void Cl43_Test05()
{
    char* c1 = "hello";
    char* c2 = "world";
    char* c3 = "world";
    Cl43_A1<int,char*>cc(c1);
    std::cout<<"1 == 2?:"<<cc.cmp(1,2)<<"\n";

    Cl43_A1<char*,char*> cc2(c2);
    std::cout<<"c1 == c3?:"<<cc2.cmp(c1,c3)<<"\n";
    std::cout<<"c2 == c3?:"<<cc2.cmp(c2,c3)<<"\n";
}
//����û��ƫ�ػ���ֻ�к������أ�����














#endif //EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
