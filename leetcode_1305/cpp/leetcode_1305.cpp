//
// Created by wangzy on 2022/4/9.
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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        //思路：1、利用中序遍历将BST的节点以从小到大顺序排列
        //2、再利用数组排序的方式排序两个列表
        vector<int> vec1;
        vector<int> vec2;
        inOrderBSTHelper(root1,vec1);
        inOrderBSTHelper(root2,vec2);
        vector<int> res;
        sortArrHelper(vec1,vec2,res);
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
    void inOrderBSTHelper(TreeNode* root,vector<int>& vec)    {
        if(root){
            inOrderBSTHelper(root->left,vec);
            vec.push_back(root->val);
            inOrderBSTHelper(root->right,vec);
        }
    }
    void sortArrHelper(vector<int>& vec1,vector<int>& vec2,vector<int>& res){
        int idx1 = 0;int idx2 = 0;
        while(idx1 < vec1.size() && idx2 < vec2.size()){
            if(vec1[idx1] <= vec2[idx2])
                res.push_back(vec1[idx1++]);
            else //vec1[idx1] > vec2[idx2]
                res.push_back(vec2[idx2++]);
        }
        if(idx1 == vec1.size()){
            while(idx2 < vec2.size())
                res.push_back(vec2[idx2++]);
        }else{
            //idx2 == vec2.size()
            while(idx1 < vec1.size())
                res.push_back(vec1[idx1++]);
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
    TreeNode *root1 = new TreeNode(2);
    TreeNode *left1 = new TreeNode(1);
    TreeNode *right1 = new TreeNode(4);
    TreeNode *root2 = new TreeNode(1);
    TreeNode *left2 = new TreeNode(0);
    TreeNode *right2 = new TreeNode(3);
//    TreeNode *ll = new TreeNode(1);
//    TreeNode *lr = new TreeNode(7);
//    TreeNode *rl = nullptr;
//    TreeNode *rr = new TreeNode(3);
    root1->left = left1;
    root1->right = right1;
    root2->left = left2;
    root2->right = right2;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
//    right->right = rr;
//    ll->left = new TreeNode(0);
//    rr->right = new TreeNode(4);
    vector<string> rootArr1 = Solution().levelOrderStr(root1);
    printVec(rootArr1);
    //root1 = [2,1,4]
    vector<string> rootArr2 = Solution().levelOrderStr(root2);
    printVec(rootArr2);
    //root2 = [1,0,3]
    vector<int> res = Solution().getAllElements(root1,root2);
    printVec(res);
    //result
    //[0,1,1,2,3,4]
}