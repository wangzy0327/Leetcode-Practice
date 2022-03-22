//
// Created by wzy on 2022/3/22.
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
    ListNode *detectCycle(ListNode *head) {
        //快慢指针
        //如果有环，快慢指针相遇后，分别从头节点跟相遇节点向前，直到相遇即为环的索引节点
        //可证明
        // --------
        //    |----|
        //设 a为环前一段，b为从环起点到相遇节点，c为从相遇节点到环起点
        //  2(a+b) = a+b+c+b -> a = c
        //如果无环，快指针则遇到nullptr返回
        if(!head)
            return nullptr;
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow)
                break;
        }
        if(!fast || !fast->next)
            return nullptr;
        //慢指针从头开始，快指针从相遇节点开始 用到证明 a = c
        slow = head;
        while(slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
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
//    ListNode* head = new ListNode(3);
//    ListNode* h1 = new ListNode(2);
//    ListNode* h2 = new ListNode(0);
//    ListNode* h3 = new ListNode(-4);
//    head->next = h1;h1->next = h2;h2->next = h3;
//    h3->next = h1;

    ListNode* head = new ListNode(1);
    ListNode* posNode = Solution().detectCycle(head);
    //result
    //true 没有环
    cout<<boolalpha<<(posNode == nullptr)<<endl;
//    cout<<boolalpha<<(posNode == h1)<<endl;
    //result
    //true  返回入环第一个节点


}
