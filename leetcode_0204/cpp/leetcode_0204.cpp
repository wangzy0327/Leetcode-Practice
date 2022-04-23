//
// Created by wangzy on 2022/4/23.
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
    int countPrimes(int n) {
        //采用高效实现方案：筛数法
        //如果一个数是素数，ep:2,那么所有2的倍数2x2 = 4,3x2 = 6,4x2 = 8...都不可能是素数
        vector<int> vec(n,1);
        for(int i = 2;i*i < n;i++){
            //只有素数需要判断，合数已经判断过(减少重复判断)
            if(vec[i]){
                for(int j = i*i;j < n;j+=i)
                    vec[j] = 0;
            }
        }
        int count = 0;
        for(int i = 2;i < n;i++)
            if(vec[i])
                count++;
        return count;
    }
};

int main(){
    int n = 10;
//    int n = 0;
    //result
    //0
//    int n = 1;
    //result
    //0
    int res = Solution().countPrimes(n);
    cout<<res<<endl;
    //result
    //4
    //小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7
}