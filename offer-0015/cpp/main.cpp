#include<iostream>

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        uint32_t flag = 1;
        while(flag){
            if(n & flag)
                count++;
            flag = flag<<1;
        }
        return count;
    }
    //右移传入参数有一个好处，如果左边为0就不用继续左移了
    int hammingWeight2(uint32_t n) {
        int count = 0;
        uint32_t flag = 1;
        while(n){
            if(n & flag)
                count++;
            n = n>>1;
        }
        return count;
    }
};

int main(int argc,char* argv[]){
    unsigned int n = 11;
    std::cout<<Solution().hammingWeight2(11)<<std::endl;
    std::cout<<Solution().hammingWeight2(128)<<std::endl;
    std::cout<<Solution().hammingWeight2(4294967293)<<std::endl;
}