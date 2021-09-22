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
        using Cl43_MsgSender<Company>::sendClear;
        sendClear(info);
        //����3:����ָ��Ҫ���õú�����base��(�����������ã���������õ���virtual��������ȷ�ʸ����λ�ر�virtual�����İ���Ϊ)
        Cl43_MsgSender<Company>::sendClear(info);
    }
};

//  �����ƿ��ӵ�Ƕ������������Ľⷨ�������鶼��ͬ:�Ա�������ŵbase class template���κ��ػ��汾����֧��һ��(����)�汾���ṩ�Ľӿڡ�
//�����ŵ����δ��ʵ�ֳ�������ô�������ڽ�����ʱ�����ջ����һ�������Ǹ������Ǳ��������ö����޷�ͨ�����롣

//  �������ԣ����ָ��"base class members"����Чreferences�����������ʱ����ܷ���������(�����������ඨ��ʽʱ)��Ҳ���ܷ���������(��
//��Щtemplate���ض���templateʵ�ξ��ֻ�ʱ)��

/*�ص��ס:
 *  1.����derived class template��ͨ��"this->"ָ��base class templates�ڵĳ�Ա���ƣ�����һ����ȷָ��"base class �ʸ����η�"��ɡ�
 */



#endif //EFFECTIVECPP_CLAUSE43_LERNING_ACCESS_NAME_IN_TEMPLATIZED_BASE_CLASS_HPP
