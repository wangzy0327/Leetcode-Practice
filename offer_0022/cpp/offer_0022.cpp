//
// Created by wangzy on 2022/3/22.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x) : val(x),next(nullptr) {}
    ListNode(int x,ListNode *next):val(x),next(next) {}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        //快慢指针
        ListNode* fast = head;
        ListNode* slow = head;
        int i = 0;
        while(i < k && fast){
            fast = fast->next;
            i++;
        }
        while(fast){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
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
void printList(std::list<T> l){
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

int main() {
    ListNode* head = new ListNode(1);
    ListNode* h1 = new ListNode(2);
    ListNode* h2 = new ListNode(3);
    ListNode* h3 = new ListNode(4);
    ListNode* h4 = new ListNode(5);
    head->next = h1;h1->next = h2;h2->next = h3;h3->next = h4;
    int k = 2;
    ListNode* res = Solution().getKthFromEnd(head,k);
    list<int> l = toList<int>(head);
    printList(l);
    list<int> l_res = toList<int>(res);
    printList(l_res);
    delList(head);
    //result
    //[1,2,3,4,5]
    //[4,5]
    /**
     * 给定一个链表: 1->2->3->4->5, 和 k = 2.
        返回链表 4->5.
     *
     */
}