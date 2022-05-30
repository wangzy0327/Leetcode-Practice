//
// Created by wangzy on 2022/5/30.
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

class Cmp2{
    public:
        bool operator()(const vector<int>& a,const vector<int>& b) const{
            return (a[0] == b[0])?a[1]<b[1]:a[0]>b[0];
        }
};

struct Cmp3{
    bool operator()(const vector<int>& a,const vector<int>& b) const{
        return (a[0] == b[0])?a[1]<b[1]:a[0]>b[0];
    }
};

class Solution {
public:
    //lambda表达式
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {

        //首先对数对进行排序，按照数对的元素 1 降序排序，按照数对的元素 2 升序排序。原因是，按照元素 1 进行降序排序，对于每个元素，在其之前的元素的个数，就是大于等于他的元素的数量，而按照第二个元素正向排序，我们希望 k 大的尽量在后面，减少插入操作的次数
        //按照排完序后的顺序，依次将每个人放入队列中，那么当我们放入第 i 个人时
        // 1. 第0,...,i-1个人已经站在队列中，只要他们站在第i个人前面，就会对i个人产生影响，因为他们都比第i个人高或等于
        // 2. 第i+1,...,n-1个人还没有在队列中，无论他们放在哪里都不会对第i个人产生影响，因为他们都比第i个人矮
        [](const vector<int>& u, const vector<int>& v) {
            return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
        };
        //函数对象 按照元素1降序，按照元素2升序 注意降序是 返回 a > b 升序返回 a < b
        auto cmp = [](const vector<int>& a,const vector<int>& b) ->bool {return (a[0] == b[0])?a[1]<b[1]:a[0]>b[0];};
        //priority_queue传入的是函数对象类
//        priority_queue<int,vector<int>,decltype(cmp)> pq;
        //传入函数对象 sort(a.begin(),a.end(),less<int>());
        sort(people.begin(),people.end(),cmp);
        //依次插入
        vector<vector<int>> res;
        for(int i = 0;i < people.size();i++){
            if(res.size() > people[i][1]){
                res.insert(res.begin()+people[i][1],people[i]);
            }else{
                //res.size() <= people[i][0]
                res.push_back(people[i]);
            }
        }
        return res;
    }
    //函数对象
    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),Cmp2());
        //依次插入
        vector<vector<int>> res;
        for(int i = 0;i < people.size();i++){
            if(res.size() > people[i][1]){
                res.insert(res.begin()+people[i][1],people[i]);
            }else{
                //res.size() <= people[i][0]
                res.push_back(people[i]);
            }
        }
        return res;
    }
    //结构体 函数对象
    vector<vector<int>> reconstructQueue3(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),Cmp3());
        //依次插入
        vector<vector<int>> res;
        for(int i = 0;i < people.size();i++){
            if(res.size() > people[i][1]){
                res.insert(res.begin()+people[i][1],people[i]);
            }else{
                //res.size() <= people[i][0]
                res.push_back(people[i]);
            }
        }
        return res;
    }
};


int main(){
    vector<vector<int>> people = {
            {7,0},{4,4},{7,1},{5,0},{6,1},{5,2}
    };
    //result
    //[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
    /*
     编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
    编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
    编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
    编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
    编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
    编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
    因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
     * */
    vector<vector<int>> res = Solution().reconstructQueue3(people);
    printVecArr(res);
    return 0;
}