//
// Created by wzy on 2022/4/19.
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


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        //思路:使用字符串数组来表示每一行 或者 int数组来表示每一行皇后的位置
        //回溯每一行，对每一行的每一列摆放进行验证
        vector<string> vec = vector<string>(n,string(n,'.'));
        vector<vector<string>> res;
        dfs(res,vec,n,0);
        return res;
    }
private:
    void dfs(vector<vector<string>>& res,vector<string>& vec,int n,int row){
        if(row == n){
            //说明前row行进行了皇后摆放的插入
            res.push_back(vec);
            return ;
        }
        for(int i = 0;i < n;i++){
            if(valid(vec,n,row,i)){
                vec[row][i] = 'Q';
                dfs(res,vec,n,row+1);
                vec[row][i] = '.';
            }
        }
    }
    bool valid(vector<string>& vec,int n,int row,int idx){
        //判断是否在同一列
        for(int i = 0;i < row;i++)
            //说明有在同一列
            if(vec[i][idx] == 'Q')
                return false;
        //判断是否在左上方
        // row - idx = i - x
        for(int i = 0;i < row;i++){
            int j = i - row + idx;
            if( j >= 0 && j < n && vec[i][j] == 'Q')
                return false;
        }
        //判断是否在右上方
        // i - (n-x) = row - (n-idx)
        for(int i = 0;i < row;i++){
            int j = row+idx-i;
            if( j >= 0 && j < n && vec[i][j] == 'Q')
                return false;
        }
        return true;
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

int main(){
    int n = 4;
    auto res = Solution().solveNQueens(n);
    printVecArr(res);
    //result
    //[[.Q..,...Q,Q...,..Q.],[..Q.,Q...,...Q,.Q..]]
}