//
// Created by wzy on 2022/4/11.
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
    int maxSumBST(TreeNode* root) {
        //每个子树返回最大和最小值
        //然后比较左右子树的最大最小值来确定是否为BST
        this->val = 0;
        this->minNode = nullptr;
        this->maxNode = nullptr;
        helper(root);
        return this->val;
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
    //保存子树的最小节点和最大节点
    TreeNode* minNode;
    TreeNode* maxNode;
    int val;
    //每次递归返回需要保存当前子树是否是BST以及其BST累加和
    pair<int,bool> helper(TreeNode* root){
        if(root){
            pair<int,bool> leftPair = helper(root->left);
            TreeNode* lMinNode = minNode;
            TreeNode* lMaxNode = maxNode;
            //为了不影响右子树的最大最小节点，重置TreeNode值
            minNode = nullptr;maxNode = nullptr;
            pair<int,bool> rightPair = helper(root->right);
            TreeNode* rMinNode = minNode;
            TreeNode* rMaxNode = maxNode;
            //如果左右子树返回键值和为负数的话
            if(!leftPair.second  || !rightPair.second)
                return make_pair(-1,false);
            //如果不满足BST树的话
            if(lMaxNode && lMaxNode->val >= root->val)
                return make_pair(-1,false);
            if(rMinNode && rMinNode->val <= root->val)
                return make_pair(-1,false);
            //更新最大节点和最小节点
            maxNode = rMaxNode?rMaxNode:root;
            minNode = lMinNode?lMinNode:root;
            //否则满足BST树，更新val
            int sub_res = leftPair.first+rightPair.first+root->val;
            if(sub_res > this->val)
                this->val = sub_res;
            return make_pair(sub_res,true);
        }
        return make_pair(0,true);
    }
};

class Solution2 {
public:
    int maxSumBST(TreeNode* root) {
        /**
        后序遍历，递归函数traverse()返回一个int[]，长度为4，每个元素分别代表：

        以root为根节点的二叉树是否为二叉搜索树（是为1，不是为0）
        以root为根节点的二叉树中的最小节点值
        以root为根节点的二叉树中的最大节点值
        以root为根节点的二叉树中的所有节点值之和
        ans为全局变量，维护全局最大值，也是最终返回的结果
        */
        ans = 0;
        postTraverse(root);
        return ans;
    }
private:
    int ans;
    vector<int> postTraverse(TreeNode* root){
        if(root){
            vector<int> lRes = postTraverse(root->left);
            vector<int> rRes = postTraverse(root->right);
            //左右子树如果有一个不是BST 或者
            //当前节点大于等于左子树最大节点或小于等于右子树最小节点
            if(!lRes[0] || !rRes[0] || root->val<=lRes[2] || root->val>=rRes[1])
                return {0,INT_MAX,INT_MIN,0};
            int min_num = min(root->val,lRes[1]);
            int max_num = max(root->val,rRes[2]);
            int sum = lRes[3]+root->val+rRes[3];
            ans = max(sum,ans);
            return vector<int>{1,min_num,max_num,sum};
        }
        return {1,INT_MAX,INT_MIN,0};
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
    TreeNode *left = new TreeNode(4);
    TreeNode *right = new TreeNode(3);
    TreeNode *ll = new TreeNode(2);
    TreeNode *lr = new TreeNode(4);
    TreeNode *rl = new TreeNode(2);
    TreeNode *rr = new TreeNode(5);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    rr->left = new TreeNode(4);
    rr->right = new TreeNode(6);
    vector<string> rootArr1 = Solution().levelOrderStr(root);
    printVec(rootArr1);
    //root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
    int res1 = Solution().maxSumBST(root);
    cout<<res1<<endl;
    //result
    //20
    int res2 = Solution2().maxSumBST(root);
    cout<<res2<<endl;
    //result
    //20
}
