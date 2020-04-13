public class Solution {
    public int removeDuplicates(int[] nums) {
        if(nums.length == 0)
            return 0;
        int k = 1;
        //[0,k) not duplicates array
        for(int i = 1;i < nums.length;i++)
            if(nums[i] != nums[i-1])
                nums[k++] = nums[i];
        return k;
    }
	public static void main(String[] args) {
        int[] nums = {1,1,2};
        new Solution().removeDuplicates(nums,val);
    }
}