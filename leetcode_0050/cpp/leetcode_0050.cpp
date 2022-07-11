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
    double myPow(double x, int n) {
        //思路：快速幂计算
        // m^(k) = (m^2)^(k/2) {k%2 == 0} | (m)*(m^2)^(k/2) {k%2 == 1}
        // 设M = (m^2),递归求解 M^(k/2)的解，直到指数为0
        double ans = 1.0;
        int flag = 0;
        if(n < 0){
            //防止出现越界 -2147483648 -> 2147483648
            ans = x;
            n++;
            n = -n;
            flag = 1;
        }
        while(n != 0){
            if((n&1) != 0)
                ans = ans * x;
            x = x * x;
            n >>= 1;
        }
        return (flag==1)?1/ans:ans;
    }
};

int main(){
    double x = 2.0;
    int n = 10;
    //result 1024
//    double x = 2.0;
//    int n = -2;
    //result 0.25
//    double x = 1.0;
//    int n = -2147483648;
    //result 1.0
    double res = Solution().myPow(x,n);
    cout<<res<<endl;
    //1024
}