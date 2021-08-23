//
// Created by Sea on 2021/8/17.
//

#ifndef EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP
#define EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP

#include <memory>
#include <iostream>
#include <mutex>
#include <fstream>
//条款29:为"异常安全"而努力是值得的

//直接来看示例1:
//假设有个class用来表现夹带背景图案的GUI菜单，这个类希望用于多线程环境，它有一个互斥器作为并发控制
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
    std::mutex Mutex;//互斥器
    Image * bgImage; //目前的背景图像
    int imageChanges;//背景被改变的次数
};
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Mutex.lock();
    delete bgImage;
    ++imageChanges;
    bgImage = new  Image(imgSrc);
    Mutex.unlock();
}
//上面的函数从"异常安全性"观点来看就很糟糕
/*  当异常被抛出时，带有异常安全性的函数会:
 *1.不泄漏任何资源。PrettyMenu::changeBackground没有做到这点，一旦new发生异常，那么互斥器将永远锁住。用条款13中的share_ptr实现一个锁即可解决
 *2.不允许数据败坏。如果new抛出异常，bgImage指向一个被删除的对象，imageChanges依旧被累加，其实图像并未刷新
 */

/*   解决数据败坏。异常安全函数(Exception-safe function)提供以下三个保证之一:
 * 1.基本承诺:如果异常被抛出，程序内的任何事物仍然保持在有效状态下。（示例1中的changeBackground一旦异常抛出，
 *可以让PrettyMenu继续拥有原背景图像，或让它拥有缺省背景图像）
 * 2.强烈保证:如果异常被抛出，程序状态不可改变。强烈保证程序执行结束后只有两种状态，要么如预期一样执行成功，要么
 *函数调用异常后回到被调用前的状态。
 * 3.不抛掷（no throw）保证,承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。像内置类型(ints,ptrs等)都提供了no throw保证
 */

//如条款13一样使用智能指针管理资源
//例子2:利用RAII实现一个自动管理的互斥器
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
            mutexPtr(pm,_clause29_UnLock)//指定删除器_clause14_UnLock
    {
        _clause29_Lock(mutexPtr.get());
    }
    //不再需要析构函数
private:
    std::shared_ptr<std::mutex> mutexPtr;
};
class PrettyMenuExp1{
public:
    void changeBackground(std::istream& imgSrc);
private:
    std::shared_ptr<Image> bgImage;//使用智能指针管理资源
    int imageChanges;//背景被改变的次数
    std::mutex pm;
};
//唯一不足:如果抛出异常，std::istream读入的记号(read marker)已被移走，这样的移动对程序其余部分是一种可见的状态改变(所以这个还只是:基本异常安全保证)
void PrettyMenuExp1::changeBackground(std::istream &imgSrc) {
    Clause29_Lock m1(&pm);
    bgImage.reset(new Image(imgSrc));
    ++imageChanges;
}

//怎样才能让上面的不足变得更加完美呢？(也就是:强烈异常安全保证)
//有个策略(copy and swap)会导致强烈保证，原则:为需要修改的对象做出一份副本，然后再副本身上做一切必要的修改。
//若修改动作抛出异常，原对象状态仍保持不变。待修改成功后，再将副本和原对象在不抛出异常的操作中置换（swap），这种手法称之为:Pimpl idiom

//例子3:用pimpl idiom手法来实现一个强烈保证
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
    std::shared_ptr<PMImpl> pImpl;//使用智能指针管理资源
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

//一个软件系统要不就具备异常安全性，要不就全然否定，没有所谓的"局部异常安全系统"。如果系统内有一个(仅此一个)函数不具
//备异常安全性，那么整个系统也将不具备异常安全性。因为调用那个不具备异常安全性的函数可能导致资源泄漏或数据结构败坏。

/*重点记住:
 * 1.异常安全函数(Exception-safe function)即使发生异常也不会泄漏资源或允许任何数据结构败坏。这样的函数区分未三种可能的保证:
 *基本型、强烈型、不抛异常型
 * 2."强烈保证"往往能够以copy-and-swap实现出来，但"强烈保证"并非对所有函数都可实现或具备现实意义
 * 3.函数提供的"异常安全保证"通常最高只等于其调用的各个函数的"异常安全保证"中的最弱者。例如木桶原理:由多块木板构成的水桶，
 *其价值在于其盛水量的多少，但决定水桶盛水量多少的关键因素不是其最长的板块，而是其最短的板块
 */




#endif //EFFECTIVECPP_CLAUSE29_STRICE_FOR_EXCEPTION_SAFE_CODE_HPP
