//
// Created by wzy on 2022/3/23.
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
    int nextGreaterElement(int n) {
        //1.从后向前遍历找到 后一个位置大于前一个位置的元素. 记录为pos 如果找不到则返回 -1(降序排列不可能有比其更大)
        //2.从后向前遍历，找到刚好大于pos的位置的值 j，然后反转两个位置元素
        //  s[pos]|...>...|s[j]|...>...|
        //3.然后反转pos后面的元素(因为j后面的元素为降序，反转后保证其为下一个更大元素)
        //并将后面的数字按照从小到大排列

        //步骤1
        string s = to_string(n);
        int pos = -1;
        for(int i = s.length()-1;i>0;i--){
            if(s[i] > s[i-1]){
                pos = i - 1;
                break;
            }
        }
        if(pos == -1)
            return -1;

        //步骤2
        for(int i = s.length()-1;i>0;i--){
            if(s[i] > s[pos]){
                swap(s[i],s[pos]);
                break;
            }
        }

        //步骤3
        reverse(s,pos + 1,s.length()-1);
        string str_int_max = to_string(INT_MAX);
        string ano_s = s;
        while(ano_s.length() < str_int_max.length())
            ano_s = "0"+ano_s;
        return (ano_s > str_int_max)?-1:atoi(s.c_str());
    }
private:
    void reverse(string& s,int start,int end){
        while(start < end){
            char tmp = s[start];
            s[start] = s[end];
            s[end] = tmp;
            start++;end--;
        }
    }
};

int main() {
    int a = INT_MAX;
    cout<<a<<endl;
    //2147483647
//    int n = 21;
    //result
    //-1

//    int n = 2147483647;
    //result
    //-1

//    int n = 1999999999;
    //result
    // -1

    int n = 13;
    //result
    // 31
    cout<<Solution().nextGreaterElement(n)<<endl;


}