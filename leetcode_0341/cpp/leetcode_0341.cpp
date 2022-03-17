//
// Created by wzy on 2022/3/17.
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

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedInteger{
    int value;
    vector<NestedInteger> sub;
public:
    NestedInteger(){
        value = INT_MIN;
    }
    NestedInteger(int _value){
        value = _value;
    }
    NestedInteger(vector<NestedInteger>& _sub){
        value = INT_MIN;
        for(NestedInteger nestedInteger : _sub)
            sub.push_back(nestedInteger);
    }
    bool isInteger() const{
        return value != INT_MIN;
    };
    int getInteger() const{
        return value;
    };
    const vector<NestedInteger> &getList() const{
        return sub;
    };
};

class NestedIterator {
private:
    deque<int> deq;
    void append(const vector<NestedInteger> &nestedList){
        for(int i = 0;i < nestedList.size();i++){
            if(nestedList[i].isInteger()){
                deq.push_back(nestedList[i].getInteger());
            }else{
                append(nestedList[i].getList());
            }
        }
    }
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        append(nestedList);
    }

    int next() {
        int res = deq.front();
        deq.pop_front();
        return res;
    }

    bool hasNext() {
        return !deq.empty();
    }
};

class NestedIterator2 {
private:
    vector<int> vals;
    vector<int>::iterator cur;

    void dfs(const vector<NestedInteger> &nestedList) {
        for (auto &nest : nestedList) {
            if (nest.isInteger()) {
                vals.push_back(nest.getInteger());
            } else {
                dfs(nest.getList());
            }
        }
    }

public:
    NestedIterator2(vector<NestedInteger> &nestedList) {
        dfs(nestedList);
        cur = vals.begin();
    }

    int next() {
        return *cur++;
    }

    bool hasNext() {
        return cur != vals.end();
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
    vector<NestedInteger> n1 = {NestedInteger(1),NestedInteger(1)};
    NestedInteger arr1 = NestedInteger(n1);
    NestedInteger n2 = NestedInteger(2);
    vector<NestedInteger> n3 = {NestedInteger(1),NestedInteger(1)};
    NestedInteger arr3 = NestedInteger(n3);
    vector<NestedInteger> narr = {arr1,n2,arr3};
//    NestedInteger arr = NestedInteger(narr);
    vector<int> res;
    //输入：nestedList = [[1,1],2,[1,1]]
    //输出：[1,1,2,1,1]
    //输入：nestedList = [1,[4,[6]]]
    //输出：[1,4,6]
    NestedIterator nestedIterator = NestedIterator(narr);
    while(nestedIterator.hasNext()){
        res.push_back(nestedIterator.next());
    }
    printVec(res);
    //[1,1,2,1,1]
}


