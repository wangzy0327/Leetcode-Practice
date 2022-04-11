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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //思路：递归求解：由于所有节点的值均为唯一的
        //递归左子树、右子树 ，如果存在p或q，则返回左子树根，或右子树根,否则返回null
        //如果递归返回的左右子树均不为null,则返回当前节点(说明p、q分别在左右子树找到了)
        //如果递归返回的左右子树任何一个为null,则返回当前节点
        if(root){
            TreeNode* lRes = lowestCommonAncestor(root->left,p,q);
            TreeNode* rRes = lowestCommonAncestor(root->right,p,q);
            if(!lRes && root->val != p->val && root->val != q->val)
                return rRes;
            else if(!rRes && root->val != p->val && root->val != q->val)
                return lRes;
            else{
                //lRes && rRes
                //!lRes && (root->val == p->val || root->val == q->val)
                //!rRes && (root->val == p->val || root->val == q->val)
                return root;
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
    TreeNode *root = new TreeNode(3);
    TreeNode *left = new TreeNode(5);
    TreeNode *right = new TreeNode(1);
    TreeNode *ll = new TreeNode(6);
    TreeNode *lr = new TreeNode(2);
    TreeNode *rl = new TreeNode(0);
    TreeNode *rr = new TreeNode(8);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    lr->left = new TreeNode(7);
    lr->right = new TreeNode(4);
    vector<string> rootArr1 = Solution().levelOrderStr(root);
    printVec(rootArr1);
//    root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//  [3,5,1,6,2,0,8,null,null,7,4,null,null,null,null]
    TreeNode* p = left;
    TreeNode* q = right;
    TreeNode* res = Solution().lowestCommonAncestor(root,p,q);
    cout<<res->val<<endl;
    //result
    //3
}