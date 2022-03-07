//
// Created by wzy on 2022/3/7.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //首先要读懂题意 什么是连续的序列
        // 举栗 [100,4,200,1,3,2] 中 1,2,3,4是连续的整数就是连续序列(不要求它们本身有顺序)
        //每次只有最小的数字 去统计长度，避免中间数字统计，如果遇到前后有连续的数字跳过
        unordered_set<int> record;
        //对元素去重，减少重复元素的判断
        for(auto num : nums)
            record.emplace(num);
        int longSeqLen = 0;
        for(auto num : record){
            //从连续序列最下数值开始，ep[100,4,200,1,3,2] 只从1开始，其他跳过
            //内层循环判断连续序列的长度进行比较
            int curLen = 1;
            if(!record.count(num - 1)){
                for(int j = num + 1;record.count(j);j++)
                    curLen++;
                longSeqLen = max(longSeqLen,curLen);
            }
        }
        return longSeqLen;
    }
};

int main(int argc,char* argv[]){
    vector<int> nums = {100,4,200,1,3,2};
    int res = Solution().longestConsecutive(nums);
    cout<<res<<endl;
    //res
    //4
}
