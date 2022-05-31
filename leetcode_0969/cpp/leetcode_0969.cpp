//
// Created by wangzy on 2022/5/31.
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

template<typename T>
string convertVecToStr(std::vector<T> l){
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
    return res;
}

template<typename T>
void printVecArr(std::vector<std::vector<T>> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << convertVecToStr(ele);
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    std::cout<<res<<std::endl;
}

class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        //思路：理解题意 arr[i]的范围在1...arr.length之间 翻转操作符合递归性质
        //采用贪心算法
        //使用翻转的方式对arr[0...n-1]进行排序，关键点在于每轮递归需要将最大的元素arr[n-1]
        //放在数组的最后，然后递归向前排序arr[0...n-2]
        //如何才能将当前寻找数组arr[0...k-1]的最大值放在末尾
        //那就是如果当前值不在数组最后假设在i-1位置，则翻转前i个位置，将原i位置的翻转到了0的位置
        //接着翻转前k个元素，将最大值放在k-1的位置上，本轮递归结束
        int n = arr.size();
        pancakeHelper(arr,n);
        return res;
    }
private:
    vector<int> res;
    void pancakeHelper(vector<int>& arr,int k){
        //k <= 1 只有一个元素直接返回
        if(k > 1){
            int ind = k - 1;
            while(arr[ind] != k)
                ind--;
            //如果当前索引就是最大值则递归向下
            if(ind == k - 1)
                pancakeHelper(arr,k-1);
            else{
                //1.翻转前ind个元素
                rotate(arr,ind+1);
                res.push_back(ind+1);
                //2.翻转前k个元素
                rotate(arr,k);
                res.push_back(k);
                //3.第k大元素放在指定位置后 递归向下
                pancakeHelper(arr,k-1);
            }
        }
    }
    void rotate(vector<int>& arr,int m){
        int l = 0;
        int r = m - 1;
        while(l < r)
            swap(arr[l++],arr[r--]);
    }
};

int main(){
    vector<int> arr = {3,2,4,1};
    vector<int> sort_arr = Solution().pancakeSort(arr);
    //result
    //[4,2,4,3]
    //我们执行 4 次煎饼翻转，k 值分别为 4，2，4，和 3。
    //初始状态 arr = [3, 2, 4, 1]
    //第一次翻转后（k = 4）：arr = [1, 4, 2, 3]
    //第二次翻转后（k = 2）：arr = [4, 1, 2, 3]
    //第三次翻转后（k = 4）：arr = [3, 2, 1, 4]
    //第四次翻转后（k = 3）：arr = [1, 2, 3, 4]，此时已完成排序

    //[3,4,2,3,1,2]
    //初始状态 arr = [3, 2, 4, 1]
    //第一次翻转后（k = 3）：arr = [4,2,3,1] 将最大值放在首位
    //第二次翻转后 (k = 4): arr = [1,3,2,4] 将最大值放在末尾 接着递归向下
    //第三次翻转后 (k = 2): arr = [3,1,2,4] 将次最大值放在首位
    //第四次翻转后 (k = 3): arr = [2,1,3,4] 将次最大值放在倒二末尾
    //第五次翻转后 (k = 1): arr = [2,1,3,4] 将找到的2放在跟首位交换 (可优化)
    //第六次翻转后 (k = 2): arr = [1,2,3,4] 将2放在指定位置
    printVec(sort_arr);
}