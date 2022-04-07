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
    vector<vector<int>> BSTSequences(TreeNode* root) {
        //输出所有可能的组合 可以想到用回溯来解决问题
        //组合的特殊性，首选需要保证根节点先入数组，然后才是左右子树
        //该组合的特性满足 层次遍历
        //回溯的结束条件是 数组path为空
        if(!root)
            return vector<vector<int>>{{}};
        vector<TreeNode*> path = {root};
        vector<vector<int>> res;
        vector<int> sub_res;
        dfs(path,res,sub_res);
        return res;
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
    void dfs(vector<TreeNode*>& path,vector<vector<int>>& res,vector<int>& sub_res){
        if(path.size() == 0){
            res.push_back(sub_res);
            return ;
        }
        int sz = path.size();
        // 用于后面回溯恢复状态
        // vector<TreeNode*> copy = vector<TreeNode*>(path);
        for(int i = 0;i < sz;i++){
            TreeNode* cur = path[i];
            //移除path的i位置节点
            path.erase(path.begin()+i);
            sub_res.push_back(cur->val);
            if(cur->left)
                path.push_back(cur->left);
            if(cur->right)
                path.push_back(cur->right);
            //回溯入口
            dfs(path,res,sub_res);
            //恢复原状态
            if(cur->left)
                path.pop_back();
            if(cur->right)
                path.pop_back();
            //将i位置节点放入path
            path.insert(path.begin()+i,cur);
            sub_res.pop_back();
        }
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
    TreeNode *root = new TreeNode(2);
    TreeNode *left = new TreeNode(1);
    TreeNode *right = new TreeNode(3);
//    TreeNode *ll = new TreeNode(1);
//    TreeNode *lr = new TreeNode(3);
//    TreeNode *rl = nullptr;
//    TreeNode *rr = new TreeNode(6);
    root->left = left;
    root->right = right;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
//    right->right = rr;
//    ll->left = new TreeNode(0);
//    lr->right = new TreeNode(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //[2,1,3]
    /**
     *         2
              / \
             1   3
     */
     vector<vector<int>> res ;
     res = Solution().BSTSequences(root);
     printVecArr(res);
     //result
     //[[2,1,3],[2,3,1]]
}