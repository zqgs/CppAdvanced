//
// Created by Sea on 2021/6/23.
//

#ifndef EFFECTIVECPP_CLAUSE01_VIEWCPP_AS_A_FEADERATION_OF_LANGUAGES_HPP
#define EFFECTIVECPP_CLAUSE01_VIEWCPP_AS_A_FEADERATION_OF_LANGUAGES_HPP


//条款01 视C++为一个语言联邦
/*C++主要分为四个部分:
 * 1.C.C++仍然是以C为基础。区块（blocks）、语句（statements）、预处理器（preprocessor）、内置数据类型（built-in data type）、
 * 数组（array）、指针（point）等都是来自于C。许多时候C++对问题的解法不过就是较高级的C解法，当以C++内的C成分工作时搞笑编程守则
 * 映射出C语言的局限:没有模板（templates）、没有异常（exceptions）、没有重载（overloading）等等
 *
 *
 * 2.Object-Oriented C++.这部分也就是C with Classes所诉求的:classes（包括构造函数和析构函数）、封装（encapsulation）、继承（inheritance）、
 * 多态（polymorphism）、virsual函数（动态绑定）等等.这一部分是面向对象设计在C++上最直接的体现。
 *
 *
 * 3.Template C++.这是C++的泛型编程(generic programming)部分，Template相关考虑与设计已经涵盖整个C++,良好编程守则中"唯template适用"的特殊条款
 * 并不罕见。实际上由于templates威力强大，他们带来崭新的编程范型，也就是template metaprogramming(TMP,模板元编程)。
 *
 * 4.STL.STL是个template程序库。它对容器（containers）、迭代器（iterators）、算法（algorithms）以及函数对象（function object）的
 * 规约有极佳的紧密配合与协调。
 *
 */

/*
 * 对于内置(C-Like类C)类型而言pass-by-value(值传递)通常比pass-by-reference(引用传递)高效，当从C part of C++移往Object-Oriented C++，
 * 由于用于自定义(user-defined)构造函数和析构函数的存在，pass-by-reference-const(只读引用传递)往往更好。运行Template C++时尤其如此，因为
 * 此时你甚至都不知道所处理的对象的类型。然后一旦跨入STL,迭代器和函数对象都是在C point之上塑造出来的，所以STL的迭代器和函数对象而言，旧式的
 * C pass-by-value守则再次适用
 */


/*重点记住:
 * C++高效编程守则视情况而变化，取决于你使用C++的哪个部分
 */



#endif //EFFECTIVECPP_CLAUSE01_VIEWCPP_AS_A_FEADERATION_OF_LANGUAGES_HPP
