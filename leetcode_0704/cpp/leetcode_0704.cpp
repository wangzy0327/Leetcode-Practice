//
// Created by wzy on 2022/3/18.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        //[left,right] 跳出循环条件为 left > right
        while(left <= right){
            //防止数值越界
            int mid = left + (right -  left)/2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target){
                left = mid + 1;
            }else{
                //nums[mid] > target
                right = mid - 1;
            }
        }
        return -1;
    }
};

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

int main() {
//    vector<int> nums = {-1,0,3,5,9,12};
//    int target = 9;
    vector<int> nums nums = {2,2};
    int target = 3;
    int res = Solution().search(nums,target);
    cout<<res<<endl;
}

