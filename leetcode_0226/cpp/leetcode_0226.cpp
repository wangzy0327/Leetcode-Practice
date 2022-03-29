//
// Created by wzy on 2022/3/29.
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
    TreeNode* invertTree(TreeNode* root) {
        if(root){
            TreeNode* left = root->left;
            TreeNode* right = root->right;
            root->left = invertTree(right);
            root->right = invertTree(left);
        }
        return root;
    }
    void traversePreTree(string& s,TreeNode* root){
        if(root){
            s+=(to_string(root->val)+",");
            traversePreTree(s,root->left);
            traversePreTree(s,root->right);
        }
    }
    void printTree(TreeNode* root){
        string s;
        traversePreTree(s,root);
        cout<<"[";
        s = s.substr(0,s.length()-1);
        cout<<s;
        cout<<"]"<<endl;
    }
    void deleteTree(TreeNode* root){
        if(root){
            deleteTree(root->left);
            deleteTree(root->right);
            root = nullptr;
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

int main() {
    TreeNode* root = new TreeNode(4);
    TreeNode* left = new TreeNode(2);
    TreeNode* right = new TreeNode(7);
    TreeNode* ll = new TreeNode(1);
    TreeNode* lr = new TreeNode(3);
    TreeNode* rl = new TreeNode(6);
    TreeNode* rr = new TreeNode(9);
//    [4,2,1,3,7,6,9]
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    Solution().printTree(root);
    root = Solution().invertTree(root);
    Solution().printTree(root);
    //result
    //[4,7,9,6,2,3,1]
    Solution().deleteTree(root);
    return 0;
}