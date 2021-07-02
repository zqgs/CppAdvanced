//
// Created by Sea on 2021/6/29.
//

#ifndef EFFECTIVECPP_CLAUSE04_BEFORE_USED_OBJECT_MAKSSURE_IS_INITIALIZED_HPP
#define EFFECTIVECPP_CLAUSE04_BEFORE_USED_OBJECT_MAKSSURE_IS_INITIALIZED_HPP


#include <iostream>
#include <list>
//条款04：确定对象被使用前已被初始化
/* 如果使用了未初始化的变量会可能出现什么样的后果：读取未初始化的值会导致不明确的行为。在某些平台
 * 上，仅仅只是读取未初始化的值，就有可能使得程序终止运行。更可能的情况是读入一些“半随机”bits,
 * 污染了正在进行读取动作的对象，最终导致不可测知的程序行为以及令人发狂的调试过程。
 */

//初始化规则:对象的初始化动作何时一定发生，何时不一定发生
//初始化规则似乎是个无法决定的状态，最佳处理:永远在使用对象之前将其初始化。对于无任何成员的内置类型，则需手动完成此事。

void _04Test_rule(){
    int x=0;//对int手动初始化
    const char* text = "A C-style string";//对指针手动初始化
    double d;
    std::cin>>d;//以读取input stream的方式完成初始化
}

//对于内置类型以外的任何东西，初始化将在构造函数身上完成。确保每一个构造函数都将对象的每一个成员初始化
//注意：赋值与初始化是两种行为
class PhoneNumber{PhoneNumber(){} ~PhoneNumber(){}};
class ABEntry{
public:
    ABEntry();
    ABEntry(const std::string& name,
            const std::string& address,
            const std::list<PhoneNumber>& phones);
    ABEntry(const std::string& name,
            const std::string& address,
            const std::string& car,
            const std::list<PhoneNumber>& phones);
private:
    std::string theName;
    std::string theAddress;
    std::string theCar;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
};
//赋值操作
ABEntry::ABEntry(const std::string& name,
        const std::string& address,
        const std::list<PhoneNumber>& phones){
    theName = name;
    theAddress = address;
    thePhones = phones;
    numTimesConsulted = 0;
    //以上成员变量都不是被初始化而是被赋值。
    // 初始化发生的时间更早，发生于成员默认构造函数被自动调用之时，比进入重载的构造函数更早。
}
//C++规定:对象的成员变量的初始化动作发生在进入构造函数本体之前
//成员初值列表
ABEntry::ABEntry(const std::string& name,
                 const std::string& address,
                 const std::string& car,
                 const std::list<PhoneNumber>& phones):
                 theName(name),theAddress(address),theCar(car),
                 thePhones(phones),numTimesConsulted(0)
{
    //该构造函数和上一个的最终结果相同，但通常效率最高
}

//默认构造可以指定nothing作为初始化实参
ABEntry::ABEntry():theName(),theAddress(),
                    theCar(),thePhones(),numTimesConsulted(0)
{
}

//C++有着十分固定的"成员舒适化次序"。
// 次序总是相同:基类(base_classes)更早于其派生类(derived classes)被初始化，
// class的成员变量总是以其声明次序被初始化,即便在成员初值列中与声明次序不同，但是也是按照声明次序依次完成初始化
// 例:初始化array时需要指定大小，因此代表大小的那个成员变量必须先有初值



/*
 * C++中的static对象是指存储区不属于stack和heap、”寿命”从被构造出来直至程序结束为止的对象。
 * 这些对象包括全局对象，定义于namespace作用域的对象，在class、function以及file作用域中被声明为static的对象。
 * 其中，函数内的static对象称为local static对象，而其它static对象称为non-local static对象。
 *
 * local static对象初始化：当函数被第一次调用后才会被构造出来，在main结束后被析构
 * non-loacl static对象初始化:在main函数开始之前就已经被构造出来，在main结束后被析构
*/
//常见文件跨域问题extren抛出对象容易引发初始化次序问题。
//文件1
class FileSystem{
public:
    FileSystem(){}
    ~FileSystem(){}
    std::size_t numDisks() const{
        return 0;
    }
};
extern FileSystem tfs;//抛出对象 此对象可能未经初始化

//文件2
class Diretory{
public:
    Diretory(){
        std::size_t disks = tfs.numDisks();//此对象可能未被初始化，导致不明确调用。C++无法准确的决定它们的初始化顺序
    }
    ~Diretory(){}
};

//如何消除以上问题呢？需要合并两个文件，使用static即可完全解决初始化先后的问题且此时的static是local-static,当函数没有被
//调用时，不会触发static对象的构造，减少内存的使用成本。
//文件3
class _FileSystem_Single{
public:
    _FileSystem_Single(){}
    ~_FileSystem_Single(){}
    std::size_t numDisks() const{
        return 0;
    }
};
FileSystem& _tfs(){
    static FileSystem __tfs;//唯一 类似Singleton
    return __tfs;
}

//文件3 -- 同属一个文件作用域
class _Diretory_Single{
public:
    _Diretory_Single(){
        std::size_t disks = _tfs().numDisks();//经由_tfs调用的_FileSystem_Single必定会初始化
    }
    ~_Diretory_Single(){}
};


//以上情况在多线程使用时需要特别注意，任何一个non-const-static对象，无论是local static或non-loacl static
//在多线程环境下都会产生不确定的因素。所以在启动线程前，应手动调用static引用返回函数(例:_tfs())，即可消除
//与初始化相关的"竞速形式"


/*重点记住:
 * 1.为内置型对象进行手工初始化，因为C++不保证初始化它们。
 * 2.构造函数最好使用成员初值列，而不要在构造函数内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在class中声明的次序相同
 * 3.为免除“跨编译单元的初始化次序问题(如：文件1和文件2产生的问题)”,请使用loacl static对象(文件3中描述)替换non-local static对象
 */


#endif //EFFECTIVECPP_CLAUSE04_BEFORE_USED_OBJECT_MAKSSURE_IS_INITIALIZED_HPP
