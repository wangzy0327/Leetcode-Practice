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
    ListNode* middleNode(ListNode* head) {
        //快慢指针
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
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
    ListNode* res = Solution().middleNode(head);
    cout<<boolalpha<<(res==h2)<<endl;
    /**
     *
    输入：[1,2,3,4,5]
    输出：此列表中的结点 3 (序列化形式：[3,4,5])
    返回的结点值为 3 。 (测评系统对该结点序列化表述是 [3,4,5])
     */
}
