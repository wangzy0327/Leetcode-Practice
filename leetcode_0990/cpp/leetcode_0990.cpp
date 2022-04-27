//
// Created by wzy on 2022/4/27.
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
    bool equationsPossible(vector<string>& equations) {
        //思路：通过并查集 先将有连接关系的 变量放入并查集中
        //而后判断不连接的 变量如果之前判断是连接的，则返回false
        // 否则 返回true

        //因为都是小写字母所以并查集数量设置为26
        parents = vector<int>(26);
        for(int i = 0;i < parents.size();i++)
            parents[i] = i;
        sz = vector<int>(26,1);
        //默认没有初始化时 parents[p] = p
        for(auto ele:equations){
            char op = ele[1];
            if(op == '='){
                int p = ele[0] - 'a';
                int q = ele[3] - 'a';
                //设置合并连接
                unionElements(p,q);
            }
        }
        for(auto ele:equations){
            char op = ele[1];
            if(op == '!'){
                int p = ele[0] - 'a';
                int q = ele[3] - 'a';
                if(isConnected(p,q))
                    return false;
            }
        }
        return true;
    }
private:
    int find(int p){
        if(p != parents[p])
            parents[p] = find(parents[p]);
        return parents[p];
    }
    bool isConnected(int p,int q){
        return find(p) == find(q);
    }
    void unionElements(int p,int q){
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == qRoot)
            return ;
        if(sz[pRoot] >= sz[qRoot]){
            //数量小的指向数量多的
            parents[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }else{
            //sz[pRoot] < sz[qRoot]
            parents[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        }
    }
    vector<int> parents;
    vector<int> sz;
};

int main(){
    vector<string> vec = {
            "a==b",
            "a!=b",
//            "c==c",
//            "b==d",
//            "x!=z"
    };
    bool res = Solution().equationsPossible(vec);
    cout<<boolalpha<<res<<endl;
    //result
    //false

    //result
    //true

}
