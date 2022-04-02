//
// Created by wzy on 2022/4/2.
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root)
            return new TreeNode(val);
        if(root){
            if(val < root->val)
                root->left = insertIntoBST(root->left,val);
            else if(val > root->val)
                root->right = insertIntoBST(root->right,val);
        }
        return root;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<TreeNode*> cur;
        vector<TreeNode*> next;
        if(!root)
            return vector<vector<int>> {};
        if(root)
            cur.push_back(root);
        vector<vector<int>> res;
        vector<int> curEles;
        while(cur.size()){
            for(int i = 0;i < cur.size();i++){
                TreeNode* node = cur[i];
                curEles.push_back(node->val);
                if(node->left)
                    next.push_back(node->left);
                if(node->right)
                    next.push_back(node->right);
            }
            res.push_back(curEles);
            curEles.clear();
            cur = next;
            next.clear();
        }
        return res;
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

template<typename T>
string convertVecToStr(std::vector<T> l){
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
    return res;
}

template<typename T>
void printVecArr(std::vector<std::vector<T>> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << convertVecToStr(ele);
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
    TreeNode *right = new TreeNode(7);
    TreeNode *ll = new TreeNode(1);
    TreeNode *lr = new TreeNode(3);
    TreeNode *rl = nullptr;
    TreeNode *rr = nullptr;
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    vector<string> vec = Solution().levelOrderStr(root);
//    [4,2,7,1,3,null,null]
    printVec(vec);
    int val = 5;
    TreeNode* anoRoot = Solution().insertIntoBST(root,val);
    vector<string> vecAno = Solution().levelOrderStr(anoRoot);
    printVec(vecAno);
    //result
    //[4,2,7,1,3,5,null]
}