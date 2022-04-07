//
// Created by wzy on 2022/4/7.
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

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0),left(nullptr),right(nullptr) {}
    TreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
    TreeNode(int x,TreeNode *left,TreeNode* right):val(x),left(left),right(right) {}
};

class Solution {
public:
    TreeNode* convertBiNode(TreeNode* root) {
        //按照BST中序遍历，保证从小到大顺序,保存pre前一个节点,来改动链表
        TreeNode* pre = nullptr;
        TreeNode* head = nullptr;
        inorderConvert(root,head,pre);
        // pre->left = nullptr;
        return head;
    }

    vector<string> printTree(TreeNode* root){
        string s;
        vector<string> levelOrder = levelOrderStr(root);
        return levelOrder;
    }
    void deleteTree(TreeNode* root){
        if(root){
            deleteTree(root->left);
            deleteTree(root->right);
            root = nullptr;
        }
    }
    vector<string> levelOrderStr(TreeNode* root){
        vector<TreeNode*> cur;
        vector<TreeNode*> next;
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
                TreeNode* node = cur[i];
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
    void inorderConvert(TreeNode* root,TreeNode*& head,TreeNode*& pre){
        if(root){
            inorderConvert(root->left,head,pre);
            if(!pre){
                pre = root;
                head = root;
            }else{
                pre->right = root;
                // pre->left = nullptr;
                //注意将root的左边节点置为nullptr
                root->left = nullptr;
                pre = root;
            }
            inorderConvert(root->right,head,pre);
        }
    }
};

void printNode(TreeNode* head){
    TreeNode* cur = head;
    if(!cur){
        cout<<"[]"<<endl;
        return ;
    }
    cout<<"[";
    while(cur->right){
        cout<<cur->val<<",";
        if(cur->left)
            cur = cur->left;
        else
            cout<<"null,";
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
    TreeNode *root = new TreeNode(4);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(5);
    TreeNode* ll = new TreeNode(1);
    TreeNode* lr = new TreeNode(3);
    TreeNode* rl = nullptr;
    TreeNode* rr = new TreeNode(6);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    ll->left = new TreeNode(0);
//    lr->right = new TreeNode(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //[4,2,5,1,3,null,6,0]
    //[4,2,5,1,3,null,6,0,null,null,null,null,null]
    TreeNode* head = Solution().convertBiNode(root);
    printNode(head);
    //result
    //[0,null,1,null,2,null,3,null,4,null,5,null,6]
}