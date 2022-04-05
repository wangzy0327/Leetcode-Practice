//
// Created by wangzy on 2022/4/5.
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
    TreeNode* increasingBST(TreeNode* root) {
        deque<TreeNode*> dq;
        inOrder(root,dq);
        return rebuild(dq);
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
    void inOrder(TreeNode* root,deque<TreeNode*>& dq){
        if(root){
            inOrder(root->left,dq);
            root->left = nullptr;
            dq.push_back(root);
            inOrder(root->right,dq);
        }
    }
    TreeNode* rebuild(deque<TreeNode*>& dq){
        TreeNode* pre = nullptr;
        TreeNode* cur = nullptr;
        TreeNode* root = nullptr;
        while(dq.size()){
            if(!root){
                root = dq.front();
                pre = root;
                dq.pop_front();
            }
            else{
                cur = dq.front();
                dq.pop_front();
                pre->right = cur;
                pre = cur;
            }
        }
        if(pre)
            pre->right = nullptr;
        return root;
    }
};


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
    TreeNode *root = new TreeNode(5);
    TreeNode *left = new TreeNode(1);
    TreeNode *right = new TreeNode(7);
//    TreeNode* ll = nullptr;
//    TreeNode* lr = nullptr;
//    TreeNode* rl = new TreeNode(3);
//    TreeNode* rr = new TreeNode(6);
    root->left = left;
    root->right = right;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
//    right->right = rr;
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //root = [5,1,7]
    TreeNode* ano = Solution().increasingBST(root);
    vector<string> anoArr = Solution().levelOrderStr(ano);
    printVec(anoArr);
    //result
    //[1,null,5,null,7]
}