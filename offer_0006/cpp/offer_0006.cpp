//
// Created by wangzy on 2022/3/23.
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
    bool isPalindrome(ListNode* head) {
        //这里采用快慢指针找到 第二段的起始位置节点
        // 1->2->3->2->1  找到 3
        // 1->2->2->1    找到2
        // 然后就地反转 找到的第二段位置
        // 1->2->2->null  1->2->null
        // 1->2->3->null  1->2->3->null
        //然后判断 是否为回文
        //最后将 第二段反转 保持原链表 顺序
        // 1->2->2->1
        // 1->2->3->2->1
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* ano = reverse(slow);
        fast = head;slow = ano;
        while(fast && slow){
            if(fast->val != slow->val)
                break;
            fast = fast->next;
            slow = slow->next;
        }
        //再反转回来
        reverse(ano);
        if(slow && fast)
            return false;
        else
            return true;
    }
private:
    ListNode* reverse(ListNode* node){
        ListNode* pre = nullptr;
        ListNode* cur = node;
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
    ListNode* head = new ListNode(1,new ListNode(2,new ListNode(3)));
    list<int> l = toList<int>(head);
    bool res = Solution().isPalindrome(head);
    printList(l);
    cout<<boolalpha<<res<<endl;
    list<int> l2 = toList<int>(head);
    printList(l2);
    delList(head);
}