//
// Created by wangzy on 2022/3/20.
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
    int minEatingSpeed(vector<int>& piles, int h) {
        //思路：二分搜索，吃香蕉速度为[1,max[piles]+1)
        int left = 1;
        int right = maxPiles(piles) + 1;
        //[left,right]
        //循环退出条件 left == right [x,x)为空，取不到
        while(left < right){
            int mid = left + (right - left)/2;
            if(canFinish(piles,mid,h)){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool canFinish(vector<int>& piles,int k,int h){
        for(int i = 0;i < piles.size();i++){
            int spend =  piles[i]/k + ((piles[i]%k==0)?0:1);
            if(h - spend >= 0){
                h -= spend;
            }else{
                return false;
            }
        }
        return true;
    }
    // long long sumPiles(vector<int>& piles){
    //     long long res = 0;
    //     for(auto ele:piles)
    //         res += ele;
    //     return res;
    // }
    int maxPiles(vector<int>& piles){
        int res = piles[0];
        for(int i = 1;i < piles.size();i++)
            if(res < piles[i])
                res = piles[i];
        return res;
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
    vector<int> vec = {3,6,7,11};
    int h = 8;
    int res = Solution().minEatingSpeed(vec,h);
    //result
    //4
    cout<<res<<endl;
}

