//
// Created by wangzy on 2022/3/26.
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
    int findKthLargest(vector<int>& nums, int k) {
        //快速排序Qsort
        //要寻找位置的索引
        int target = nums.size() - k;
        srand(time(0));
        qSortHelper2(nums,target,0,nums.size()-1);
        return nums[target];
    }
private:
    void qSortHelper(vector<int>& nums,int target,int start,int end){
        int pos = partition(nums,start,end);
        if(target == pos){
            return ;
        }else if(target > pos){
            qSortHelper(nums,target,pos+1,end);
        }else{
            //target < pos
            qSortHelper(nums,target,start,pos-1);
        }
    }
    void qSortHelper2(vector<int>& nums,int target,int start,int end){
        pair<int,int> pos_range = partition2(nums,start,end);
        if(target <= pos_range.first && target >= pos_range.second){
            return ;
        }else if(target > pos_range.second){
            qSortHelper2(nums,target,pos_range.second+1,end);
        }else{
            //target < pos
            qSortHelper2(nums,target,start,pos_range.first-1);
        }
    }
    int partition(vector<int>& nums,int start,int end){
        if(start == end)
            return start;
        int rand_idx = start+rand()%(end - start + 1);
        swap(nums[start],nums[rand_idx]);
        int v = nums[start];
        int l = start+1;int r = end;
        //nums[start+1,l) < v nums(r,end] > v
        //循环结束条件 l == r + 1
        while(l <= r){
            while(l<=r && nums[l]<v)
                l++;
            while(l<=r && nums[r]>v)
                r--;
            if(l > r)
                break;
            swap(nums[l],nums[r]);
            l++;r--;
        }
        //nums[...r,l...]
        swap(nums[start],nums[r]);
        return r;
    }
    pair<int,int> partition2(vector<int>& nums,int start,int end){
        //采用三路快排来返回区间
        if(start == end)
            return make_pair(start,end);
        int rand_idx = start+rand()%(end-start+1);
        swap(nums[start],nums[rand_idx]);
        int v = nums[start];
        int l = start ;int r = end + 1;int p = start+1;
        //nums[start+1,l] < v nums[l+1,p) == v nums[r,end] > v
        while(p < r){
            if( nums[p]<v)
                swap(nums[++l],nums[p++]);
            else if( nums[p]==v)
                p++;
            else if( nums[p]>v)
                swap(nums[p],nums[--r]);
        }
        //nums[...r,p...]
        swap(nums[start],nums[l]);
        // [l...r] == v
        return make_pair(l,r-1);
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

int main(){
//    vector<int> vec = {3,2,1,5,6,4};
//    int k = 2;
    //result 5
//    vector<int> vec = {3,2,3,1,2,4,5,5,6};
//    int k = 4;
    //result 4
    vector<int> vec = {99,99};
    int k = 1;
    int res = Solution().findKthLargest(vec,k);
    cout<<res<<endl;
}
