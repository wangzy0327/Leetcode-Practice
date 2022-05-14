//
// Created by wangzy on 2022/5/14.
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

struct Node{
    Node* left;
    Node* right;
    int value;
    int sz;  //子树节点数量
    int ans; //方案排列数
    Node(int val):value(val),left(nullptr),right(nullptr),sz(1),ans(0){}
};
class Solution {
public:
    int numOfWays(vector<int>& nums) {
        //思路：对于a0,a1,a2,a3,...,an由于保持相同二叉查找树，a0根节点是固定的
        //左子树即为小于a0的元素按照数组顺序依次插入左子树中
        //右子树即为大于a0的元素按照数组顺序依次插入右子树中
        //设f[ai]表示对ai(对应节点)为根节点的子树，将其包含的所有元素进行重排序得到的相同结果二叉排序树的排列数
        //设以ai 为根节点的子树对应的排列的长度为size(ai)
        //排列首个元素为ai
        //f[al]表示左子树对应排序数, f[ar]表示右子树对应的排序数
        //为了保证二叉查找树结果相同,需要在size(ai)-1个位置中找到size(al)个位置排列左子树，而右子树的位置也就随之而定
        //f[ai] = C(size(ai)-1,size(al))*f[al]*f[ar];
        //极端情况下，当以ai为根节点只有一个元素时, f[ai] = 1;当其某个子树为空时，size(子树)大小为0,f(子树)为1
        //由于求f[ai]需要事先知道 树中元素大小，以及左子树大小，所以首先需要构建树,并记录树中根节点子树sz大小
        //每个子树保留成员变量记录f[ai]的值
        // 求C(n,k) = C(n-1,k-1) + C(n-1,k); C(n,0) = 1;
        // 设 N = 10^9+7 , 乘法满足 a = (N*i)+p; b = (N*j)+q; (a*b)%N = (N*i*N*j+N*i*q+N*j*p+pq)%N = (a%N*b%N) = p*q

        //构建BST
        Node* root = new Node(nums[0]);
        for(int i = 1;i < nums.size();i++)
            insert(root,nums[i]);

        //预先求出C(n,k) ,后面会用到
        vector<vector<int>> dp = vector<vector<int>>(nums.size()+1,vector<int>(nums.size()+1,0));
        dp[0][0] = 1;
        dp[1][0] = 1;
        dp[1][1] = 1;
        for(int i = 2;i <= nums.size();i++){
            //初始化 C(n,0) 为1
            dp[i][0] = 1;
            dp[i][i] = 1;
            for(int j = 1;j < i;j++){
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%mod;
            }

        }
//        printVecArr(dp);


        //dfs 递归求子树排列
        dfs(root,dp);
        return root->ans-1;

    }
private:
    static constexpr int mod = 1000000007;
    void insert(Node* root,int val){
        Node* cur = root;
        while(true){
            cur->sz++;
            if(val < cur->value){
                if(!cur->left){
                    cur->left = new Node(val);
                    return ;
                }
                else
                    cur = cur->left;
            }else{
                //val > cur->val
                if(!cur->right){
                    cur->right = new Node(val);
                    return ;
                }
                else
                    cur = cur->right;
            }
        }
    }
    void dfs(Node* root,vector<vector<int>>& dp){
        //C(size(ai)-1,size(al))*f[al]*f[ar]
        if(root){
            int sz = root->sz;
            if(root->left)
                dfs(root->left,dp);
            if(root->right)
                dfs(root->right,dp);
            int fl = (root->left)?root->left->ans:1;
            int fr = (root->right)?root->right->ans:1;
            int lsz = (root->left)?root->left->sz:0;
            root->ans = (long long)dp[sz-1][lsz]%mod*fl%mod*fr%mod;
            return ;
        }
    }
};

int main(){
//    vector<int> nums = {3,4,5,1,2};
    //result
    //5
    /*下面 5 个数组会得到相同的 BST：
    [3,1,2,4,5]
    [3,1,4,2,5]
    [3,1,4,5,2]
    [3,4,1,2,5]
    [3,4,1,5,2]
    * */
//    vector<int> nums = {1,2,3};
    //result
    //0
    vector<int> nums = {9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18};
    //result
    //216212978
    int res = Solution().numOfWays(nums);
    cout<<res<<endl;
}