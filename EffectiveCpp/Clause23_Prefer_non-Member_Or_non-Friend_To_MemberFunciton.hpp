//
// Created by Sea on 2021/7/22.
//

#ifndef EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
#define EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP

//����23:����non-member��non-friend�滻member����

//��1:
class WebBrowser{
public:
    void clearCache(){}
    void clearHistory(){}
    void removeCookies(){}
    //�����ͬʱִ��һЩ���������ܻ��ṩһ�������ĺ���
    void clearEverything(){
        clearCache();
        clearHistory();
        removeCookies();
    }
};

//Ҳ�п�����һ���ǳ�Ա����
void clearBrowserexp1(WebBrowser &wb){
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}

//˼��:����clear������ʵ�ָ��ã�
//�ӷ�װ�ĽǶ�˼��:Խ�ٵĴ�����Է�����������Խ������ݿɱ���װ�������Ǿ�Խ�����ɵĸı�������ݡ�

/*  Ϊʲônon-member non-friend����Ҫ��class member���߷�װ�ԣ�
 *��һ:class-member/friend�����ܹ�ֱ�ӷ������ڵ�������Դ(private�Լ�enums��typedefs�ȵ�Ҳ������)
 *�ڶ�:non-member/non-friend������ֱ�ӷ������ڵ�˽�л���Դ������Ҳ����ʵ�ֳ�Ա������ʵ�ֵĻ��ܡ�
 *����non-member/non-friend���߷�װ��
 */


/* ����Ϊʲônon-member/non-friendΪʲôҪ��class member���߷�װ�ԡ���Ҫע������:
 * ��һ:��������ֻ������non-member/non-friend������friend������private��Ա����Ȩ����member������ͬ��
 *������ߵĶԷ�װ��������ͬ��
 * �ڶ�:ֻ�������װ�Զ��ú���"��Ϊ���non-member",������ζ��"����������һ�����member"��������non-member
 *��Ϊstatic member������ֻҪ����classһ���ֻ��Ϊ��friend���Ͳ���Ӱ��class�ķ�װ�ԡ�
 */

//����˼����������C++�е�ʵ��:
namespace WebBrowserStuff{
    class  WebBrowserExp2{};
    void clearBrowser(WebBrowserExp2 &wb){}
}
//��һ����ӵ�д����ı����������ֱ����ͨ��;�����ǿ���ģ��C++��׼����ʵ�����Ƶ�Ч��
//ͷ�ļ�1:#include "WebBrowserExp3.h" ��ʾ���Ļ���
namespace WebBrowserStuff{
    class  WebBrowserExp3{};
    void clearBrowser(WebBrowserExp3 &wb){}
}
//ͷ�ļ�2:#include ""WebBrowserfun1.h"" ��ʾ����1
namespace WebBrowserStuff{
    void BrowserFun1(WebBrowserExp3 &wb){}
}
//ͷ�ļ�3:#include ""WebBrowserfun2.h"" ��ʾ����2
namespace WebBrowserStuff{
    void BrowserFun2(WebBrowserExp3 &wb){}
}

//����ʵ�ַ�ʽ����C++��׼�����֯��ʽ�����û���ʹ��ĳЩ����ʱ�����Խ���������ͷ�ļ����������̶ȵĽ����˱���������
//���ַ�ʽ�����������и�class�ĳ�Ա��������Ϊclass�������嶨�壬���ܱ��и�ΪƬ�Ρ�


//����������������ڶ��ͷ�ļ��ڣ�������ͬһ�������ռ䣬��ζ�ſ���������չ��һ����������
//ֻ��Ҫ�������non-member/non-friend������ӽ��������ռ��ڣ���������Ӧ��ͷ�ļ����ɡ�

//namespace���class��class����ʽ��Կͻ�����ʱ������չ��(��չ��ʽֻ��ͨ�����������������޷����ʻ����private)��

/*�ص��ס:
 * 1.������non-member��non-friend�滻member�������������������ӷ�װ�ԡ��������Ժͻ��������ԡ�
 */

#endif //EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
