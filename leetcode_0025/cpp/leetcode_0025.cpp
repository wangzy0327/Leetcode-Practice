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

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode* cur = dummyHead;
        //每个待反转k段的前置节点
        ListNode* lPre = cur;
        //每个待反转k段节点的后续节点
        ListNode* rSucc = nullptr;
        ListNode* l = nullptr;
        while(cur){
            //l为每个k段节点的最左端节点
            l = cur->next;
            for(int i = 1;i <= k && cur ;i++)
                cur = cur->next;
            //如果剩余节点不足k，保持原顺序返回
            if(!cur)
                break;
            //保存k段节点的后序节点,并截断当前k个节点
            rSucc = cur->next;
            cur->next = nullptr;
            //反转当前k个节点
            ListNode* reverseHead = reverse(l);
            //连接截取的前置节点和后序节点
            lPre->next = reverseHead;
            l->next = rSucc;
            //重置前置节点和当前节点
            lPre = l;
            cur = lPre;
        }
        ListNode* ret = dummyHead->next;
        dummyHead = nullptr;
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

int main(){
    ListNode* head = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4,new ListNode(5)))));
    std::list<int> l = toList<int>(head);
    printVec<int>(l);
    int k = 2;
    ListNode* anoHead = Solution().reverseKGroup(head,k);
    std::list<int> reverseL = toList<int>(anoHead);
    printVec<int>(reverseL);
    delList(anoHead);
//  result
//    [1,2,3,4,5]
//    [2,1,4,3,5]
}