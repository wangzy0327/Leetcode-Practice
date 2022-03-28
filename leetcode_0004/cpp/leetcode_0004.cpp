//
// Created by wangzy on 2022/3/28.
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //由于要求时间复杂度为O(log(m+n))而且数组有序，由此可想到需要用到二分查找
        //由于要找到中位数转化为寻找 正序数组中 第k个元素
        //可以分为奇数 (m+n)/2  /偶数 (m+n)/2,(m+n)/2+1
        //每次可以找到 第k/2个元素，即寻找k/2-1索引的位置,每次可以过滤掉较小元素的k/2个元素
        int m = nums1.size();
        int n = nums2.size();
        int k = (m+n)/2;
        if((m+n)%2 == 1){
            return findKthNum(nums1,nums2,k + 1);
        }else{
            return (double)(findKthNum(nums1,nums2,k)+findKthNum(nums1,nums2,k+1))/2;
        }
    }
private:
    int findKthNum(vector<int>& nums1,vector<int>& nums2,int k){
        int idx1 = 0;
        int idx2 = 0;
        while(true){
            //如果出现起始索引超过数组长度，则直接在另一个数组上寻找
            if(idx1 == nums1.size())
                return nums2[idx2+k-1];
            if(idx2 == nums2.size())
                return nums1[idx1+k-1];
            //二分搜索的跳出条件
            if(k == 1)
                break;
            int newpos1 = min((int)nums1.size()-1,idx1+k/2-1);
            int newpos2 = min((int)nums2.size()-1,idx2+k/2-1);
            if(nums1[newpos1]<=nums2[newpos2]){
                k-=(newpos1-idx1+1);
                idx1 = newpos1 + 1;
            }else{
                //nums1[newpos1] > nums2[newpos2]
                k-=(newpos2-idx2+1);
                idx2 = newpos2 + 1;
            }
        }
        return min(nums1[idx1],nums2[idx2]);
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
//    vector<int> nums1 = {1,3};
//    vector<int> nums2 = {2};
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2,4};
    double res = Solution().findMedianSortedArrays(nums1,nums2);
    cout<<res<<endl;
}