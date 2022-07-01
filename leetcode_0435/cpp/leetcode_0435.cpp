//
// Created by wzy on 2022/7/1.
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
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    //思路：
        /**
    假设在某一种最优的选择方法中，[l_k, r_k] 是首个（即最左侧的）区间，那么它的左侧没有其它区间，右侧有若干个不重叠的区间。设想一下，如果此时存在一个区间 [l_j, r_j]，使得 r_j < r_k，即区间 jj 的右端点在区间 kk 的左侧，那么我们将区间 k 替换为区间 j，其与剩余右侧被选择的区间仍然是不重叠的。而当我们将区间 k 替换为区间 j 后，就得到了另一种最优的选择方法


    我们可以不断地寻找右端点在首个区间右端点左侧的新区间，将首个区间替换成该区间。那么当我们无法替换时，首个区间就是所有可以选择的区间中右端点最小的那个区间。因此我们将所有区间按照右端点从小到大进行排序，那么排完序之后的首个区间，就是我们选择的首个区间。

    如果有多个区间的右端点都同样最小怎么办？由于我们选择的是首个区间，因此在左侧不会有其它的区间，那么左端点在何处是不重要的，我们只要任意选择一个右端点最小的区间即可。

    当确定了首个区间之后，所有与首个区间不重合的区间就组成了一个规模更小的子问题。由于我们已经在初始时将所有区间按照右端点排好序了，因此对于这个子问题，我们无需再次进行排序，只要找出其中与首个区间不重合并且右端点最小的区间即可。用相同的方法，我们可以依次确定后续的所有区间。
        */
        //反过来 达到不重叠区间数，则需要移除区间最小
        //类比:leetcode 0452
        auto cmp = [](const vector<int>& u,const vector<int>& v)->bool{return u[1] < v[1];};
        sort(intervals.begin(),intervals.end(),cmp);
        int count = intervals.size();
        //需要射箭的数量
        int ans = 1;
        int lastEnd = intervals[0][1];
        for(auto interval : intervals){
            //这里由于边界相等不算重叠，则是大于等于
            if(interval[0] >= lastEnd){
                ans++;
                lastEnd = interval[1];
            }
        }
        return count - ans;
    }
};

int main(){
    vector<vector<int>> intervals =
    {{-52,31},{-73,-26},{82,97},{-65,-11},{-62,-49},{95,99},{58,95},{-31,49},{66,98},{-63,2},{30,47},{-40,-26}};
    //result
    //7

//    vector<vector<int>> intervals =
//            {{1,2},{2,3},{3,4},{1,3}};
    //result
    //1
    //移除 [1,3] 后，剩下的区间没有重叠

    int res = Solution().eraseOverlapIntervals(intervals);
    cout<<res<<endl;
    return 0;
}
