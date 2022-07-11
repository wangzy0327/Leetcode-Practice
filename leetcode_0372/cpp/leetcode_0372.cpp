//
// Created by wzy on 2022/7/11.
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

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        // 先验知识 (a*b) mod m = (a mod m)*(b mod m) mod m
        // a^(m+n) = a^m * a^n % mod
        // 快速幂： 3*9 = ((3*3)^2)^2 * 3  循环次数为log n (n为指数)
        //解题思路：分治 ep: 99^(2345) = (99^(234))^10 * 99^5
        // 99^(k) ( 0 < k < 10) 可以采用分治思想求解
        return dfs(a,b,b.size());
    }
private:
    int mod = 1337;
    //u为指数的索引
    int dfs(int a,vector<int>& b,int u){
        if(u == 0)
            return 1;
        return quickPow(dfs(a,b,u-1),10) * quickPow(a,b[u-1]) % mod;
    }
    // 0 < b < 10 快速幂计算
    int quickPow(int a,int b){
        int res = 1;
        a %= mod;
        //如果幂为单数
        while(b != 0){
            if(b%2 == 1)
                res = res*a % mod;
            a = a * a % mod;
            b /= 2;
        }
        return res;
    }
};

int main(){
    int a = 2147483647;
    vector<int> b = {2,0,0};
//    int a = 2;
//    vector<int> b = {1,0};
    //result 1024
    int res = Solution().superPow(a,b);
    cout<<res<<endl;
    //result 1198
}