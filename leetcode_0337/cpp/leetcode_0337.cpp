//
// Created by wangzy on 2022/5/18.
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
#include <cstring>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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

class Solution {
public:
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
    int rob(TreeNode* root) {
        //错误！！！初始错误思路：由于是树状结构，可知达到最大金额必定是隔层累加 愚蠢的进行层次遍历，隔行求和
        //反例 下图中最高金额为 3+4 ，并不是隔行取
        //    2
        //   / \
        //  1   3
        //   \
        //   4
        //
        //正确思路：由于父子不能同时取，所以每个节点有两种状态，偷或者不偷
        //1.当偷当前节点时，那么两个孩子节点就不能偷了
        //2.当不偷当前节点时，获取两个孩子子树所能达到的最大金额就行
        //用数组来表示节点选择哪种状态，0表示不偷，1表示偷
        //任何一个节点能偷到的最大钱的状态可以定义为
        //1.当前节点选择不偷：当前节点能偷到的最大钱数 = 左孩子能偷到的钱+右孩子能偷到的钱
        //2.当前节点选择偷：当前节点能偷到的最大钱数 = 左孩子选择自己不偷时能得到的钱 + 右孩子选择不偷时能得到的钱 + 当前节点的钱数
        // root[0] = max(root.left[0],root.left[1]) + max(root.right[0],root.right[1])
        // root[1] = root.val + root.left[0] + root.right[0]
        // return max(root[0],root[1])
        //初始状态 只有一个节点 root[0] = 0;root[1] = root.val;
        pair<int,int> res = robHelper(root);
        return max(res.first,res.second);
    }
    int rob2(TreeNode* root) {
        //思路：采用 记忆化搜索+重复子结构
        //采用unordered_map<TreeNode*,int>来记录 某个节点所能达到的最高金额
        //如果TreeNode* 在记录中直接返回，不在的话求解
        //求解过程，root节点的最高金额 分为 取当前节点 和 不取当前节点 两种情况
        // dp(表示取当前节点)

        return dp(root);
    }
private:
    unordered_map<TreeNode*,int> record;
    int dp(TreeNode* root){
        if(root){
            if(record.count(root))
                return record[root];
            //取当前节点
            int val = root->val;
            //左子树最大金额
            int lVal = dp(root->left);
            //右子树最大金额
            int rVal = dp(root->right);
            //当前节点子树最大金额为 max(val + sum(dp(root->left->left),dp(root->left->right)) +dp(root->right),lVal+rVal)
            //左子树下不包含root->left的最大金额
            int llVal = (!root->left)?0:(dp(root->left->left)+dp(root->left->right));
            //右子树下不包含root->right的最大金额
            int rrVal = (!root->right)?0:(dp(root->right->left)+dp(root->right->right));
            int res = max(val+llVal+rrVal,lVal+rVal);
            record[root] = res;
            return res;
        }
        return 0;
    }
    pair<int,int> robHelper(TreeNode* root){
        pair<int,int> status = {0,0};
        pair<int,int> left_status = {0,0};
        pair<int,int> right_status = {0,0};
        if(root->left)
            left_status = robHelper(root->left);
        if(root->right)
            right_status = robHelper(root->right);
        status.first = max(left_status.first,left_status.second) + max(right_status.first,right_status.second);
        status.second = root->val + left_status.first + right_status.first;
        return status;
    }
};

int main(){
    TreeNode* root = new TreeNode(2);
    TreeNode* left = new TreeNode(1);
    TreeNode* right = new TreeNode(3);
    TreeNode* ll = nullptr;
    TreeNode* lr = new TreeNode(4);
    //[2,1,3,null,4]
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    vector<string> treeStr = Solution().printTree(root);
    printVec(treeStr);
    int res = Solution().rob(root);
    cout<<res<<endl;
    //result
    //7 = 3 + 4
}
