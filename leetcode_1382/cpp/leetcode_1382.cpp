//
// Created by wzy on 2022/4/8.
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
    TreeNode* balanceBST(TreeNode* root) {
        //贪心 取中间节点为根 递归分 左右子树
        vector<TreeNode*> vec;
        inOrderBST(root,vec);
        return balanceHelper(vec,0,vec.size()-1);
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
    void inOrderBST(TreeNode* root,vector<TreeNode*>& vec){
        if(root){
            inOrderBST(root->left,vec);
            vec.push_back(root);
            inOrderBST(root->right,vec);
        }
    }
    TreeNode* balanceHelper(vector<TreeNode*>& vec,int start,int end){
        if(start > end)
            return nullptr;
        else if(start == end)
            return new TreeNode(vec[start]->val);
        int mid = start + (end - start)/2;
        int target = vec[mid]->val;
        TreeNode* root = new TreeNode(target);
        root->left = balanceHelper(vec,start,mid - 1);
        root->right = balanceHelper(vec,mid+1,end);
        return root;
    }
};

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
    TreeNode *root = new TreeNode(1);
//    TreeNode *left = new TreeNode(5);
    TreeNode *right = new TreeNode(2);
//    TreeNode *ll = new TreeNode(1);
//    TreeNode *lr = new TreeNode(7);
//    TreeNode *rl = nullptr;
    TreeNode *rr = new TreeNode(3);
//    root->left = left;
    root->right = right;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
    right->right = rr;
//    ll->left = new TreeNode(0);
    rr->right = new TreeNode(4);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //root = [1,null,2,null,3,null,4,null,null]
    TreeNode* newRoot = Solution().balanceBST(root);
    vector<string> newRootArr = Solution().levelOrderStr(newRoot);
    printVec(newRootArr);
    //result
    //[2,1,3,null,null,null,4]
}