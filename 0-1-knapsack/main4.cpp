#include <iostream>
#include <vector>

using namespace std;

class Knapsack01{
public:
    int knapsack01(const vector<int>& w,const vector<int> &v,int C){
        assert(w.size() == v.size());
        int n = w.size();
        if( n == 0)
            return 0;
        vector<int> memo(C+1,-1);
        for(int j = 0;j <= C;j++)
            memo[0][j] = (j>=w[0] ? v[0] : 0);
        for(int i = 1;i <= n;i++)
            for(int j = C;j >= w[i];j--)
                memo[j] = max(memo[j],v[i] + memo[j - w[i]]);
        return memo[C];
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}