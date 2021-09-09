//
// Created by Sea on 2021/9/2.
//

#ifndef EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP
#define EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP

#include <functional>

//����35:����virtual�������������ѡ��

//����1:����һ����Ϸ�������｡��ָ�������
class Cl35_GameCharacter{
public:
    virtual int healthValue() const;//���� prue virtual,��������ȱʡʵ��
    virtual ~Cl35_GameCharacter()= 0;

    //����������Ǻ���ģ�����ĳ���Ƕ�˵ȴ���������������㡣�Ƿ�����������������virtual����Ʒ�ʽ�أ�
};

//����2:��Non-Virtual Interface�ַ�ʵ��Template Methodģʽ(��C++template���޹���)
class Cl35_GameCharacter_exp1{
public:
    int healthValue() const//��non-virtual��Ϊvirtual���⸲��(wrapper)
    {
        //��һЩ��ǰ����:������������������ת��¼����֤classԼ�����̡���֤�������Ⱦ�������
        int retVal = doHealthValue();//������Ҫ������
        //��һЩ�º���:�������������֤�������º��������ٴ���֤class��Լ������
        return retVal;
    }

private:
    virtual int doHealthValue() const{

    }
};
/*
 * ��virtual��Ƶ�private�У�����������¶������ɸ��������õĺ�����
 * 1.���¶���virtual������ʾĳЩ��"���"���
 * 2.����virtual������ʾ��"��ʱ"�����,�Ӷ���������"���ʵ�ֻ���"�Ŀ�����������base class������"������ʱ������"��Ȩ��
*/

//����3:��Function Pointersʵ��Strategyģʽ
//����:�뿴��ĿClause35_FunctionToStrategy����Cl35_GameCharacter_Exp2��


//����4:��std::Function ʵ�� Strategyģʽ
//һ��ϰ����template�Լ����Ƕ���ʽ�ӿڵ�ʹ�ã����ں���ָ��������������Եù��ֿ��������塣
//����:�뿴��ĿClause35_FunctionToStrategy����Cl35_GameCharacter_Exp3��
class Cl35_GameCharacter_Exp3;
typedef std::function<int(const Cl35_GameCharacter_Exp3&)> HealthCalcFunc;
// std::function���Ͳ����Ķ�����Գ����κ����ǩ��ʽ���ݵĿɵ����
// ˵�˻�����:����ֵ�ܱ���ʽת����int,�����ܱ���ʽת����const Cl35_GameCharacter_Exp3&�ĺ������ܱ�std::function���á�
// ���֮�£���û�к���ָ����ô�Ͽ�,��������3���ⲿû��Ӱ��,����ָ���Ĳ��Ժ��������˾��˵ĵ��ԡ�


/*
�ܽ�:
1.����ָ�����ƱȽ���,ֻ������һ���涨��ʽ�ĺ���(����callback�ص�����),�ҷ���ֵ�̶����ɸı䡣(��3)
2.ʹ��std::function���Լ���:��ͨ��������������ĳ����Ա������lambda���ʽ,�ҷ���ֵ֧����ʽת��(��4)

Cl35_EvilBadGuyExp1 ebg_exp1(calcHealth);//����1,ʹ����ͨ�������㽡��ֵ
std::cout <<"Cl35_EvilBadGuyExp1:healthValue:"<< ebg_exp1.healthValue()<<"\n";


Cl35_EyeCandyCharater *ecc1 = new Cl35_EyeCandyCharater(HealthCalculator());//;//����2,ʹ�ú���������㽡��ֵ
std::cout << "Cl35_EvilBadGuyExp1:healthValue" << ecc1->healthValue() << "\n";
delete ecc1;

Cl35_GameLevel currentLevel;
Cl35_EvilBadGuyExp1 ebg_exp2(std::bind(&Cl35_GameLevel::health, currentLevel, std::placeholders::_1));//����3��ʹ��ĳ����Ա�������㽡��ֵ
std::cout << "Cl35_EvilBadGuyExp1:healthValue:" << ebg_exp2.healthValue() << "\n";


auto lambda = [](const Cl35_GameCharacter_Exp3& hh)->int{
    std::cout << "lambda function\n";
    return 60;
};
Cl35_EvilBadGuyExp1 ebg_exp4(lambda);//����4,ʹ��lambda���㽡��ֵ
std::cout << "Cl35_EvilBadGuyExp4:healthValue:" << ebg_exp4.healthValue() << "\n";
*/

//�ŵ��Strategyģʽ:��ͳ��Strategy�����Ὣ�������㺯������һ������ļ̳���ϵ�е�virtual������Ա
//����5:��ͳ����ģʽʵ��:�뿴��ĿClause35_FunctionToStrategy����Cl35_GameCharacter_Exp4�뽡��ֵ���������HealthCalcFunction��
class Cl35_GameCharacter_Exp4;
class HealthCalcFunction{
public:
    virtual int calc(const Cl35_GameCharacter_Exp4&)const{
        return 0;
    }
};
HealthCalcFunction defaultHealthCalc;
class Cl35_GameCharacter_Exp4
{
public:
    explicit Cl35_GameCharacter_Exp4(HealthCalcFunction *phcf = &defaultHealthCalc):
            pHealthCalc(phcf)
    {

    }
    int healthValue()const{ return pHealthCalc->calc(*this); }
    ~Cl35_GameCharacter_Exp4(){}

private:
    HealthCalcFunction* pHealthCalc;
};
//��5�ĺô�:��׼��Strategy���ױ�𣬶��һ��ṩһ��"���н����㷨����ʹ��"�Ŀ�����----ֻ��ҪΪHealthCalcFunction�ṩһ�������༴��

/*ժҪ:��������ͼѰ������麯�����������ʱ����������һ���������:
 * 1.ʹ��non-virtual-interface(NVI)�ַ�,����Template Method���ģʽ��һ��������ʽ������public non-virtual��Ա���������Խϵͷ���
 *private��protected��virtual������
 * 2.��virtual�滻Ϊ"����ָ���Ա����",����Strategy���ģʽ��һ�ַֽ������ʽ��
 * 3.��std::function��Ա�����滻virtual��������Ϊ�����κοɵ�����(callable entity)����һ�����������ǩ��ʽ����Ҳ��Strategy���ģʽ��
 *һ�ַֽ���ʽ��
 * 4.���̳���ϵ�ڵ�virtual�����滻Ϊ��һ����ϵ�ڵ�virtual���������Ǵ�ͳStrategy���ģʽʵ���ַ�
 */

/*�ص��ס:
 *  1.virtual�����������������NVI�ַ���Strategy���ģʽ�Ķ�����ʽ��NVI�ַ�������һ��������ʽ��Template Method���ģʽ
 *  2.�����ܴӳ�Ա����ת�Ƶ�class�ⲿ������������һ��ȱ���ǣ��ǳ�Ա�����޷�����class��non-public��Ա��
 *  3.std::function������Ϊ����һ��ĺ���ָ�롣�����Ķ���ɽ���"�������Ŀ��ǩ��ʽ(����callback����ʽ<����ֵ������>)����"�����п�
 * ������(����callback����)������:��ͨ��������������ĳ����Ա������lambda���ʽ
 */



#endif //EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP
