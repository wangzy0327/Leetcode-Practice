//
// Created by wzy on 2022/4/21.
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
public:
    NumArray(vector<int>& nums) {
        //思路：采用线段树来降低对元素的更新时间复杂度(Ologn)(注意线段树不一定是完全二叉树)
        /*
                           [0...9]
                  [0...4]          [5...9]
            [0...2]  [3...4]     [5...7]    [8...9]
       [0...1] [2]   [3]  [4]  [5...6] [7] [8]    [9]
       [0] [1]                 [5] [6]
        */
        //如图可知：叶子结点在最差的情况下占据下面两层
        // n = 2^k   最多 2*n就够
        // n = 2^k+1  最多需要 4*n 就够
        n = nums.size();
        segementTree = vector<int>(4*n,0);
        builder(nums,0,0,n-1);
    }

    void update(int index, int val) {
        change(index,val,0,0,n-1);
    }

    int sumRange(int left, int right) {
        return sumRangeHelper(left,right,0,0,n-1);
    }
    ~NumArray() = default;
private:
    int n;
    vector<int> segementTree;
    //向线段树表示区间[start,end]添加元素
    void builder(vector<int>& nums,int treeIdx,int start,int end){
        //如果start == end说明找到指定位置
        if(start == end){
            segementTree[treeIdx] = nums[start];
            return ;
        }
        int mid = start + (end - start)/2;
        int leftIdx = treeIdx*2+1;
        int rightIdx = treeIdx*2+2;
        //区间切分左半和右半
        builder(nums,leftIdx,start,mid);
        builder(nums,rightIdx,mid+1,end);
        segementTree[treeIdx] = segementTree[leftIdx] + segementTree[rightIdx];
    }
    //更新元素
    void change(int idx,int val,int treeIdx,int start,int end){
        if(start == end){
            segementTree[treeIdx] = val;
            return ;
        }
        int mid = start + (end - start)/2;
        int leftIdx = treeIdx*2+1;
        int rightIdx = treeIdx*2+2;
        if(idx <= mid){
            change(idx,val,leftIdx,start,mid);
        }else{
            change(idx,val,rightIdx,mid+1,end);
        }
        segementTree[treeIdx] = segementTree[leftIdx] + segementTree[rightIdx];
    }
    //分段求和
    int sumRangeHelper(int left,int right,int treeIdx,int start,int end){
        if(start == left && end == right){
            return segementTree[treeIdx];
        }
        int mid = start + (end - start)/2;
        int leftIdx = treeIdx*2+1;
        int rightIdx = treeIdx*2+2;
        if(left > mid){
            //如果寻找区间在右边
            return sumRangeHelper(left,right,rightIdx,mid+1,end);
        }else if(right <= mid){
            //如果寻找区间在左边
            return sumRangeHelper(left,right,leftIdx,start,mid);
        }else{
            //如果寻找区间两边都有
            return sumRangeHelper(left,mid,leftIdx,start,mid) + sumRangeHelper(mid+1,right,rightIdx,mid+1,end);
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

int main(){
    vector<int> nums = {1,3,5};
    NumArray* numArray = new NumArray(nums);
    //NumArray numArray = new NumArray([1, 3, 5]);
    cout<<numArray->sumRange(0,2)<<endl;
    //numArray.sumRange(0, 2); // 返回 1 + 3 + 5 = 9
    //result
    //9
    numArray->update(1,2);
    //numArray.update(1, 2);   // nums = [1,2,5]
    cout<<numArray->sumRange(0,2)<<endl;
    //numArray.sumRange(0, 2); // 返回 1 + 2 + 5 = 8
    //result
    //8
    delete numArray;
}