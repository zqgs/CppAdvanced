//
// Created by Sea on 2021/6/23.
//

#ifndef EFFECTIVECPP_CLAUSE02_PREFER_CONSTS_ENUMS_INLINE_TO_DEFINE_HPP
#define EFFECTIVECPP_CLAUSE02_PREFER_CONSTS_ENUMS_INLINE_TO_DEFINE_HPP
#include <string>




//条款02：尽量以编译器替换预处理器（以const,enum,inline替换#define）
/*取代原因:
 * 1.#define只会在预处理阶段完成宏替换，宏名称可能没有进入记号表内，当编译发生错误，错误信息可能索引不到宏从而
 * 带来不必要的麻烦。
 * 2.在调试阶段原因也可能是索引不到宏，所使用的名称未进入记号表，导致调试产出不必要的麻烦
 */

#define ASPECT_RATIO 1.653 //预处理器阶段被执行替换操作
const int AspectRation = 1.653;//编译阶段会检查数据类型，运行阶段完成值的替换


//若要在头文件内定义一个常量(不可改变)的char*-base的字符串，必须写两次const
const char* const authName= "zengqingguo";

//通常string对象比char*-base更合适
const std::string strAuthName = "zengqingguo";

//class专属常量，将常量的作用域限制于class内，该常量的使用范围将属于整个class，而非某个对象
class GamePlayer{
private:
    static const int Numturns = 5;//常量声明式（C++要求对所使用的任何东西提供一个定义式） 常量只会初始化时创建一次，所有对象都可以反复调用
    int scores[Numturns];
};
//如果该常量是class的专属常量又是static且为整数类型（ints,chars,bools）,只要不取它们的地址，则可以声明并使用，无须提供定义式
const int GamePlayer::Numturns;//由于声明时已经获得初值，定义时无须再设初值

/*无法利用#define来创建一个class专属常量，#define并不重视作用域。一旦宏被定义，它将再之后的编译过程都有效(除非某处被#undef)
 *
 */




#endif //EFFECTIVECPP_CLAUSE02_PREFER_CONSTS_ENUMS_INLINE_TO_DEFINE_HPP
