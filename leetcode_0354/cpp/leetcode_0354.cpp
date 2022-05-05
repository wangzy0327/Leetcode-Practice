//
// Created by wangzy on 2022/5/4.
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

class cmp2{
public:
    bool operator ()(const vector<int>& a,const vector<int>& b){
        return a[0]==b[0] ? b[1] < a[1] : a[0] < b[0];
    }
};
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        //思路1:自定义排序+动态规划
        //思路2:自定义排序+贪心算法(二分查找)
        //首先会想到先进行信封排序 (排序规则将宽相同的高度高的排在前面，宽度小的排在前面)
        //这样的排序保证了 排在后面的信封只要高度比前面高度高，则一定可以嵌套前面的信封
        //排序过后就是找 信封嵌套数量dp[j]
        //重叠子问题:信封嵌套数量
        //初始Base:dp[0] = 1
        //状态为: 排序后的信封高度数组值大小 nums[i]
        //状态转移方程: dp[i] = max(dp[i],dp[j] + 1) | {j<i && nums[i]>nums[j] }
        //使用lambda表达式 自定义函数对象
        auto cmp = [](const vector<int>& env1,const vector<int>& env2) -> bool {
            return env1[0] == env2[0]?env1[1] > env2[1]:env1[0] < env2[0];
        };
        // //排序
        sort(envelopes.begin(),envelopes.end(),cmp);
        //将envelopes高度抽取出来
        vector<int> nums = vector<int>(envelopes.size(),0);
        for(int i = 0;i < nums.size();i++)
            nums[i] = envelopes[i][1];
        return lengthOfEnv2(nums);

    }
private:
    //Time of Exceeded
    int lengthOfEnv(vector<int>& nums){
        vector<int> dp = vector<int>(nums.size(),1);
        int max_num = 1;
        for(int i = 0;i < dp.size();i++){
            for(int j = 0;j < i;j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i],dp[j]+1);
                    max_num = max(dp[i],max_num);
                }
            }
        }
        return max_num;
    }
    //贪心算法：保证每个信封个数，对应着最小的信封高度
    //最终可以放置的信封piles堆数
    //arr用来存储嵌套数量n的最小元素,索引为嵌套数量
    //使用二分搜索来完成搜索 前面大于nums的元素
    int lengthOfEnv2(vector<int>& nums){
        //piles用来记录最嵌套信封的最大数量
        int piles = 0;
        vector<int> arr = vector<int>(nums.size(),0);
        //二分搜索退出条件 left==right [left,right)
        //找到第一个大于nums[i]的元素 然后进行替换
        for(int i = 0;i < nums.size();i++){
            //跳出的left就是要替换的下一个位置
            int left = 0;
            int right = piles;
            while(left < right){
                int mid = left + (right - left)/2;
                if(nums[i] <= arr[mid]){
                    right = mid;
                }else if(nums[i] > arr[mid]){
                    left = mid + 1;
                }
            }
            //如果在指定区间没找到大于或等于其元素放置的位置则在后面新建
            if(left == piles)
                piles++;
            arr[left] = nums[i];
        }
        return piles;
    }
};

int main(){
    vector<vector<int>> envelopes = {
//            {6,4},
//            {6,5}
    //result
    //1
            {5,4},
            {6,4},
            {6,7},
            {2,3}
    };
    int res = Solution().maxEnvelopes(envelopes);
    cout<<res<<endl;
    //result
    //3 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]
}