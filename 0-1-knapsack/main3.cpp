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
        vector<vector<int>> memo(2,vector<int>(C+1,-1));
        for(int j = 0;j <= C;j++)
            memo[0][j] = (j>=w[0] ? v[0] : 0);
        for(int i = 1;i <= n;i++)
            for(int j = 0;j <= C;j++){
                memo[i%2][j] = memo[(i - 1)%2][j];
                if(j >= w[i])
                    memo[i%2][j] = max(memo[i%2][j],v[i] + memo[(i - 1)%2][j - w[i]]);
            }
        return memo[(n-1)%2][C];
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}