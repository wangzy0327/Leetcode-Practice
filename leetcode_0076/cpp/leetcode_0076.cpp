//
// Created by wzy on 2022/3/21.
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
    string minWindow(string s, string t) {
        //采用哈希表存储t所需要的每个字符数量和字符种类
        //滑动窗口(当字符种类少于 所需种类 右边界向右滑动)
        // 当字符种类等于 所需种类 左边界向右滑动 并且 valid小于所需字符种类
        //滑动窗口退出条件，右边界滑动到最大长度
        unordered_map<char,int> need;
        for(char c : t)
            need[c]++;
        //滑动窗口哈希表
        unordered_map<char,int> window;
        //当前窗口有效的种类数量
        int valid = 0;
        int left = 0;
        int right = 0;
        //[0,0)
        //最小子串左侧索引 ，长度
        int start = 0, len = INT_MAX;
        while(right < s.size() || valid == need.size()){
            if(valid < need.size()){
                char rChar = s[right];
                if(need.count(rChar)){
                    //如果滑动窗口该字符数量达到所需字符数量则 有效数量+1
                    window[rChar]++;
                    if(window[rChar] == need[rChar])
                        valid++;
                }
                //右侧边界右移
                right++;
            }
            if(valid == need.size()){
                char lChar = s[left];
                //[left,right)
                if(len > right - left){
                    len = right - left;
                    start = left;
                }
                if(need.count(lChar)){
                    if(window[lChar] == need[lChar])
                        valid--;
                    window[lChar]--;
                }
                //左侧边界右移
                left++;
            }
        }
        return (len==INT_MAX)?"":s.substr(start,len);
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
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string res = Solution().minWindow(s,t);
    cout<<res<<endl;
}