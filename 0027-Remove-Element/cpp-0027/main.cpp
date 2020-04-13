class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for(int i = 0;i < nums.size();i++){
            if( val != nums[i] ){
                nums[k++] = nums[i];
            }
        }
        return k;
    }
};

int main() {

    vector<int> nums = {3, 2, 2, 3};
    int val = 3;

    cout << Solution().removeElement(nums, val) << endl;

    return 0;
}