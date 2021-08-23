//
// Created by Sea on 2021/8/17.
//

#ifndef EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP
#define EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP

#include <memory>
#include <iostream>
#include <mutex>
#include <fstream>
//����29:Ϊ"�쳣��ȫ"��Ŭ����ֵ�õ�

//ֱ������ʾ��1:
//�����и�class�������ּд�����ͼ����GUI�˵��������ϣ�����ڶ��̻߳���������һ����������Ϊ��������
class Image{
public:
    Image():iMag(0){}
    Image(std::istream&):iMag(88){}
    int iMag;
};
class PrettyMenu{
public:
    void changeBackground(std::istream& imgSrc);

private:
    std::mutex Mutex;//������
    Image * bgImage; //Ŀǰ�ı���ͼ��
    int imageChanges;//�������ı�Ĵ���
};
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Mutex.lock();
    delete bgImage;
    ++imageChanges;
    bgImage = new  Image(imgSrc);
    Mutex.unlock();
}
//����ĺ�����"�쳣��ȫ��"�۵������ͺ����
/*  ���쳣���׳�ʱ�������쳣��ȫ�Եĺ�����:
 *1.��й©�κ���Դ��PrettyMenu::changeBackgroundû��������㣬һ��new�����쳣����ô����������Զ��ס��������13�е�share_ptrʵ��һ�������ɽ��
 *2.���������ݰܻ������new�׳��쳣��bgImageָ��һ����ɾ���Ķ���imageChanges���ɱ��ۼӣ���ʵͼ��δˢ��
 */

/*   ������ݰܻ����쳣��ȫ����(Exception-safe function)�ṩ����������֤֮һ:
 * 1.������ŵ:����쳣���׳��������ڵ��κ�������Ȼ��������Ч״̬�¡���ʾ��1�е�changeBackgroundһ���쳣�׳���
 *������PrettyMenu����ӵ��ԭ����ͼ�񣬻�����ӵ��ȱʡ����ͼ��
 * 2.ǿ�ұ�֤:����쳣���׳�������״̬���ɸı䡣ǿ�ұ�֤����ִ�н�����ֻ������״̬��Ҫô��Ԥ��һ��ִ�гɹ���Ҫô
 *���������쳣��ص�������ǰ��״̬��
 * 3.��������no throw����֤,��ŵ�����׳��쳣����Ϊ���������ܹ��������ԭ�ȳ�ŵ�Ĺ��ܡ�����������(ints,ptrs��)���ṩ��no throw��֤
 */

//������13һ��ʹ������ָ�������Դ
//����2:����RAIIʵ��һ���Զ�����Ļ�����
void _clause29_Lock(std::mutex *pm){
    pm->lock();
}
void _clause29_UnLock(std::mutex *pm){
    pm->unlock();
}
class Clause29_Lock
{
public:
    explicit Clause29_Lock(std::mutex* pm):
            mutexPtr(pm,_clause29_UnLock)//ָ��ɾ����_clause14_UnLock
    {
        _clause29_Lock(mutexPtr.get());
    }
    //������Ҫ��������
private:
    std::shared_ptr<std::mutex> mutexPtr;
};
class PrettyMenuExp1{
public:
    void changeBackground(std::istream& imgSrc);
private:
    std::shared_ptr<Image> bgImage;//ʹ������ָ�������Դ
    int imageChanges;//�������ı�Ĵ���
    std::mutex pm;
};
//Ψһ����:����׳��쳣��std::istream����ļǺ�(read marker)�ѱ����ߣ��������ƶ��Գ������ಿ����һ�ֿɼ���״̬�ı�(���������ֻ��:�����쳣��ȫ��֤)
void PrettyMenuExp1::changeBackground(std::istream &imgSrc) {
    Clause29_Lock m1(&pm);
    bgImage.reset(new Image(imgSrc));
    ++imageChanges;
}

//��������������Ĳ����ø��������أ�(Ҳ����:ǿ���쳣��ȫ��֤)
//�и�����(copy and swap)�ᵼ��ǿ�ұ�֤��ԭ��:Ϊ��Ҫ�޸ĵĶ�������һ�ݸ�����Ȼ���ٸ���������һ�б�Ҫ���޸ġ�
//���޸Ķ����׳��쳣��ԭ����״̬�Ա��ֲ��䡣���޸ĳɹ����ٽ�������ԭ�����ڲ��׳��쳣�Ĳ������û���swap���������ַ���֮Ϊ:Pimpl idiom

//����3:��pimpl idiom�ַ���ʵ��һ��ǿ�ұ�֤
struct PMImpl{
    std::shared_ptr<Image> bgImage;
    int imageChanges;
    PMImpl(){}
    PMImpl( std::shared_ptr<PMImpl> temPtr):
    bgImage(temPtr->bgImage),
    imageChanges(temPtr->imageChanges)
    {

    }
};
class PrettyMenuExp2
{
public:
    PrettyMenuExp2(){
        pImpl = std::make_shared<PMImpl>();
        pImpl->imageChanges = 1;
        pImpl->bgImage = std::make_shared<Image>();
        pImpl->bgImage->iMag = 99;
    }
    void changeBackground(std::istream& imgSrc);
private:
    std::shared_ptr<PMImpl> pImpl;//ʹ������ָ�������Դ
    std::mutex pm;
};

void PrettyMenuExp2::changeBackground(std::istream &imgSrc) {
    using std::swap;
    Clause29_Lock ml(&pm);
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
    std::cout<<"pNew->imageChanges:"<<pNew->imageChanges<<"\n";
    std::cout<<"pNew->bgImage->iMag:"<<pNew->bgImage->iMag<<"\n";

    pNew->bgImage.reset(new Image(imgSrc));
    ++pNew->imageChanges;
    swap(pImpl,pNew);

    std::cout<<"pImpl->imageChanges:"<<pImpl->imageChanges<<"\n";
    std::cout<<"pImpl->bgImage->iMag:"<<pImpl->bgImage->iMag<<"\n";
}

void Clause29_test01()
{
    std::filebuf fb;
    if (!fb.open ("test.txt",std::ios::in))
    {
        std::istream is(&fb);
        PrettyMenuExp2 pme;
        pme.changeBackground(is);
    }
}

//һ�����ϵͳҪ���;߱��쳣��ȫ�ԣ�Ҫ����ȫȻ�񶨣�û����ν��"�ֲ��쳣��ȫϵͳ"�����ϵͳ����һ��(����һ��)��������
//���쳣��ȫ�ԣ���ô����ϵͳҲ�����߱��쳣��ȫ�ԡ���Ϊ�����Ǹ����߱��쳣��ȫ�Եĺ������ܵ�����Դй©�����ݽṹ�ܻ���

/*�ص��ס:
 * 1.�쳣��ȫ����(Exception-safe function)��ʹ�����쳣Ҳ����й©��Դ�������κ����ݽṹ�ܻ��������ĺ�������δ���ֿ��ܵı�֤:
 *�����͡�ǿ���͡������쳣��
 * 2."ǿ�ұ�֤"�����ܹ���copy-and-swapʵ�ֳ�������"ǿ�ұ�֤"���Ƕ����к�������ʵ�ֻ�߱���ʵ����
 * 3.�����ṩ��"�쳣��ȫ��֤"ͨ�����ֻ��������õĸ���������"�쳣��ȫ��֤"�е������ߡ�����ľͰԭ��:�ɶ��ľ�幹�ɵ�ˮͰ��
 *���ֵ������ʢˮ���Ķ��٣�������ˮͰʢˮ�����ٵĹؼ����ز�������İ�飬��������̵İ��
 */




#endif //EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP
