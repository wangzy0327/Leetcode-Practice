//
// Created by wzy on 2022/4/6.
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
    int kthLargest(TreeNode* root, int k) {
        //求最大的k个节点 采用先右根左的顺序 保证从大到小
        int target = 0;
        TreeNode* targetNode = findKthLarge(root,k,target);
        if(!targetNode)
            return INT_MIN;
        return targetNode->val;
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
    TreeNode* findKthLarge(TreeNode* root,int k,int& target){
        if(root){
            TreeNode* rNode = findKthLarge(root->right,k,target);
            if(rNode)
                return rNode;
            target++;
            if(k == target)
                return root;
            TreeNode* lNode = findKthLarge(root->left,k,target);
            if(lNode)
                return lNode;
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
    TreeNode *root = new TreeNode(3);
    TreeNode *left = new TreeNode(1);
    TreeNode *right = new TreeNode(4);
//    TreeNode* ll = nullptr;
    TreeNode* lr = new TreeNode(2);
//    TreeNode* rl = new TreeNode(3);
//    TreeNode* rr = new TreeNode(6);
    root->left = left;
    root->right = right;
//    left->left = ll;
    left->right = lr;
//    right->left = rl;
//    right->right = rr;
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    //root = [3,1,4,null,2], k = 1
    int k = 1;
    int res = Solution().kthLargest(root,k);
    cout<<res<<endl;
    //result
    //4
}