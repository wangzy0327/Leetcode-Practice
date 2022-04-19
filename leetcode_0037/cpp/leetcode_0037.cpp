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
    void solveSudoku(vector<vector<char>>& board) {
        //思路：回溯
        //每个进入到每个需要填充的位置是需要传入i,j来进行定位
        //如果dfs找到了返回true,不需要返回重置，否则如果为false，重置接着找下一个满足的
        dfs(board,0,0);
        return ;
    }
private:
    bool dfs(vector<vector<char>>& board,int idx_x,int idx_y){
        //如果索引超出范围则返回
        if(idx_x >= board.size() || idx_y >= board[idx_x].size())
            return true;
        pair<int,int> p = nextPos(board,idx_x,idx_y);
        //如果当前的位置为空格，则进行填充 并对下一个空格位置进行查找
        if(board[idx_x][idx_y] == '.'){
            for(int i = 1;i <= 9;i++){
                char c = (char)('0'+i);
                if(valid(board,idx_x,idx_y,c)){
                    board[idx_x][idx_y] = c;
                    if(!dfs(board,p.first,p.second))
                        board[idx_x][idx_y] = '.';
                }
            }
            //尝试过所有1-9都不符合 返回 false
            if(board[idx_x][idx_y] == '.')
                return false;
        }else{
            return dfs(board,p.first,p.second);
        }
        return true;
    }
    pair<int,int> nextPos(vector<vector<char>>& board,int idx_x,int idx_y){
        int i = idx_x;int j = idx_y + 1;
        for(;i < board.size();i++){
            for(;j < board[i].size();j++){
                if(board[i][j] == '.')
                    return make_pair(i,j);
            }
            //注意换行寻找下一个空格索引 需要将 列索引置为0
            j = 0;
        }
        return make_pair(i,j);
    }
    bool valid(vector<vector<char>>& board,int idx_x,int idx_y,char ch){
        //判断行
        for(int i = 0;i < board.size();i++)
            if(board[i][idx_y] == ch)
                return false;
        //判断列
        for(int i = 0;i < board[idx_x].size();i++)
            if(board[idx_x][i] == ch)
                return false;
        //判断宫
        //求索引所在的宫格左上角 坐标
        int left_idx = (idx_x/3)*3;
        int left_idy = (idx_y/3)*3;
        for(int i = left_idx;i < left_idx + 3;i++){
            for(int j = left_idy;j < left_idy + 3;j++){
                if(board[i][j] == ch)
                    return false;
            }
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
    vector<vector<char>> board = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
    };
    Solution().solveSudoku(board);
    printVecArr(board);
    //result
    /*
     *
     [[5,3,4,6,7,8,9,1,2],
     [6,7,2,1,9,5,3,4,8],
     [1,9,8,3,4,2,5,6,7],
     [8,5,9,7,6,1,4,2,3],
     [4,2,6,8,5,3,7,9,1],
     [7,1,3,9,2,4,8,5,6],
     [9,6,1,5,3,7,2,8,4],
     [2,8,7,4,1,9,6,3,5],
     [3,4,5,2,8,6,1,7,9]]
     *
     */
}