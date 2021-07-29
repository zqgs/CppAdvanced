//
// Created by Sea on 2021/7/28.
//

#ifndef EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
#define EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
#include <vector>
#include <iostream>
//����25:����д��һ�����׳��쳣��swap����

//������һ�±�׼���swapʵ��
/*namespace Cl25___std{//��װ�Ǳ�׼��
    template <typename T>
    //ֻҪ����֧��copying(ͨ���������캯���Ϳ�����ֵ���������)
    void swap(T& a,T& b){
        T temp(a); //a���Ƶ�temp
        a = b;//b���Ƶ�a
        b = temp;//temp���Ƶ�b
    }
}*/
//��ĳЩ���Ͷ���:��ָ��ָ��һ�������ں����������ݡ�������Ƴ����ı�����ʽΪpimpl�ַ�
class Cl25_WidgetImpl{
private:
    int a,b,c;
    std::vector<double> v;
};
class Cl25_Widget{
public:
    Cl25_Widget(const Cl25_Widget& rhs){}
    Cl25_Widget& operator=(const Cl25_Widget& rhs){

        //���Ƴ�Ա
        *pImpl = *(rhs.pImpl);
        return *this;
    }

private:
    Cl25_WidgetImpl* pImpl;
};
//���Ҫ��������Cl25_Widget��ֵ��Ψһ��Ҫ�����ǽ���pImplָ�룬����ȱʡswapȴ��֪������ʱʹ��ȱʡswap��ô���ڲ�������ʲô��
//swap�Ḵ������Cl25_Widget�����Ḵ������Cl25_WidgetImpl���󣬴�ʱЧ�ʻ�Ƚϵ��¡�

//ǿ���ػ�std::swap�ᷢ��ʲô��
//����ʾ��1:ͨ�����ǲ�����ı�std�����ռ��е��κζ�����������Ϊ��׼template�����ػ��汾��ʹ��ר��Ϊĳ�������
namespace std{
    template<>//��ʾstd::swap��һ��ȫ�ػ��汾��
    void swap<Cl25_Widget>(Cl25_Widget& a,Cl25_Widget& b){
        //std::swap(a.pImpl,b.pImpl); //������˽�г�Ա��������ֱ�ӱ���
    }
}
//����ʾ��2��ʾ��1�����ػ��汾ʧ�ܺ�,�����class�ڲ�����swap�����ֻ�������
class Cl25_WidgetExp1{
public:
    Cl25_WidgetExp1(const Cl25_WidgetExp1& rhs){}
    Cl25_WidgetExp1& operator=(const Cl25_WidgetExp1& rhs){
        //���Ƴ�Ա
        *pImpl = *(rhs.pImpl);
        return *this;
    }
    void swap(Cl25_WidgetExp1& other){
        std::swap(pImpl,other.pImpl);
    }
private:
    Cl25_WidgetImpl* pImpl;
};
//�ٴ�ΪCl25_WidgetExp1�����ػ��汾
namespace std{
    template<>
    void swap<Cl25_WidgetExp1>(Cl25_WidgetExp1& a,Cl25_WidgetExp1& b){
        a.swap(b); //���ڿ���ͨ�����룬����STL��һ���ԣ���Ϊ����STL���ṩ��public swap��Ա������std::swap�ػ��汾
    }
}

//����ʾ��3:��ʾ��2�Ļ�����������һ�㣬���Cl25_WidgetExp1��Cl25_WidgetImpl����class template����calsses,ʵ��std�ػ�swap�����������أ�
template <typename T>
class Cl25_WidgetImplExp1{
private:
    T a,b,c;
    std::vector<double> v;
};

template <typename T>
class Cl25_WidgetExp2{
public:
    Cl25_WidgetExp2(const Cl25_WidgetExp2& rhs){}
    Cl25_WidgetExp2& operator=(const Cl25_WidgetExp2& rhs){
        //���Ƴ�Ա
        *pImpl = *(rhs.pImpl);
        return *this;
    }
    void swap(Cl25_WidgetExp2& other){
        std::swap(pImpl,other.pImpl);
    }
private:
    Cl25_WidgetImplExp1<T>* pImpl;
};

//ΪCl25_WidgetExp2����std�ػ��汾����ʼ��������Cl25_WidgetExp2������
/*namespace std{
    template<typename T>
    //���ֱ��벻ͨ����C++ֻ�����class templateƫ�ػ����������function templateƫ�ػ�
    void swap<Cl25_WidgetExp2<T>>(Cl25_WidgetExp2<T>& a,Cl25_WidgetExp2<T>& b){
        a.swap(b);
    }
}*/

