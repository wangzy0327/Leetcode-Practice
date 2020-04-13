public class Solution {
	public int removeElement(int[] nums, int val) {
        int num = 0;
        for(int i = 0;i < nums.length;i++)
            if(val != nums[i]){
                if(nums[i] != val)
                    nums[num++] = nums[i];
            }
        return num;
    }
	public static void main(String[] args) {
        int[] nums = {3, 2, 2, 3};
        int val = 2;
        new Solution().removeElement(nums,val);
    }
}