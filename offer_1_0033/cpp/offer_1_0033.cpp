//
// Created by wzy on 2022/4/7.
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
    bool verifyPostorder(vector<int>& postorder) {
        //验证BST的后序结果(左右根)
        //可以根据BST性质 根节点小于 右子树 划分出 左子树和右子树 范围
        //而后递归验证 左子树(<)和右子树(>) 是否满足BST性质
        //时间复杂度O(nlogn)
        return verifyPostorder(postorder,0,postorder.size()-1);
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
    bool verifyPostorder(vector<int>& postorder,int start,int end){
        if(start >= end)
            return true;
        int target = postorder[end];
        int i = start;
        while(i < end){
            if(postorder[i] > target)
                break;
            i++;
        }
        if(!isMoreThan(postorder,i,end-1,target) || !isLessThan(postorder,start,i-1,target))
            return false;
        return verifyPostorder(postorder,start,i-1) && verifyPostorder(postorder,i,end-1);
    }
    bool isMoreThan(vector<int>& postorder,int start,int end,int target){
        for(int i = start;i <= end;i++)
            if(postorder[i] <= target)
                return false;
        return true;
    }
    bool isLessThan(vector<int>& postorder,int start,int end,int target){
        for(int i = start;i <= end;i++)
            if(postorder[i] >= target)
                return false;
        return true;
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
    TreeNode *root = new TreeNode(5);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(6);
    TreeNode* ll = new TreeNode(1);
    TreeNode* lr = new TreeNode(3);
//    TreeNode* rl = new TreeNode(7);
//    TreeNode* rr = new TreeNode(9);
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
//    right->left = rl;
//    right->right = rr;
//    lr->left = new TreeNode(3);
//    lr->right = new TreeNode(5);
    vector<string> rootArr = Solution().levelOrderStr(root);
    printVec(rootArr);
    // [5,2,6,1,3,null,null]
    /**
             5
            / \
           2   6
          / \
         1   3
     *
     *
     */
//    vector<int> postorder = {1,6,3,2,5};
    //false
    vector<int> postorder = {1,3,2,6,5};
    //true
    bool res = Solution().verifyPostorder(postorder);
    cout<<boolalpha<<res<<endl;
    //result
    //true
}