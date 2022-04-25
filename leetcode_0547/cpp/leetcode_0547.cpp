//
// Created by wzy on 2022/4/25.
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
    int findCircleNum(vector<vector<int>>& isConnected) {
        //思路：采用并查集（主要解决连接和合并问题）
        //进行合并连接操作后，对每个城市进行根节点判断去重(无序集合)
        int n = isConnected.size();
        parents = vector<int>(n,0);
        sz = vector<int>(n,1);
        //初始化 并查集
        for(int i = 0;i < n;i++)
            parents[i] = i;
        for(int i = 0;i < n;i++){
            //注意这里由于连通性 只需要判断一半即可
            for(int j = i+1;j < n;j++){
                if(isConnected[i][j] == 1){
                    unionElements(i,j);
                }
            }
        }
        unordered_set<int> res;
        for(int i = 0;i < n;i++)
            res.insert(find(i));
        return res.size();
    }
private:
    vector<int> parents;
    //根节点的孩子数量
    vector<int> sz;//采用大小压缩路径
    int find(int p){
        //递归压缩路径
        if(p != parents[p])
            parents[p] = find(parents[p]);
        return parents[p];
    }
    //合并两个元素
    void unionElements(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ)
            return ;
        int szP = sz[rootP];
        int szQ = sz[rootQ];
        //路径压缩
        if(szP >= szQ){
            parents[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
        }else{
            parents[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        }
    }
};

int main(){
    vector<vector<int>> isConnected = {
            {1,1,0},
            {1,1,0},
            {0,0,1}
    };
    int res = Solution().findCircleNum(isConnected);
    cout<<res<<endl;
    //result
    //2
}