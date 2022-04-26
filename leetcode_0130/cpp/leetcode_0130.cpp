//
// Created by wzy on 2022/4/26.
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
    void solve(vector<vector<char>>& board) {
        //思路：由于边界上的'O'不会被围绕，可以通过边界上的'O'为起点进行dfs遍历
        //将连接到的节点字符改为'#',剩下所有的'O'都是被围绕的，设置为'X'即可
        //然后再将'#'设置为'O'即可

        //从边界寻找'O'
        int m = board.size();int n = board[0].size();
        //首行边界
        for(int i = 0;i < n;i++)
            dfs(board,0,i);
        //首列
        for(int i = 0;i < m;i++)
            dfs(board,i,0);
        //尾行
        for(int i = 0;i < n;i++)
            dfs(board,m-1,i);
        //尾列
        for(int i = 0;i < m;i++)
            dfs(board,i,n-1);
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(board[i][j] == 'O')
                    board[i][j] = 'X';
                else if(board[i][j] == '#')
                    board[i][j] = 'O';
            }
        }
    }
private:
    void dfs(vector<vector<char>>& board,int i,int j)    {
        if(i >= 0 && i < board.size() && j >= 0 && j < board[0].size() && board[i][j] == 'O'){
            board[i][j] = '#';
            //上
            dfs(board,i-1,j);
            //下
            dfs(board,i+1,j);
            //左
            dfs(board,i,j-1);
            //右
            dfs(board,i,j+1);
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

int main(){
    vector<vector<char>> board = {
            {'X','X','X','X'},
            {'X','O','O','X'},
            {'X','X','O','X'},
            {'X','O','X','X'}
    };
    printVecArr(board);
    Solution().solve(board);
    cout<<"------------------------------------------------"<<endl;
    printVecArr(board);
    /*
     * [[X,X,X,X],[X,X,X,X],[X,X,X,X],[X,O,X,X]]
     * */
}