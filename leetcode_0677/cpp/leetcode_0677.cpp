//
// Created by wzy on 2022/4/24.
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

struct Node{
    char ch;
    int val;
    vector<Node*> nexts;
    Node(char ch):ch(ch),val(0),nexts(vector<Node*>(26,nullptr)){};
    Node(char ch,int val):ch(ch),val(val),nexts(vector<Node*>(26,nullptr)){};
};
class MapSum {
public:
    MapSum() {
        //思路：前缀树
        //使用虚拟头节点来存储前一个节点，来对接下来要判断的节点进行判定
        dummyHead = new Node(' ');
    }
    ~MapSum() = default;
    void insert(string key, int val) {
        Node* cur = dummyHead;
        for(int i = 0;i < key.size();i++){
            int num = key[i] - 'a';
            if(!cur->nexts[num]){
                cur->nexts[num] = new Node(key[i]);
            }
            cur = cur->nexts[num];
            //如果是最后一个值则设置
            if(i == key.size()-1)
                cur->val = val;
        }
    }

    int sum(string prefix) {
        int ans = 0;
        Node* cur = dummyHead;
        //找到对应前缀的节点，如果没找到则直接返回0
        for(int i = 0;i < prefix.size();i++){
            int num = prefix[i] - 'a';
            if(!cur->nexts[num])
                return ans;
            else
                cur = cur->nexts[num];
        }
        //找到后回溯dfs 节点找到前缀和
        return dfs(cur);
    }
private:
    Node* dummyHead;
    int dfs(Node* node){
        Node* cur = node;
        int ans = cur->val;
        for(int i = 0;i < 26;i++){
            Node* next = cur->nexts[i];
            if(next)
                ans += dfs(next);
        }
        return ans;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */

int main(){
    MapSum* mapSum = new MapSum();
    mapSum->insert("apple",3);
    cout<<mapSum->sum("ap")<<endl;
    //返回 3 (apple = 3)
    mapSum->insert("app",2);
    cout<<mapSum->sum("ap")<<endl;
    //返回 5 (apple + app = 3 + 2 = 5)
}