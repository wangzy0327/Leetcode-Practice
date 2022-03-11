//
// Created by wzy on 2022/3/11.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <sstream>

using namespace std;

class ExamRoom {
/**
考场排座的位次本质是要保证 座次的有序集合在有离开后还要保证顺序，以方便有学生能进来坐
这里有序集合能够保证顺序性，所以能够快速插入元素和删除元素 时间复杂度为O(logn),且通过遍历能够确定考生坐的位置
需要注意考虑，左右边界
*/
private:
    int size;
    set<int> tree;
public:
    ExamRoom(int n) {
        this->size = n;
    }

    int seat() {
        //最初学生位置为0
        int stud = 0;
        //如果没有空位置
        if(size <= tree.size())
            return -1;
        //如果tree里面还没有元素，直接返回初始化的stud的0位置
        if(tree.size()){
            //遍历所有已坐位置，找出最大空档，存储位置
            //dist 用来存储最大距离 初始化
            //这里解释一下要把dist设置为tree首个元素的原因
            //如果0位置存在，就是初始化值0
            //如果0位置被移除，则最大间隔就初始化为0到第一个元素的距离
            //否则可能出现0位置被移除，后面的距离都不是最大，而0处漏掉的情况
            int dist = *tree.begin();
            //初始化前一个距离为prev
            int prev = -1;
            for(auto i : tree){
                int d = 0;
                if(prev != -1){
                    d = (i - prev)/2;
                    if(d > dist){
                        stud = prev + d;
                        dist = d;
                    }
                }
                prev = i;
            }
            //判断最右端距离
            if(size - 1 - prev > dist)
                stud = size - 1;
        }
        tree.insert(stud);
        return stud;
    }

    void leave(int p) {
        if(p >= 0 && p < size)
            tree.erase(p);
    }
};

int main(int argc,char* argv[]){
    ExamRoom examRoom(10);
    cout<<examRoom.seat()<<",";
    cout<<examRoom.seat()<<",";
    cout<<examRoom.seat()<<",";
    cout<<examRoom.seat()<<",";
    examRoom.leave(4);
    cout<<examRoom.seat()<<endl;
    //result
    // [0,9,4,2,5]
}

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */