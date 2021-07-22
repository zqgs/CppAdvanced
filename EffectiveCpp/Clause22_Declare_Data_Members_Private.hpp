//
// Created by Sea on 2021/7/21.
//

#ifndef EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP
#define EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP

//条款22:将成员变量声明为private

//1.实现精准控制:以函数返回让成员变量
class AccessLevels{
public:
    int getReadOnly() const{return readOnly;}
    void setReadWirte(int value) {ReadWrite = value; }
    int getReadWirte()const {return ReadWrite;}
    void setWirteOnly(int value) {writeOnly = value;}
private:
    int noAccess;//对此int无任何访问动作
    int readOnly;//对此int做只读访问
    int ReadWrite;//对此int做读写访问
    int writeOnly;//对此int做只写访问
};


//2.C++封装性质:使用函数访问成员变量(内部实现与外部调用分离)
class SpeedDaeCollection{
public:
    void addValue(int Speed){}
    double averageSoFar() const{}
    //averageSoFar实现方式:实时调用计算/分时调用计算，如果获取平均值以函数的方式呈现，就可以在函数内部自由的实现。
    //将成员变量隐藏在函数接口背后，可以为"所有可能的实现"提供弹性。
};

//从封装的角度观看:其实只有两种访问权限:private(提供封装)和其他(不提供封装)

/*重点记住:
 * 1.切记将成员变量声明为private。这可赋予调用着访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，
 *并提供class作者充分的实现弹性。
 * 2.protected并不比public更具封装性
 */

#endif //EFFECTIVECPP_CLAUSE22_DECLARE_DATA_MEMBERS_PRIVATE_HPP
