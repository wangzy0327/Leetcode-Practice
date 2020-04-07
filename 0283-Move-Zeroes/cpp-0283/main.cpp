class Solution {
public:
    //时间复杂度O(n)
    //空间复杂度O(1)
    void moveZeroes(vector<int>& nums) {
        int k = 0;  // [0,k)非零元素
        for(int i = 0;i < nums.size();i++){
            if(nums[i]!=0){
                if ( i != k )
                  swap(nums[k++],nums[i]);
                else
                    k++;
            }
        }
    }
};

void print_vec(const vector<int>& vec){
    for(int e: vec)
        cout << e << " ";
    cout << endl;
}
int main() {

    vector<int> nums = {0,1,0,3,12};
    Solution().moveZeroes(nums);
    print_vec(nums);
    return 0;
}