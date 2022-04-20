//
// Created by wzy on 2022/4/20.
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

class NumArray {
    /*
    思路：由于数组不可变，且需要多次调用索引间的元素和
    使用前缀和进行处理(存储从0索引到指定索引的前缀和)
    */
public:
    NumArray(vector<int>& nums) {
        int sum = 0;
        for(int i = 0;i < nums.size();i++){
            //prefix_sum 存储从[0,i]的前缀和
            sum += nums[i];
            prefix_sum.push_back(sum);
        }
    }

    int sumRange(int left, int right) {
        //由于包含左右边界 所以左侧需要left-1 , [left,right]
        int pre = (left == 0)?0:prefix_sum[left - 1];
        return prefix_sum[right] - pre;
    }
    ~NumArray() = default;
private:
    vector<int> prefix_sum;
};

int main(){
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray* numArray = new NumArray(nums);
    int left = 0;int right = 2;
    cout<<numArray->sumRange(left,right)<<endl;
    //result 1
    left = 2;right = 5;
    cout<<numArray->sumRange(left,right)<<endl;
    //result -1
    left = 0;right = 5;
    cout<<numArray->sumRange(left,right)<<endl;
    //result -3
    delete numArray;
}