//��Ȼƫ�ػ���ͨ������ô��ȡ����function template�ķ�ʽ�أ���ʵ���std��function template���ض��ǲ��е�
/*namespace std{
    template <typename T>
    //���ƿ��У���ʵ��Ȼ��C++ίԱ���ֹ�������ͱ�׼�����Ѿ������õĶ�����
    void swap(Cl25_WidgetExp2<T>& a,Cl25_WidgetExp2<T>& b){
        a.swap(b);
    }
}*/

//��ȷʾ��4:һ����ԣ�����function template�ǿ��еģ����std��׼����⡣
namespace WidgetStuff{
    template<typename T>
    class Cl25_WidgetExp3{
    public:
        Cl25_WidgetExp3(const Cl25_WidgetExp3& rhs){}
        Cl25_WidgetExp3& operator=(const Cl25_WidgetExp3& rhs){
            //���Ƴ�Ա
            *pImpl = *(rhs.pImpl);
            return *this;
        }
        void swap(Cl25_WidgetExp3& other){
            std::swap(pImpl,other.pImpl);
        }
    private:
        Cl25_WidgetImplExp1<T>* pImpl;
    };

    //�ɹ�,�õ����ߵ���swap�ܹ�ȡ�ýϸ�Ч�İ汾
    template<typename T>
    void swap(Cl25_WidgetExp3<T>& a,Cl25_WidgetExp3<T>& b){
        a.swap(b);
    }

    //ʾ��4�е�������classes��class template���ɡ�
}


//ʵ��5:�ӵ����ߵĽǶȳ�����������Ҫ�������swap���ڸ�Ч�ػ��汾�������֮�������������std::swap
template <typename T>
void doSomeThing(T& obj1,T& obj2)
{
    //1.��ȷʹ��
    using std::swap;
    swap(obj1,obj2);

    //2.����ʹ��(������˵����ֻ�ǵ�T���ڸ�Ч�汾ʱ����������ȷ����֮)
    std::swap(obj1,obj2);

    //˼��Ϊʲô2�Ǵ���ģ�
    //��:��Ϊ2ǿ���ñ�����ѡ����std�ķ����������ǲ��еġ�����1��ʹ����using��std::swap��¶����������
    //������"ʵ��ȡ���Ĳ��ҹ���"�����Ȳ���T�ĸ�Чswap�汾������Ҳ����ͻ����using��¶��std::swap��׼�汾��
    //������ñ������������ǵ�������ö�Ӧ��swap��������ô����using�����ǲ����ѡ��
}

//���default swap��member swap��non-member swap��std::swap�ػ��汾���Լ���swap�ĵ����ܽ�:
/* ���ȣ����swapȱʡ���class��class template�ṩ���Խ��յ�Ч�ʣ���ô��������Ӷ����swap�汾��
 *�����߽��Զ����ȱʡswap�汾��
 * ��Σ����swapȱʡ�汾��Ч�ʲ���(������class��class template��ʹ����ĳ��pimpl�ַ�)����ô����Ӧ�ó�����һ������:
 *1.�ṩһ��public swap������������Ч�������������ֵ���û������������Ӧ�׳��쳣��
 *2.��class��template���ڵ������ռ�(��std)�ṩһ��non-member swap,����������1��swap��Ա����
 *3.������ڱ�дclass(����class template)������Ϊclass����һ��std::swap�ػ��汾������������1��swap��Ա����
 * ����������swap,ȷ������һ��using����ʽ���Ա���std::swap�ں������ع⣬�����namespace���η�('std::')��ֱ�ӵ���swap����
 * ��:swap�����׳��쳣��һԼ��ֻʩ����member��������ʵʩ��non-member��ԭ��:swapȱʡ�汾���Կ������캯���Ϳ������Ʋ�����Ϊ������
 *һ����������߶������׳��쳣��
 */


/*�ص��ס:
 * 1.��std::swap������Ч�ʲ���ʱ���ṩһ��swap��Ա�����������׳��쳣��
 * 2.����ṩһ��member swap��Ҳ���ṩһ��non-member swap��������ǰ�ߣ�����classes(��class template)�����ػ�std::swap
 * 3.����swapʱӦ���std::swapʹ��using����ʽ��Ȼ�����swap���Ҳ����κ������ռ������
 * 4.Ϊ"�û���������"����std templateȫ�ػ��Ǻõģ���ǧ��Ҫ������std�ڼ����std����ȫ�µĶ���
 */

#endif //EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
