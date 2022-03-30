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
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> s;
        return findHelper(root,k,s);
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
private:
    bool findHelper(TreeNode* root,int k,unordered_set<int>& s) {
        if(root){
            if(s.count(k-root->val))
                return true;
            s.insert(root->val);
            return findHelper(root->left,k,s) || findHelper(root->right,k,s);
        }
        return false;
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
    TreeNode* left = new TreeNode(3);
    TreeNode* right = new TreeNode(6);
    TreeNode* ll = new TreeNode(2);
    TreeNode* lr = new TreeNode(4);
    TreeNode* rl = nullptr;
    TreeNode* rr = new TreeNode(7);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    Solution().printTree(root);
//    root = [5,3,6,2,4,null,7], k = 9
    int k = 9;
    bool res = Solution().findTarget(root,k);
    cout<<boolalpha<<res<<endl;
    //result
    //true
    return 0;
}