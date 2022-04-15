//
// Created by wzy on 2022/4/15.
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
    int slidingPuzzle(vector<vector<int>>& board) {
        //最少移动次数
        //最小深度    最小旋转 可以联想到BFS来解决
        // target = [[1,2,3],[4,5,0]]
        //设置一个遍历过的 无重复集合 来去重走过的路
        //队列用来存放每次BFS的所有可能结果
        //unorderd_set 需要放入可以散列的元素不能放容器 这里使用string
        string target = "123450";
        string board_s = "";
        for(int i = 0;i < board.size();i++)
            for(int j = 0;j < board[i].size();j++)
                board_s += ((char)('0'+board[i][j]));
        //如果初始就是target board直接返回0
        if(board_s == target)
            return 0;
        move = 0;
        deque<string> dq;
        dq.push_back(board_s);
        unordered_set<string> visited;
        bfs(dq,visited,target);
        return move;
    }
private:
    int move;
    void bfs(deque<string>& dq,unordered_set<string>& visited,string& target){
        while(dq.size()){
            int sz = dq.size();
            for(int i = 0;i < sz;i++){
                string board = dq.front();
                dq.pop_front();
                if(board == target)
                    return ;
                    // else if(visited.count(board))
                    //     continue;
                else{
                    //计算 变换后的谜板
                    auto next_boards = nextVec(board,visited);
                    for(auto next_board:next_boards)
                        dq.push_back(next_board);
                    //添加判断过的board
                    visited.insert(board);
                }
            }
            move += 1;
        }
        //如果队列为空,则无法到达
        move = -1;
    }
    vector<string> nextVec(string board,unordered_set<string>& visited){
        vector<string> res;
        string tmp = board;
        int m = 2;int n = 3;
        int idx_x = 0; int idx_y = 0;
        int i = 0;
        while(i < board.size()){
            if(board[i] == '0')
                break;
            else
                i++;
        }
        idx_x = i/n; idx_y =i%n;
        //0位置上下左右判断
        //向上
        if(idx_x > 0){
            swap(tmp[i],tmp[(idx_x-1)*n+idx_y]);
            if(!visited.count(tmp))
                res.push_back(tmp);
            tmp = board;
        }
        //向下
        if(idx_x < m - 1){
            swap(tmp[i],tmp[(idx_x+1)*n+idx_y]);
            if(!visited.count(tmp))
                res.push_back(tmp);
            tmp = board;
        }
        //向左
        if(idx_y > 0){
            swap(tmp[i],tmp[idx_x*n+idx_y-1]);
            if(!visited.count(tmp))
                res.push_back(tmp);
            tmp = board;
        }
        //向右
        if(idx_y < n - 1){
            swap(tmp[i],tmp[idx_x*n+idx_y+1]);
            if(!visited.count(tmp))
                res.push_back(tmp);
            tmp = board;
        }
        return res;
    }
};

int main(){
    vector<vector<int>> board = {{1,2,3},{4,0,5}};
    //board = [[1,2,3],[4,0,5]]
    //交换 0 和 5 ，1 步完成
    int res = Solution().slidingPuzzle(board);
    cout<<res<<endl;
    //result
    //1
}