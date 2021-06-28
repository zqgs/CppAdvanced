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
 */

/*
 * the enum hack补偿:一个属于枚举类型的数值可充当ints来使用（模板元编程技术的基础应用）
 */
class GamePlayerEnum{
private:
    enum{NumTurns = 5};//enum行为像#define而不是const
    int scores[NumTurns];
};

/*
 * #define误用:宏看起来像函数，但不会产生函数调用带来的而外开销，用模板代替带参函数宏
*/
//误用
#define CALL_WITH_MAX(a,b) f((a)>(b)?(a):(b))//无论何时写出这类宏，必须为宏中所有实参带上小括号

//正确
template <typename T>
inline void callWithMax(const T&a,const T&b)
{
    f(a > b ? a : b);
}

/*
 *有了consts、enums和inlines我们对预处理器(特别是#define)的需求降低了，但仍需要预处理器来控制编译。但可以减少对预处理器的使用
 * 1.对于单纯的常量，最好以const对象或enums替换#defines
 * 2.对于形似函数的宏，最好改用inline函数替换#defines
 */

#endif //EFFECTIVECPP_CLAUSE02_PREFER_CONSTS_ENUMS_INLINE_TO_DEFINE_HPP
