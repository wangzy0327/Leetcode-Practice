//
// Created by wzy on 2022/4/1.
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        //1.找到指定节点(判断指定节点有无孩子) 若无孩子则直接返回
        //2.如果只有左孩子，返回左孩子，如果只有有孩子返回右孩子
        //3.如果左右两个孩子都有，则有两种结果
        //1).返回右节点，并将左子树放到右子树最小节点的左边
        //2).返回左节点，并将右子树放到左子树最大节点的右边
        //这里采用2)
        TreeNode* node = root;
        if(!root)
            return nullptr;
        if(root->val > key){
            //在左子树上寻找
            root->left = deleteNode(root->left,key);
            return root;
        }else if(root->val < key){
            //在右子树上寻找
            root->right = deleteNode(root->right,key);
            return root;
        }else{
            //root->val == key
            //左子树为空
            if(!root->left){
                TreeNode* right = root->right;
                root = nullptr;
                return right;
            }else if(!root->right){
                //右子树为空
                TreeNode* left = root->left;
                root = nullptr;
                return left;
            }else{
                //左右子树都不为空  这里返回右子树
                TreeNode* right = root->right;
                TreeNode* left = root->left;
                //右子树最小节点
                TreeNode* rMin = minNode(right);
                rMin->left = left;
                root = nullptr;
                return right;
            }
        }
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
    TreeNode* minNode(TreeNode* root){
        TreeNode* node = root;
        while(node->left)
            node = node->left;
        return node;
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
    vector<string> vec = Solution().levelOrderStr(root);
//    root = [5,3,6,2,4,null,7], key = 3
    printVec(vec);
    int key = 3;
    TreeNode* ano = Solution().deleteNode(root,key);
    vector<string> vecAno = Solution().levelOrderStr(ano);
    printVec(vecAno);
    //result
    //[5,4,6,2,null,null,7]

}