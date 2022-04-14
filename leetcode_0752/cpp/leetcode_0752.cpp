//
// Created by wzy on 2022/4/14.
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

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        //思路：广度优先搜索BFS 每次将移动一个拨轮的一位数字所有列举出来入队 旋转次数+1
        //如果队列中出现target则 找到了返回旋转次数
        //如果队列中出现deadends则将其出队并不进行可能出现的下一个拨轮计算
        //直到队列为空，则返回
        deque<string> dq;
        dq.push_back("0000");
        rotate = 0;
        unordered_set<string> s(deadends.begin(),deadends.end());
        //如果死亡数字中含有target,则直接返回-1
        if(s.count(target))
            return -1;
        //如果初始值等于target,则直接返回0
        if(target == "0000")
            return 0;
        bfs(dq,s,target);
        return rotate == 0?-1:rotate;
    }
private:
    int rotate;
    void bfs(deque<string>& dq,unordered_set<string>& deadends,string target){
        while(dq.size()){
            int sz = dq.size();
            for(int i = 0;i < sz;i++){
                string num = dq.front();
                dq.pop_front();
                if(deadends.count(num))
                    continue;
                else if(num == target)
                    return ;
                else{
                    //计算当前数字可能出现的下一批数字并将其入队
                    vector<string> vec = nextNums(num,deadends);
                    for(int i = 0;i < vec.size();i++)
                        dq.push_back(vec[i]);
                    //将遍历过的num加入deadends可防止走回头路
                    deadends.insert(num);
                }
            }
            rotate += 1;
        }
        //队列为空
        //达不到设置为-1
        rotate = -1;
    }
    vector<string> nextNums(string num,unordered_set<string>& deadends){
        //每次改变一位
        vector<string> res;
        for(int i = 0;i < 4;i++){
            string tmp = string(num);
            if(num[i] == '9')
                tmp[i] = '0';
            else
                tmp[i] += 1;
            if(!deadends.count(tmp))
                res.push_back(tmp);
        }
        for(int i = 0;i < 4;i++){
            string tmp = string(num);
            if(num[i] == '9')
                tmp[i] = '0';
            else
                tmp[i] -= 1;
            if(!deadends.count(tmp))
                res.push_back(tmp);
        }
        return res;
    }
};

int main(){
//    vector<string> deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"};
//    string target = "8888";
    //result
    //-1
    //无法旋转到目标数字且不被锁定
    vector<string> deadends = {"0201","0101","0102","1212","2002"};
    string target = "0202";
    //result
    //6
    //可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"
    int res = Solution().openLock(deadends,target);
    cout<<res<<endl;

    return 0;
}