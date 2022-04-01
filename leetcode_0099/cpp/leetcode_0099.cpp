//
// Created by wzy on 2022/3/30.
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
    void recoverTree(TreeNode* root) {
        //考察中序遍历
        //一个正常的BST会是递增序列，如果错误的交换两个节点，则会出现递减
        //这里的递减分为两个情况，一个是交换的是相邻元素（只会有一个递减）
        //ep:1,2,3,4,5,6,7 -> 1,3,2,4,5,6,7
        //交换的是非相邻元素(两个递减)
        //ep:1,2,3,4,5,6,7 -> 1,6,3,4,5,2,7
        //可通过这个找到两个交换的元素
        //然后重新遍历树，对两个元素的值进行 交换
        //错误交换的值
//        vector<int> vec;
//        inorder(vec,root);
//        pair<int,int> eles = findErrorElements(root,vec);
        //用来标识是否是第一次遇到递减
        int flag = -1;
        TreeNode* pre = nullptr;
        pair<int,int> eles = make_pair(-1,-1);
        //使用O(1)空间复杂度
        inorder(pre,root,flag,eles);
        recover(root,eles);
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

    void traversePreTree(string& s,TreeNode* root){
        if(root){
            s+=(to_string(root->val)+",");
            traversePreTree(s,root->left);
            traversePreTree(s,root->right);
        }
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


private:
    void inorder(vector<int>& vec,TreeNode* root){
        if(root){
            inorder(vec,root->left);
            vec.push_back(root->val);
            inorder(vec,root->right);
        }
    }
    void inorder(TreeNode*& pre,TreeNode* root,int& flag,pair<int,int>& eles){
        if(root){
            inorder(pre,root->left,flag,eles);
            if(pre != nullptr && pre->val > root->val && flag == -1){
                eles.first = pre->val;
                eles.second = root->val;
                flag = 0;
            }else if(pre != nullptr && pre->val > root->val && flag != -1){
                eles.second = root->val;
            }
            pre = root;
            inorder(pre,root->right,flag,eles);
        }
    }
    pair<int,int> findErrorElements(TreeNode* root,vector<int>& vec){
        int swap_idx1 = -1;
        int swap_idx2 = -1;
        for(int i = 0;i < vec.size()-1;i++){
            if(vec[i]>vec[i+1] && swap_idx1 == -1){
                swap_idx1 = i;
                swap_idx2 = i+1;
            }
            else if(vec[i]>vec[i+1] && swap_idx1 != -1)
                swap_idx2 = i+1;
        }
        return make_pair(vec[swap_idx1],vec[swap_idx2]);
    }
    void recover(TreeNode* root,pair<int,int> p){
        if(root){
            recover(root->left,p);
            if(root->val == p.first)
                root->val = p.second;
            else if(root->val == p.second)
                root->val = p.first;
            recover(root->right,p);
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
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(3);
    TreeNode* right = nullptr;
    TreeNode* ll = nullptr;
    TreeNode* lr = new TreeNode(2);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    vector<string> vec = Solution().printTree(root);
    printVec(vec);
//    root = [1,3,null,null,2]
    Solution().recoverTree(root);
    vector<string> vecAno = Solution().printTree(root);
    printVec(vecAno);
    //result
    //[3,1,null,null,2]
    return 0;
}