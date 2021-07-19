//
// Created by 曾庆国 on 2021/7/19.
//

#ifndef EFFECTIVECPP_CLAUSE16_SAME_FROM_OF_NEW_AND_DELETE_HPP
#define EFFECTIVECPP_CLAUSE16_SAME_FROM_OF_NEW_AND_DELETE_HPP
#include <string>
//条款16:成对使用new和delete时要采取相同形式

/*了解new和delete的实现过程：
 * 1.使用new时有两件事发生：第一，内存被分配出来（通过operator new的函数）。
 *第二，针对此内存会有一个（或多个）构造函数被调用。
 * 2.使用delete时也有两件事发生：第一，针对此内存会与欧一个（或多个）析构函数被调用
 *第二，内存被释放。（通过名为operator delete的函数）
 */


//正确使用delete
void CL15_Test01()
{
    std::string *stringPtr1 = new std::string;
    std::string *strinfgPtr2 = new std::string[10];

    delete stringPtr1;//删除一个对象
    delete [] strinfgPtr2;//删除一个由对象组成的数组
}
//重点记住
//使用规则：new时使用[]，delete时使用[]。反之则一样



#endif //EFFECTIVECPP_CLAUSE16_SAME_FROM_OF_NEW_AND_DELETE_HPP
