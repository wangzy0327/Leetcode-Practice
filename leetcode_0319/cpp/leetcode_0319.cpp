//
// Created by wzy on 2022/7/13.
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

class Solution{
public:
    /**
     * 时间复杂度 O(1)
     * @param n
     * @return
     */
    int bulbSwitch(int n) {
        //解题思路：
        /**
        所有电灯最开始都是关着的，如果要被点亮的话，必然是操作奇数次开关
        ep:只有6盏灯，第6盏会被操作几次开关呢？ 6=1x6=2x3 在第一轮、第二轮、第三轮、第六轮会被按
        如果是16盏灯，第16盏 16=1x16=2x8=4x4 ,第一轮，第二轮，第四轮，第八轮，第十六轮
        从以上可以看出，因子都是成对出现的，除非遇到 n*n = m 的情况会出现奇数次。
        假设最后有16盏灯，求16的平方根，就可以得到 小于16的平方根 就是4盏灯会被亮着，
        分别是 1x1=1盏 2x2=4盏 3x3=9盏 4x4=16盏
         */
        return (int)sqrt(n);
    }
};

class Solution2 {
public:
    /**
     * 时间复杂度 O(n*n)
     * @param n
     * @return
     */
    int bulbSwitch(int n) {
        if(n == 0)
            return 0;
        //第一轮都亮灯
        vector<int> arr = vector<int>(n,1);
        for(int i = 2;i <= n;i++){
            for(int j = i - 1;j < n;j += i){
                arr[j] = (arr[j] == 0)?1:0;
            }
        }
        int count = 0;
        for(int i = 0;i < n;i++)
            if(arr[i] == 1)
                count++;
        return count;
    }
};



int main(){
//    int n = 3;
    //result 1
    /**
     * 解释：
        初始时, 灯泡状态 [关闭, 关闭, 关闭].
        第一轮后, 灯泡状态 [开启, 开启, 开启].
        第二轮后, 灯泡状态 [开启, 关闭, 开启].
        第三轮后, 灯泡状态 [开启, 关闭, 关闭].

        你应该返回 1，因为只有一个灯泡还亮着
     *
     */
    int n = 10000000;
    //result 3162
    int res1 = Solution().bulbSwitch(n);
    int res2 = Solution2().bulbSwitch(n);
    cout<<res1<<endl;
    cout<<res2<<endl;

}