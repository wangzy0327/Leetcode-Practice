//
// Created by wzy on 2022/4/8.
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
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        //采用先序遍历 在[low,high]区间内 累加sum
        rangeSumHelper(root,low,high,sum);
        return sum;
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
    void rangeSumHelper(TreeNode* root,int low,int high,int& sum){
        if(root){
            if(root->val >= low && root->val <= high)
                sum += root->val;
            //采用先序遍历如果当前节点的值小于low,那左子树不用遍历
            //右子树同理
            if(root->val > low)
                rangeSumHelper(root->left,low,high,sum);
            if(root->val < high)
                rangeSumHelper(root->right,low,high,sum);
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
    TreeNode *root = new TreeNode(10);
    TreeNode *left = new TreeNode(5);
    TreeNode *right = new TreeNode(15);
    TreeNode *ll = new TreeNode(3);
    TreeNode *lr = new TreeNode(7);
    TreeNode *rl = nullptr;
    TreeNode *rr = new TreeNode(18);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
//    ll->left = new TreeNode(0);
//    lr->right = new TreeNode(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
//    root = [10,5,15,3,7,null,18], low = 7, high = 15
    int low = 7;
    int high = 15;
    int res = Solution().rangeSumBST(root,low,high);
    cout<<res<<endl;
    //result
    //32
}