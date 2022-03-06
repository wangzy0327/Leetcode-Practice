//
// Created by wangzy on 2022/3/6.
//

#include <iostream>
#include <list>
#include <sstream>
#include <string>

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x) : val(x),next(nullptr) {}
    ListNode(int x,ListNode *next):val(x),next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        //1.找到反转左侧、右侧位置节点截取
        //2.反转链表段，然后接上
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode* l = nullptr;
        //考虑到要保存左节点的前一个节点，所以这里创建一个虚拟头结点
        ListNode* cur = dummyHead;
        //移动到left的前一个位置,从1移动到left位置需要left - 1 步
        for(int i = 1;i < left ;i++)
            cur = cur->next;
        ListNode* lPre = cur;
        cur = cur->next;
        l = cur;
        for(int i = left;i < right ;i++)
            cur = cur->next;
        ListNode* rSucc = cur->next;
        cur->next = nullptr;
        ListNode* reverHead = reverse(l);
        l->next = rSucc;
        lPre->next = reverHead;
        ListNode* ret = dummyHead->next;
        delete dummyHead;
        return ret;
    }
    ListNode* reverse(ListNode* head){
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur){
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};

void delList(ListNode* head){
    ListNode* cur = head;
    while(cur && cur->next){
        ListNode* next = cur->next;
        cur = nullptr;
        cur = next;
    }
    cur = nullptr;
}

template<typename T>
void printVec(std::list<T> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << ele;
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    std::cout<<res<<std::endl;
}

template<typename T>
std::list<T> toList(ListNode* head){
    std::list<T> l;
    ListNode* cur = head;
    while(cur){
        l.push_back(cur->val);
        cur = cur->next;
    }
    return l;
}

int main(){
    ListNode* head = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4,new ListNode(5)))));
    std::list<int> l = toList<int>(head);
    printVec<int>(l);
    int left = 2;
    int right = 4;
//    ListNode* anoHead = Solution().reverseList(head);
    ListNode* anoHead = Solution().reverseBetween(head,left,right);
    std::list<int> reverseL = toList<int>(anoHead);
    printVec<int>(reverseL);
    delList(anoHead);
}


