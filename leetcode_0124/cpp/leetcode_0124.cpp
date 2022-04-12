//
// Created by wzy on 2022/4/12.
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
    int maxPathSum(TreeNode* root) {
        //思路：最大路径和求解 通过 当前节点与左右子树最大路径之和更新最大路径sum来递归求解
        //由于至少包含一个节点，且节点可能为负值，所以将最大路径和初值置为INT_MIN
        ans = INT_MIN;
        maxPathHelper(root);
        return ans;
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
    int ans;
    //返回包含当前节点的最大子路径
    int maxPathHelper(TreeNode* root){
        if(root){
            //这里需要注意，左子树最大子路径 可能为负值，负值的话就可以不要左侧子路径
            int leftSub = max(0,maxPathHelper(root->left));
            int rightSub = max(0,maxPathHelper(root->right));
            //更新最大路径和
            ans = max(ans,root->val + leftSub + rightSub);
            //返回最大子路径
            return max(leftSub,rightSub) + root->val;
        }
        //空节点返回路径为0
        return 0;
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
    TreeNode *root = new TreeNode(-10);
    TreeNode *left = new TreeNode(9);
    TreeNode *right = new TreeNode(20);
    TreeNode *ll = nullptr;
    TreeNode *lr = nullptr;
    TreeNode *rl = new TreeNode(15);
    TreeNode *rr = new TreeNode(7);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    vector<string> rootArr1 = Solution().levelOrderStr(root);
    printVec(rootArr1);
    // [-10,9,20,null,null,15,7]
    int res = Solution().maxPathSum(root);
    cout<<res<<endl;
    //result
    //42
    //最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
}