//
// Created by wangzy on 2022/4/4.
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
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        //修剪节点 递归判定，如果存在当前节点在[low,high]范围内则继续遍历子树
        //如果当前节点小于low,则返回 右子树满足的节点
        //如果当前节点大于high,则返回 左子树满足的节点
        if(root){
            if(root->val >= low && root->val <= high){
                root->left = trimBST(root->left,low,high);
                root->right = trimBST(root->right,low,high);
                return root;
            }else if(root->val < low){
                return trimBST(root->right,low,high);
            }else if(root->val > high){
                return trimBST(root->left,low,high);
            }
        }
        return nullptr;
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
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(0);
    TreeNode* right = new TreeNode(2);
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
    //root = [1,0,2], low = 1, high = 2
    int low = 1;
    int high = 2;
    TreeNode* anoRoot = Solution().trimBST(root,low,high);
    //[1,null,2]
    vector<string> anoArr = Solution().levelOrderStr(anoRoot);
    printVec(anoArr);
}