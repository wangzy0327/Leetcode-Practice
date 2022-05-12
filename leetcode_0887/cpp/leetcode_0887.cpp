//
// Created by wzy on 2022/5/12.
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

class Solution {
public:
    //时间复杂度O(k*n*n) Time of Exceeded
    int superEggDrop(int k, int n) {
        //思路：动态规划
        //极端情况：如果只有一个蛋，则从一层开始逐层向上，最多就是测的楼层高度
        //极端情况：如果有无数个蛋，则采用二分法进行测量楼层高度
        //example:假设有100层楼，两个蛋，可以每10层扔一个，可知最多试19次
        // 10,20,30,40,50,60,70,80,90,100  (第一颗蛋用来缩小范围，第二颗蛋用来从碎了的下一个10倍数往上依次寻找)
        //假如第一颗扔在10层没破，然后去20层扔，破了，剩下那一颗从11层开始逐层向上(该种情况下最多扔 2+9 = 11次) 最差情况下就是99层，需要扔19次
        //example:假设有100层，两个蛋，为了平摊复杂度，可以选择按照第一颗逐层减少
        // n,n-1,n-2,...,1 (n+1)*n/2 = 100 n ~= 14
        //14,27,39,50,60,69,77,84,90,95,99,100
        //假设第一次扔在14层没破，去27层扔，破了，剩下从15层开始逐层向上（该种情况下最多扔 2+12 = 14）因为把复杂度平均了，所以任何情况下最差都是14次
        //题意转化为
        //N 个楼层，有 K 个蛋，求最少要扔 T 次，才能保证当 F 无论是 0 <= F <= N 中哪个值，都能测试出来
        //假设从x层开始扔鸡蛋，如果鸡蛋碎了，则应该用k-1个蛋从1到x-1层寻找;如果鸡蛋没碎，则应该用k个蛋从剩下n-x层开始寻找
        //由于要保证在最不利的情况下也能求解出问题 ,则应该选择两种情况中的最大值
        // M(x) = max(dp(k-1,x-1),dp(k,n-x))+1 表示从x层楼往下扔得出f需要的操作数
        //由于要求出最小的操作数 dp(k,n) = min{M(x)}
        //dp初始状态 dp(1,x) = x, dp(k,1) = 1

        vector<vector<int>> dp = vector<vector<int>>(k + 1,vector<int>(n + 1,n));
        //k个蛋，n层楼
        for(int i = 0;i <= k;i++)
            dp[i][0] = 0;
        //只有一个蛋
        for(int i = 1;i <= n;i++)
            dp[1][i] = i;
        //楼层为1
        for(int j = 1;j <= k;j++)
            dp[j][1] = 1;

        for(int i = 2;i <= k;i++){
            for(int j = 2;j <= n;j++){
                for(int p = 1;p <= j;p++){
                    //p层，最不利情况下需要的操作数
                    //保证 p < j ,则dp[i][j-p]都有解
                    int m = max(dp[i-1][p-1],dp[i][j-p]) + 1;
                    dp[i][j] = min(dp[i][j],m);
                }
            }
        }
        printVecArr(dp);
        return dp[k][n];
    }
public:
    //时间复杂度O(k*n*logn)
    int superEggDrop1(int k, int n) {
        //思路：动态规划
        //极端情况：如果只有一个蛋，则从一层开始逐层向上，最多就是测的楼层高度
        //极端情况：如果有无数个蛋，则采用二分法进行测量楼层高度
        //example:假设有100层楼，两个蛋，可以每10层扔一个，可知最多试19次
        // 10,20,30,40,50,60,70,80,90,100  (第一颗蛋用来缩小范围，第二颗蛋用来从碎了的下一个10倍数往上依次寻找)
        //假如第一颗扔在10层没破，然后去20层扔，破了，剩下那一颗从11层开始逐层向上(该种情况下最多扔 2+9 = 11次) 最差情况下就是99层，需要扔19次
        //example:假设有100层，两个蛋，为了平摊复杂度，可以选择按照第一颗逐层减少
        // n,n-1,n-2,...,1 (n+1)*n/2 = 100 n ~= 14
        //14,27,39,50,60,69,77,84,90,95,99,100
        //假设第一次扔在14层没破，去27层扔，破了，剩下从15层开始逐层向上（该种情况下最多扔 2+12 = 14）因为把复杂度平均了，所以任何情况下最差都是14次
        //题意转化为
        //N 个楼层，有 K 个蛋，求最少要扔 T 次，才能保证当 F 无论是 0 <= F <= N 中哪个值，都能测试出来
        //假设从x层开始扔鸡蛋，如果鸡蛋碎了，则应该用k-1个蛋从1到x-1层寻找;如果鸡蛋没碎，则应该用k个蛋从剩下n-x层开始寻找
        //由于要保证在最不利的情况下也能求解出问题 ,则应该选择两种情况中的最大值
        // M(x) = max(dp(k-1,x-1),dp(k,n-x))+1 表示从x层楼往下扔得出f需要的操作数
        //由于要求出最小的操作数 dp(k,n) = min{M(x)}
        //dp初始状态 dp(1,x) = x, dp(k,1) = 1

        //优化：可知dp(k-1,x-1)是随着x单调递增的，dp(k,n-x)是随着x单调递减的
        //而 dp(k,n) = min(max(dp(k-1,x-1),dp(k,n-x))+1); 就是要求出两个函数相交的位置就是min(max(M(x))) 最小的x位置
//             f(dp(k,n-x))  f(dp(k-1,x-1))
//                |     \  /      |
//                |      \/       |
//                |      /\       |
//                |     /  \      |
//                     x0  x1
//                _________________
        //比较在 x_0和 x_1 处两个函数的最大值，取一个最小的作为 xx 即可。在数学上，我们可以证明出 x_0和 x_1
        //相差 1，这也是比较显然的，因为它们正好夹住了那个想象中的交点，并且相距尽可能地近。因此我们就可以使用二分查找的方法找出 x_0 ，再得到 x_1
        vector<vector<int>> dp = vector<vector<int>>(k + 1,vector<int>(n + 1,n));
        //k个蛋，n层楼
        for(int i = 0;i <= k;i++)
            dp[i][0] = 0;
        //只有一个蛋
        for(int i = 1;i <= n;i++)
            dp[1][i] = i;
        //楼层为1
        for(int j = 1;j <= k;j++)
            dp[j][1] = 1;

        for(int i = 2;i <= k;i++){
            for(int j = 2;j <= n;j++){
                int left = 1;
                int right = j + 1;
                //二分查找找到dp[k-1][x-1]与dp[k,n-x]最近的值
                //找到首个dp[k,n-x] < dp[k-1][x-1]的位置 x1
                //在[1,j+1)楼层间寻找，寻找向右偏移，
                while(left < right){
                    int mid = left + (right - left)/2;
                    if(dp[i][j-mid] < dp[i-1][mid-1]){
                        right = mid;
                    }else{
                        //dp[i][j-mid] >= dp[i-1][mid-1]
                        left = mid + 1;
                    }
                }
                if(left == j + 1){
                    //则选择第j层
                    dp[i][j] = max(dp[i][0],dp[i-1][j-1])+1;
                }else{
                    dp[i][j] = min(max(dp[i][j-left+1],dp[i-1][left-1-1])+1,max(dp[i][j-left],dp[i-1][left-1])+1);
                }
            }
        }
        return dp[k][n];
    }
public:
    //时间复杂度O(k*n)
    //方法三：逆向思维
    //思路：反过来想这个问题：如果我们可以做 t 次操作，而且有 k 个鸡蛋，那么我们能找到答案的最高的 n 是多少？我们设 f(t,k) 为在上述条件下的 n。
    // 如果我们求出了所有的 f(t, k),那么只需要找出最小的满足 f(t,k)≥n 的 t
    // 动态规划：由于要找出最高的n,所以不需要考虑在哪里扔鸡蛋
    // 如果鸡蛋没有碎，在该层以上还可以有 f(t-1,k)层
    // 如果鸡蛋碎了,则说明在该层的下方可以有 f(t-1,k-1)层
    //状态转移方程 那最极端的情况就是恰好找到那个层数求和 f(t,k) = f(t-1,k) + f(t-1,k-1) + 1;(该层上最多层数，该层下最多层数，再加上本层)
    //base case 最初状态，f(t,1) = t (只有一个鸡蛋)
    // f(1,k) = 1 (k>=1 只能做一次操作找到的最高n)
    //t最多做n次
    /**
     *   f为哪一层蛋会碎
     * dp[x][y] 表示 x个鸡蛋 y次操作 可以最多确认多少层,即不管你这个鸡蛋在dp[x][y]及其下面那一层会碎，我们都能查出f

        假设:
        已知 x-1 个鸡蛋 y-1 次操作 可以确认 n1层
        已知 x 个鸡蛋 y-1 次操作 可以确认 n2层
        现在想知道 x个鸡蛋 y次操作 可以确认多少层

        那么，我们第一次扔鸡蛋时，直接从 n1+1 层开始扔

        如果碎了，我们还有 x-1个鸡蛋 y-1次操作 可以从 n1+1 底下的n1层找出f;
        如果没碎，我们还有 x个鸡蛋 y-1次操作 可以从 n1+1上面的n2层找出f;

        所以 dp[x][y] = dp[x-1][y-1] + dp[x][y-1] + 1

     *
     * @param k
     * @param n
     * @return
     */
    int superEggDrop2(int k, int n) {
//        vector<vector<int>> dp = vector<vector<int>>(n+1,vector<int>(k+1,0));
        //空间压缩 由于状态转移方程只跟左上，正上有关 初始化只操作1次 最高1层楼
        vector<int> dp = vector<int>(k+1,1);
//        //dp[i][1] 只有一个蛋，操作i次
//        for(int i = 1;i <= n;i++)
//            dp[i][1] = i;
//        //dp[1][i] 只能操作1次，i个蛋
//        for(int i = 1;i <= k;i++)
//            dp[1][i] = 1;

        //k >= 1 && n >= 1 如果楼层为1层，则最少扔一次 初始化结果为1
        int res = 1;
        for(int i = 2;i <= n;i++){
            //dp[i-1][j-1] ,0个蛋 最高楼层 0
            int prev = 0;
            for(int j = 1;j <= k;j++){
//                dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + 1;
                int nextLeftUp = dp[j];
                dp[j] = dp[j] + prev + 1;
                prev = nextLeftUp;
            }
            //如果i次操作，k个鸡蛋满足n层楼就保存 直接跳出
            if(dp[k] >= n){
                res = i;
                break;
            }
        }
        return res;
    }
};

int main(){
//    int k = 2;
//    int n = 6;
    //result
    //3
    int k = 4;
    int n = 10000;
    //result 23
    int res = Solution().superEggDrop2(k,n);
    cout<<res<<endl;
    //result
    //3
}