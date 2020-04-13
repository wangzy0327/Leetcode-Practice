class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        int k = 1;
        //[0,k) not duplicates array [k,i) duplicates array
        for(int i = 1;i < nums.size();i++)
            if(nums[i] != nums[i-1])
                nums[k++] = nums[i];
        return k;
    }
};

void print_vec(const vector<int>& vec){
    for(int e: vec)
        cout << e << " ";
    cout << endl;
}
int main() {

    vector<int> nums = {1,1,2};
    Solution().removeDuplicates(nums);
    return 0;
}