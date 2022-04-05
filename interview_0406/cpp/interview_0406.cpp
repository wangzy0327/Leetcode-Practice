//
// Created by wangzy on 2022/4/5.
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        //思路：记录前一个节点，如果前一个节点就是制定的节点
        //则返回当前节点
        TreeNode* pre = nullptr;
        return finder(root,p,pre);
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
    TreeNode* finder(TreeNode* root,TreeNode* p,TreeNode* &pre){
        if(root){
            TreeNode* lNode = finder(root->left,p,pre);
            if(lNode)
                return lNode;
            if(!pre)
                pre = root;
            else if(pre == p)
                return root;
            else
                pre = root;
            TreeNode* rNode = finder(root->right,p,pre);
            if(rNode)
                return rNode;
        }
        return nullptr;
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
    TreeNode* root = new TreeNode(2);
    TreeNode* left = new TreeNode(1);
    TreeNode* right = new TreeNode(3);
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
    //[2,1,3]
    TreeNode* res = Solution().inorderSuccessor(root,left);
    cout<<res->val<<endl;
    //result
    //2
}