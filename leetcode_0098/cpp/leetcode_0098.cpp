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
    bool isValidBST(TreeNode* root) {
        //检测合法BST，可用中序遍历来检测
        TreeNode* pre = nullptr;
        return inOrder(root,pre);
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
    bool inOrder(TreeNode* root,TreeNode*& pre){
        if(root){
            bool leftValid = inOrder(root->left,pre);
            if(!leftValid)
                return false;
            if(!pre)
                pre = root;
                //注意这里如果存在相同节点,则返回false
                //BST不应该存在相同元素
            else if(pre->val >= root->val)
                return false;
            else{
                //pre->val < root->val
                pre = root;
            }
            bool rightValid = inOrder(root->right,pre);
            if(!rightValid)
                return false;
        }
        return true;
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
    TreeNode* root = new TreeNode(5);
    TreeNode* left = new TreeNode(1);
    TreeNode* right = new TreeNode(4);
    TreeNode* ll = nullptr;
    TreeNode* lr = nullptr;
    TreeNode* rl = new TreeNode(3);
    TreeNode* rr = new TreeNode(6);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    bool res = Solution().isValidBST(root);
    vector<string> rootArr = Solution().levelOrderStr(root);
    //[5,1,4,null,null,3,6]
    printVec(rootArr);
    cout<<boolalpha<<res<<endl;
    //result
    //false;
}
