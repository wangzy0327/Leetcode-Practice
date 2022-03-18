import java.util.Arrays;

public class leetcode_0034 {
    class Solution {
        public int[] searchRange(int[] nums, int target) {
            if(nums.length == 0)
                return new int[]{-1,-1};
            int beginPos = findBeginPos(nums,target);
            int endPos = findEndPos(nums,target);
            if(beginPos < 0 || beginPos >= nums.length || nums[beginPos] != target)
                return new int[]{-1,-1};
            return new int[]{beginPos,endPos};
        }
        private int findBeginPos(int[] nums,int target){
            int left = 0;
            int right = nums.length;
            //[left,right)  退出条件为 left == right
            int mid = 0;
            while(left < right){
                mid = left + (right - left)/2;
                if(nums[mid] == target)
                    right = mid;
                else if(nums[mid] > target)
                    right = mid;
                else if(nums[mid] < target)
                    left = mid + 1;
            }
            return left;
        }
        private int findEndPos(int[] nums,int target){
            int left = 0;
            int right = nums.length;
            //[left,right)  退出条件为 left == right
            int mid = 0;
            while(left < right){
                mid = left + (right - left)/2;
                if(nums[mid] == target)
                    left = mid + 1;
                else if(nums[mid] > target)
                    right = mid;
                else if(nums[mid] < target)
                    left = mid + 1;
            }
            return right - 1;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0034().new Solution();
//        int[] nums = {5,7,7,8,8,10};
//        int target = 8;
        int[] nums = {2,2};
        int target = 3;
        System.out.println(Arrays.toString(solution.searchRange(nums, target)));
    }
}
