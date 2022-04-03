//
// Created by wangzy on 2022/4/3.
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        /**
        二分来 分别求出有序 数组段 中最短的 子树并返回根节点
        */
        if(nums.size() == 0)
            return nullptr;
        TreeNode* root = rebuildBST(nums,0,nums.size()-1);
        return root;
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
    TreeNode* rebuildBST(vector<int>& nums,int start,int end){
        if(start > end)
            return nullptr;
        if(start == end)
            return new TreeNode(nums[start]);
        int mid = start + (end - start)/2;
        int rootVal = nums[mid];
        TreeNode* root = new TreeNode(rootVal);
        root->left = rebuildBST(nums,start,mid-1);
        root->right = rebuildBST(nums,mid+1,end);
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
//    TreeNode* root = new TreeNode(5);
//    TreeNode* left = new TreeNode(3);
//    TreeNode* right = new TreeNode(6);
//    TreeNode* ll = new TreeNode(2);
//    TreeNode* lr = new TreeNode(4);
//    TreeNode* rl = nullptr;
//    TreeNode* rr = new TreeNode(7);
//    root->left = left;
//    root->right = right;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
//    right->right = rr;
    vector<int> nums = {-10,-3,0,5,9};
    //给定有序数组: [-10,-3,0,5,9]
    TreeNode* root = Solution().sortedArrayToBST(nums);
    vector<string> res = Solution().levelOrderStr(root);
    printVec(res);
    //[0,-10,5,null,-3,null,9]
    //一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树
}
