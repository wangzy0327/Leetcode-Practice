//
// Created by wangzy on 2022/3/5.
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
    	//思路： 总共有两个链表，一个原来链表，一个新链表(初始为nullptr)
    	// 将原来链表依次取下头节点，在新链表上以头插法依次插入，知道原来链表为nullptr
    	// 常规化反转,不用区分头节点是否为nullptr
    	// pre代表 反转后的头节点，cur 表示当前链表的头节点
    	// 操作将源链表 的头节点依次取下，通过头插法更新pre的反转链表
    	// 以 1-2->3 为例
    	// cur:1->2->3  pre:nullptr 
    	// cur:2->3     pre:1->nullptr
    	// cur:3        pre:2->1->nullptr
    	// cur:nullptr  pre: 3->2->1->nullptr
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
    ListNode* reverseList3(ListNode* head){
    	//思路： 自始至终为一个链表，直到原来链表的头节点位于链表末尾
    	// 不断将当前节点的下一个节点取下，链接到当前链表的头部 知道当前节点(原头节点)下一个节点为nullptr
    	// 不断的将 p的下一个节点取下放在 当前链表头 
    	// nHead代表头节点，p代表当前节点 
    	// 需要区分头节点是否为空
    	if(head == nullptr)
            return head;
        ListNode* nHead = head;
        ListNode* p = head;
        while(p->next){
            ListNode* q = p->next;
            p->next = q->next;
            q->next = nHead;
            nHead = q;
        }
        return nHead;
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
//    ListNode* anoHead = Solution().reverseList3(head);
    std::list<int> reverseL = toList<int>(anoHead);
    printVec<int>(reverseL);
    delList(anoHead);
}

