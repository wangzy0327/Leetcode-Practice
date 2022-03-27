//
// Created by wangzy on 2022/3/27.
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
#include <random>
#include <ctime>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        srand(time(0));
        qSort(nums,0,nums.size()-1);
        return nums;
    }
private:
    void qSort(vector<int>& nums,int start,int end){
        if(start >= end)
            return;
        int pos = partition(nums,start,end);
        qSort(nums,start,pos-1);
        qSort(nums,pos+1,end);
    }
    int partition(vector<int>& nums,int start,int end){
        if(start == end)
            return start;
        int rand_idx = start + rand()%(end-start+1);
        swap(nums[start],nums[rand_idx]);
        int v = nums[start];
        int l = start+1;int r = end;
        //nums[start+1,l)<v nums(r,end]>v
        while(l <= r){
            while(l<=r && nums[l]<v)
                l++;
            while(l<=r && nums[r]>v)
                r--;
            if(l > r)
                break;
            swap(nums[l++],nums[r--]);
        }
        swap(nums[start],nums[r]);
        return r;
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
    vector<int> nums = {5,1,1,2,0,0};
    //result
    //[0,0,1,1,2,5]
    printVec(nums);
    nums = Solution().sortArray(nums);
    printVec(nums);
}