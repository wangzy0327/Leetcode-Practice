public class leetcode_0704 {
    class Solution {
        public int search(int[] nums, int target) {
            int left = 0;
            int right = nums.length - 1;
            while(left <= right){
                //防索引数值超过 整型范围
                int mid = left + (right - left)/2;
                if(nums[mid] == target)
                    return mid;
                else if(nums[mid] < target)
                    left = mid + 1;
                else //nums[mid] > target
                    right = mid - 1;
            }
            return -1;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0704().new Solution();
        int[] nums = {-1,0,3,5,9,12};
        int target = 9;
        System.out.println(solution.search(nums, target));
    }
}
