//
// Created by Sea on 2021/7/21.
//

#ifndef EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP
#define EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP

//����22:����Ա��������Ϊprivate

//1.ʵ�־�׼����:�Ժ��������ó�Ա����
class AccessLevels{
public:
    int getReadOnly() const{return readOnly;}
    void setReadWirte(int value) {ReadWrite = value; }
    int getReadWirte()const {return ReadWrite;}
    void setWirteOnly(int value) {writeOnly = value;}
private:
    int noAccess;//�Դ�int���κη��ʶ���
    int readOnly;//�Դ�int��ֻ������
    int ReadWrite;//�Դ�int����д����
    int writeOnly;//�Դ�int��ֻд����
};


//2.C++��װ����:ʹ�ú������ʳ�Ա����(�ڲ�ʵ�����ⲿ���÷���)
class SpeedDaeCollection{
public:
    void addValue(int Speed){}
    double averageSoFar() const{}
    //averageSoFarʵ�ַ�ʽ:ʵʱ���ü���/��ʱ���ü��㣬�����ȡƽ��ֵ�Ժ����ķ�ʽ���֣��Ϳ����ں����ڲ����ɵ�ʵ�֡�
    //����Ա���������ں����ӿڱ��󣬿���Ϊ"���п��ܵ�ʵ��"�ṩ���ԡ�
};

//�ӷ�װ�ĽǶȹۿ�:��ʵֻ�����ַ���Ȩ��:private(�ṩ��װ)������(���ṩ��װ)

/*�ص��ס:
 * 1.�мǽ���Ա��������Ϊprivate����ɸ�������ŷ������ݵ�һ���ԡ���ϸ΢���ַ��ʿ��ơ���ŵԼ��������ñ�֤��
 *���ṩclass���߳�ֵ�ʵ�ֵ��ԡ�
 * 2.protected������public���߷�װ��
 */

#endif //EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP
