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
    TreeNode* convertBST(TreeNode* root) {
        /**
         * 将每个节点的值修改为原来的节点值加上所有大于它的节点值之和
         * 这样我们只需要反序中序遍历该二叉搜索树，记录过程中的节点值之和
         */
        //累加向左
        //遍历方式，先遍历右子树，后遍历左子树,返回
        int sum = 0;
        accumulateBST(root,sum);
        return root;
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
    void accumulateBST(TreeNode* root,int& sum){
        if(root){
            accumulateBST(root->right,sum);
            root->val += sum;
            sum = root->val;
            accumulateBST(root->left,sum);
        }
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
    TreeNode* root = new TreeNode(4);
    TreeNode* left = new TreeNode(1);
    TreeNode* right = new TreeNode(6);
    TreeNode* ll = new TreeNode(0);
    TreeNode* lr = new TreeNode(2);
    TreeNode* rl = new TreeNode(5);
    TreeNode* rr = new TreeNode(7);
    TreeNode* lrr = new TreeNode(3);
    TreeNode* rrr = new TreeNode(8);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    lr->right = lrr;
    rr->right = rrr;
    vector<string> vec = Solution().levelOrderStr(root);
//    [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    printVec(vec);
    TreeNode* anoRoot = Solution().convertBST(root);
    vector<string> vecAno = Solution().levelOrderStr(anoRoot);
    printVec(vecAno);
    //result
//    [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
}