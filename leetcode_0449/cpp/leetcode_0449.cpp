//
// Created by wangzy on 2022/3/31.
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


class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)
            return "#";
        return to_string(root->val)+" "+serialize(root->left)+" "+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return rebuild(ss);
    }


    TreeNode* rebuild(stringstream& ss){
        string tmp;
        ss>>tmp;
        if(tmp == "#")
            return nullptr;
        TreeNode* node = new TreeNode(stoi(tmp));
        node->left = rebuild(ss);
        node->right = rebuild(ss);
        return node;
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

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

int main() {
    TreeNode* root = new TreeNode(2);
    TreeNode* left = new TreeNode(1);
    TreeNode* right = new TreeNode(3);
//    TreeNode* ll = new TreeNode(1);
//    TreeNode* lr = new TreeNode(3);
//    TreeNode* rl = new TreeNode(6);
//    TreeNode* rr = new TreeNode(9);
//    [4,2,1,3,7,6,9]
    root->left = left;
    root->right = right;
//    left->left = ll;
//    left->right = lr;
//    right->left = rl;
//    right->right = rr;
    Codec().printTree(root);
    //[2,1,3]
    string s = Codec().serialize(root);
    TreeNode* ano = Codec().deserialize(s);
    Codec().printTree(ano);
    //result
    //[2,1,3]
}