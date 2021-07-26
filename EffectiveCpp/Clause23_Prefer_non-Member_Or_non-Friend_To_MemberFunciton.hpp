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
//����22����Ա����Ӧ����private��������ǣ���ô�����������ĺ������Է�������

/*  Ϊʲônon-member non-friend����Ҫ��class member���߷�װ�ԣ�
 *��һ:class-member/friend�����ܹ�ֱ�ӷ������ڵ�������Դ(private�Լ�enums��typedefs�ȵ�Ҳ������)
 *�ڶ�:non-member/non-friend������ֱ�ӷ������ڵ�˽�л���Դ������Ҳ����ʵ�ֳ�Ա������ʵ�ֵĻ��ܡ�
 *����non-member/non-friend���߷�װ��
 */


#endif //EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
