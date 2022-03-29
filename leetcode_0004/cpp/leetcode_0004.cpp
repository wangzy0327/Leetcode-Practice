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
        //有序且要求找寻时间复杂度要求O(log(m+n))可以想到二分搜索
        //两个有序数组中位数的寻找可以转化为找寻 两个有序数组中间的数
        //等价于 长度为m和长度为n的两个数组 如果(m+n)为奇数，即寻找 两个数组中第(m+n)/2+1个数
        //如果(m+n)为偶数，即寻找 两个数组中第(m+n)/2个数和第(m+n)/2+1个数
        //题目就转化为寻找第kth个数的问题，由于是有序的，这个问题可以采用二分搜索进行过滤筛选直到找到对应元素
        //假如k即为中位数在两个数组长度中的 序列位置，则可以分别找到在两个数组中第[k/2]位置
        //比较两个数组中 [k/2]位置的值，较小的那个，可以过滤掉其[k/2]左边的元素（这里需要注意数组长度跟[k/2]大小的问题）,因为它最多为第k-1个序列
        //二分搜索寻找的极限即为k==1,返回 两个数组中以当前索引起点最小的那个
        int m = nums1.size();
        int n = nums2.size();
        int k = (m+n)/2;
        if((m+n)%2 == 1){
            //奇数
            return (double)findKthElement(nums1,nums2,k+1);
        }else{
            return (double)(findKthElement(nums1,nums2,k)+findKthElement(nums1,nums2,k+1)) /2;
        }
    }
private:
    int findKthElement(vector<int>& nums1,vector<int>& nums2,int k)    {
        int m = nums1.size();
        int n = nums2.size();
        int idx1 = 0;
        int idx2 = 0;
        while(true){
            //特殊情况 nums1为空，nums2为空
            if(idx1 == m){
                return nums2[idx2+k-1];
            }
            if(idx2 == n){
                return nums1[idx1+k-1];
            }
            //二分搜索的结束条件
            if(k == 1)
                return min(nums1[idx1],nums2[idx2]);
            //注意索引
            int newIdx1 = min(idx1+k/2-1,m-1);
            int newIdx2 = min(idx2+k/2-1,n-1);
            if(nums1[newIdx1] <= nums2[newIdx2]){
                //缩小找寻范围
                k-=(newIdx1 - idx1 + 1);
                idx1 = newIdx1 + 1;
            }else{
                //nums1[newIdx1] > nums2[newIdx2]
                k-=(newIdx2 - idx2 + 1);
                idx2 = newIdx2 + 1;
            }
        }
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