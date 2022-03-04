#include<iostream>
#include<vector>

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x):val(x),next(nullptr) {}
    ListNode(int x,ListNode* next):val(x),next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode* node = dummyHead;
        while(node->next){
            if(node->next->val == val){
                ListNode* next = node->next;
                node->next = next->next;
                next = nullptr;
            }else{
                node = node->next;
            }
        }
        ListNode* resNode = dummyHead->next;
        dummyHead = nullptr;
        return resNode;
    }
};

template<typename T>
void printVec(std::vector<T> vec){
    std::cout<<"[";
    int n = (int)vec.size();
    for(auto i = 0;i < n;i++){
        if(i == n - 1){
            std::cout<<vec[i];
        }else{
            std::cout<<vec[i]<<",";
        }
    }
    std::cout<<"]"<<std::endl;
}

void deleteListNode(ListNode* head){
    if(head == nullptr)
        return;
    while(head->next){
        ListNode* next = head->next;
        head->next = next->next;
        next = nullptr;
    }
    head = nullptr;
}

int main(int argc,char* argv[]){
    ListNode* head = new ListNode(1);
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(6);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);
    ListNode* node6 = new ListNode(6);
    int target = 6;
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    std::vector<int> res;
    head = Solution().removeElements(head,target);
    ListNode* node = head;
    while(node){
        res.push_back(node->val);
        node = node->next;
    }
    printVec(res);
    deleteListNode(head);
}