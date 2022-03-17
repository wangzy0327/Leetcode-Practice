//
// Created by wangzy on 2022/3/17.
//

#include<iostream>
#include<sstream>
#include <string>
#include<list>

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x) : val(x),next(nullptr) {}
    ListNode(int x,ListNode *next):val(x),next(next) {}
};

class Solution{
public:
    ListNode* reverseList(ListNode* head) {
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
    ListNode* reverseList2(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        ListNode* ret = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return ret;
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
//    ListNode* anoHead = Solution().reverseList(head);
    ListNode* anoHead = Solution().reverseList2(head);
    std::list<int> reverseL = toList<int>(anoHead);
    printVec<int>(reverseL);
    delList(anoHead);
}

