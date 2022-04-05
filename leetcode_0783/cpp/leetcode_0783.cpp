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
    int getMinimumDifference(TreeNode* root) {
        int min_diff = INT_MAX;
        int pre = -1;
        //方法1.中序遍历(BST中序是单调递增 所以 最小差值一定在相邻节点间)
        inOrderDiff(root,pre,min_diff);
        //方法2.
        //因为是二叉搜索树，所以最小差值必定是左子树的最大值与当前节点 或者 当前节点与右子树最小节点之间
        //这里采用后序遍历寻找最小差值
        // getMinHelper(root,min_diff);
        return min_diff;
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

private:
    void inOrderDiff(TreeNode* root,int& pre,int& min_diff){
        if(root){
            inOrderDiff(root->left,pre,min_diff);
            //说明是最小节点
            if(pre == -1)
                pre = root->val;
            else{
                min_diff = min(min_diff,abs(root->val - pre));
                pre = root->val;
            }
            inOrderDiff(root->right,pre,min_diff);
        }
    }
    //为了避免反复向下寻找最大节点和最小节点，采用一次性返回子树最大值和最小值
    pair<TreeNode*,TreeNode*> getMinHelper(TreeNode* root,int& min_diff){
        if(root){
            pair<TreeNode*,TreeNode*> leftPair = getMinHelper(root->left,min_diff);
            pair<TreeNode*,TreeNode*> rightPair = getMinHelper(root->right,min_diff);
            if(leftPair.second)
                min_diff = min(abs(root->val - leftPair.second->val),min_diff);
            if(rightPair.first)
                min_diff = min(abs(root->val - rightPair.first->val),min_diff);
            //返回最大最小值节点
            TreeNode* minNode = (leftPair.first)?leftPair.first:root;
            TreeNode* maxNode = (rightPair.second)?rightPair.second:root;
            return make_pair(minNode,maxNode);
        }
        return make_pair(nullptr,nullptr);
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
    TreeNode* root = new TreeNode(236);
    TreeNode* left = new TreeNode(104);
    TreeNode* right = new TreeNode(701);
    TreeNode* ll = nullptr;
    TreeNode* lr = new TreeNode(227);
    TreeNode* rl = nullptr;
    TreeNode* rr = new TreeNode(911);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    vector<string> vec = Solution().levelOrderStr(root);
    //[236,104,701,null,227,null,911]
    printVec(vec);
    int res = Solution().getMinimumDifference(root);
    cout<<res<<endl;
    //result
    //9
}