//
// Created by wzy on 2022/4/6.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //因为p,q节点均存在在树中，且在BST中可以确定其在哪个子树里
        //分为3中情况:
        //1、如果p在root的左子树中，q在root的右子树中，则返回root
        //2、如果p、q均在root的左子树中,则递归返回左子树的调用
        //3、如果p、q均在root的右子树中,则递归返回右子树的调用
        if(p->val <= root->val && q->val >= root->val || p->val >= root->val && q->val <= root->val)
            return root;
        else if(p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left,p,q);
        else
            //if(p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right,p,q);
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
    TreeNode *root = new TreeNode(6);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(8);
    TreeNode* ll = new TreeNode(0);
    TreeNode* lr = new TreeNode(4);
    TreeNode* rl = new TreeNode(7);
    TreeNode* rr = new TreeNode(9);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    lr->left = new TreeNode(3);
    lr->right = new TreeNode(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    // [6,2,8,0,4,7,9,null,null,3,5,null,null,null,null]
    int k = 1;
    TreeNode* ancestor = Solution().lowestCommonAncestor(root,left,right);
    cout<<ancestor->val<<endl;
    //result
    //6
}