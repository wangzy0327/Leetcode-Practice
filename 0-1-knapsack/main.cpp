#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
 * 0-1背包问题子问题是：第i个物品放或者不放
 * F(i,c) = max(F(i-1,c),v(i) + F(i-1,c - w(i)))
 */
class Knapsack01{
private:
    vector<vector<int>> memo;
    //用[0...index]的物品，填充容积为c的背包的最大价值
    int bestValue(const vector<int>& w,const vector<int> &v,int index,int c){
        if(index < 0 || c <= 0)
            return 0;
        if(memo[index][c] != -1)
            return memo[index][c];
        int res = bestValue(w,v,index - 1,c);
        if(w[index] <= c)
            res = max(res,v[index] + bestValue(w,v,index - 1,c - w[index]));
        memo[index][c] = res;
        return res;
    }
public:
    int knapsack01(const vector<int>& w,const vector<int> &v,int C){
        assert(w.size() == v.size());
        int n = w.size();
        memo = std::vector<vector<int>>(n,vector<int>(C+1,-1));
        return bestValue(w,v,n-1,C);
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}