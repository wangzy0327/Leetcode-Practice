//
// Created by wangzy on 2022/4/6.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>
#include <random>
#include <ctime>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        Node* head = nullptr;
        Node* pre = nullptr;
        if(!root)
            return nullptr;
        //中序遍历，保留前一个节点，修改当前节点的左子树指向(左子树已经遍历完可修改)和前一个节点的右子树指向
        inOrderHelper(root,head,pre);
        //最后将首尾节点衔接在一起
        head->left = pre;
        pre->right = head;
        return head;
    }
    vector<string> printTree(Node* root){
        string s;
        vector<string> levelOrder = levelOrderStr(root);
        return levelOrder;
    }
    void deleteTree(Node* root){
        if(root){
            deleteTree(root->left);
            deleteTree(root->right);
            root = nullptr;
        }
    }
    vector<string> levelOrderStr(Node* root){
        vector<Node*> cur;
        vector<Node*> next;
        if(!root)
            return vector<string> {};
        if(root)
            cur.push_back(root);
        vector<string> res;
//        vector<string> curEles;
        while(cur.size()){
            //标识next是否都为null
            int flag = 0;
            for(int i = 0;i < cur.size();i++){
                Node* node = cur[i];
                if(!node){
                    res.push_back("null");
                    continue;
                }
                else
                    res.push_back(to_string(node->val));
                //如果node的孩子不为null,则改变flag
                if(node->left || node->right)
                    flag++;
                next.push_back(node->left);
                next.push_back(node->right);
            }
            cur = next;
            if(flag == 0)
                cur.clear();
            next.clear();
        }
        return res;
    }
private:
    void inOrderHelper(Node* root,Node*& head,Node*& pre){
        if(root){
            inOrderHelper(root->left,head,pre);
            if(!pre){
                head = root;
                pre = root;
            }else{
                pre->right = root;
                root->left = pre;
                pre = root;
            }
            inOrderHelper(root->right,head,pre);
        }
    }
};

void printNode(Node* head){
    Node* cur = head;
    if(!cur){
        cout<<"[]"<<endl;
        return ;
    }
    cout<<"[";
    while(cur->right != head){
        cout<<cur->val<<"->";
        cur = cur->right;
    }
    cout<<cur->val<<"]"<<endl;
}


template<typename T>
void printVec(std::vector<T> l){
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

int main() {
    Node *root = new Node(4);
    Node *left = new Node(2);
    Node *right = new Node(5);
    Node* ll = new Node(1);
    Node* lr = new Node(3);
//    Node* rl = new Node(7);
//    Node* rr = new Node(9);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
//    right->left = rl;
//    right->right = rr;
//    lr->left = new Node(3);
//    lr->right = new Node(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //[4,2,5,1,3]
    Node* head = Solution().treeToDoublyList(root);
    printNode(head);
    //result
    //[1->2->3->4->5]
}