//
// Created by wzy on 2022/4/12.
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
    int countNodes(TreeNode* root) {
        //思路：由于是完全二叉树，所以最左边节点一定是最底层的
        // 最底层包含的节点数最少为 1，最多为 2^h
        //重点是 如何找到完全二叉树最后一层节点对应是哪一个，这里采用二分搜索来找到对应的元素
        /**
        如何判断第 k 个节点是否存在呢？如果第 k 个节点位于第 h 层，则 k 的二进制表示包含 h+1 位，其中最高位是 1，其余各位从高到低表示从根节点到第 k 个节点的路径，0 表示移动到左子节点，1 表示移动到右子节点。通过位运算得到第 k 个节点对应的路径，判断该路径对应的节点是否存在，即可判断第 k 个节点是否存在
        ep:12 = 1100  (根节点为1，向右为1，向左为0)
               1
           2        3
       4    5     6    7
     8  9 10 11 12 13 14 15
        */
        if(!root)
            return 0;
        int low = 0;
        int h = 0;
        TreeNode* cur = root;
        while(cur->left){
            cur = cur->left;
            h++;
        }
        //这里索引从1开始，表示第几个元素
        low = 1<<h;
        int high = (1<<(h+1));
        //二分搜索 [low,high) 跳出循环条件 low == high
        //向右偏移
        while(low < high){
            int mid = low + (high - low)/2;
            if(exist(root,h,mid)){
                low = mid + 1;
            }else{
                high = mid;
            }
        }
        return low - 1;
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
    bool exist(TreeNode* root,int level,int num){
        TreeNode* cur = root;
        //注意因为高位的1即是root根节点，所以从首位的下一位判断，这里二进制位数-1
        //防止只有一层的情况下，level为0, level-1为负数
        int bits = (level-1 < 0)?0:(1<<(level-1));
        while(cur && bits){
            //首位不为0 向右子节点走，首位为0 向左子节点走
            int x = (num & bits);
            if(x != 0){
                cur = cur->right;
            }else{
                cur = cur->left;
            }
            //向右移位
            bits = bits>>1;
        }
        return cur;
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
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(3);
    TreeNode *ll = new TreeNode(4);
    TreeNode *lr = new TreeNode(5);
    TreeNode *rl = new TreeNode(6);
    TreeNode *rr = nullptr;
    root->left = left;
    root->right = right;
    left->left = ll;
    left->right = lr;
    right->left = rl;
    right->right = rr;
    vector<string> rootArr1 = Solution().levelOrderStr(root);
    printVec(rootArr1);
    //root = [1,2,3,4,5,6,null]
    int res = Solution().countNodes(root);
    cout<<res<<endl;
    //result
    //6
}