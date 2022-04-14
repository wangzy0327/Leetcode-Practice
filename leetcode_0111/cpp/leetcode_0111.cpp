//
// Created by wzy on 2022/4/14.
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
    int minDepth(TreeNode* root) {
        //这里找寻左右子树中最小的深度返回,注意 如果 左右子树有一个为null,则返回另一个子树深度+1
        //两种方式求解，一种递归 DFS
        //一种 BFS(更快) BFS 对求解最短路径和最小深度有优势
        if(!root)
            return 0;
        deque<TreeNode*> dq;
        depth = 0;
        dq.push_back(root);
        int res = bfs(dq);
        return res;
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
    int depth;
    int bfs(deque<TreeNode*> dq){
        while(dq.size()){
            int sz = dq.size();
            for(int i = 0;i < sz;i++){
                TreeNode* cur = dq.front();
                dq.pop_front();
                //如果左右子树都为null,说明遇到叶子节点 返回深度 + 1
                if(!cur->left && !cur->right)
                    return depth + 1;
                if(cur->left)
                    dq.push_back(cur->left);
                if(cur->right)
                    dq.push_back(cur->right);
            }
            //遍历完当前层，深度+1
            depth += 1;
        }
        return depth;
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
    TreeNode *root = new TreeNode(2);
//    TreeNode *left = nullptr;
    TreeNode *right = new TreeNode(3);
//    TreeNode *ll = nullptr;
//    TreeNode *lr = nullptr;
    TreeNode *rl = nullptr;
    TreeNode *rr = new TreeNode(4);
//    root->left = left;
    root->right = right;
//    left->left = ll;
//    left->right = lr;
    right->left = rl;
    right->right = rr;
    TreeNode* rrr = new TreeNode(5);
    rr->right = rrr;
    rrr->right = new TreeNode(6);
    vector<string> rootArr1 = Solution().levelOrderStr(root);
    printVec(rootArr1);
    //root = [2,null,3,null,4,null,5,null,6]
    int depth = Solution().minDepth(root);
    cout<<depth<<endl;
    //result
    //5
}