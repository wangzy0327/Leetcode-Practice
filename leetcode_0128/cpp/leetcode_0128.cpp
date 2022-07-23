//
// Created by wzy on 2022/3/7.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <climits>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //首先要读懂题意 什么是连续的序列
        // 举栗 [100,4,200,1,3,2] 中 1,2,3,4是连续的整数就是连续序列(不要求它们本身有顺序)
        //每次只有最小的数字 去统计长度，避免中间数字统计，如果遇到前后有连续的数字跳过
        unordered_set<int> record;
        //对元素去重，减少重复元素的判断
        for(auto num : nums)
            record.emplace(num);
        int longSeqLen = 0;
        for(auto num : record){
            //从连续序列最下数值开始，ep[100,4,200,1,3,2] 只从1开始，其他跳过
            //内层循环判断连续序列的长度进行比较
            int curLen = 1;
            if(!record.count(num - 1)){
                for(int j = num + 1;record.count(j);j++)
                    curLen++;
                longSeqLen = max(longSeqLen,curLen);
            }
        }
        return longSeqLen;
    }
};

class Solution2 {
public:
	//不过采用并查集效率不高
    int longestConsecutive(vector<int>& nums) {
        //采用并查集，找出并查集中集合元素最大的集合size即可
        //对于每个元素只需要判断其相邻元素是否在集合中，如果在的话，则直接放入
        //并查集 核心 : 判断连接 与 合并问题
        // ep: [7,9] 8 -> [7,8,9]
        //这里的并查集采用 哈希表来代替数组
        //init parents
        for(auto ele:nums){
            parents[ele] = ele;
            sz[ele] = 1;
        }
        for(auto ele:nums){
            helper(ele,ele-1);
            helper(ele,ele+1);
        }
        return count;
    }
private:
    int count = 0;
    unordered_map<int,int> parents;
    unordered_map<int,int> sz;
    //进行相邻元素 判定 与 合并
    void helper(int ele,int neihbor){
        int rootEle = find(ele);
        if(find(neihbor) != INT_MIN){
            unionElements(ele,neihbor);
            rootEle = find(ele);
        }
        count = max(count,sz[rootEle]);
    }
    //查找根
    int find(int ele){
        //查找压缩
        if(!parents.count(ele))
            return INT_MIN;
        while(parents.count(ele) && parents[ele] != parents[parents[ele]])
            parents[ele] = parents[parents[ele]];
        return parents[ele];
    }
    //判断连接
    bool isConnected(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP != rootQ)
            return false;
        else
            return true;
    }
    //合并集合
    void unionElements(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ)
            return;
        int szP = sz[rootP];
        int szQ = sz[rootQ];
        if(szP < szQ){
            parents[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        }else{
            parents[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
        }
    }
};

int main(int argc,char* argv[]){
    vector<int> nums = {100,4,200,1,3,2};
//    int res = Solution().longestConsecutive(nums);
    int res = Solution2().longestConsecutive(nums);
    cout<<res<<endl;
    //res
    //4
}
