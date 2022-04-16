import java.util.Arrays;

public class leetcode_0016 {
    class Solution {
        public int threeSumClosest(int[] nums, int target) {
            //思路：先排序，然后用双指针进行寻找
            Arrays.sort(nums);
            ans = Integer.MAX_VALUE;
            for(int i = 0;i < nums.length;i++){
                if(ans == 0)
                    return minSum;
                else
                    dfs(nums,target,nums[i],i+1,nums.length-1);
            }
            return minSum;
        }
        private int ans;
        private int minSum;
        private void dfs(int[] nums,int target,int num,int start,int end){
            while(start < end){
                int sum = num + nums[start] + nums[end];
                if(Math.abs(sum - target) < ans){
                    ans = Math.abs(sum - target);
                    minSum = sum;
                }
                if(sum <= target){
                    start++;
                }else{
                    end--;
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0016.Solution solution = new leetcode_0016().new Solution();
        int[] nums = {0,0,1,2,1,3};
        int target = 1;
        int res = solution.threeSumClosest(nums, target);
        System.out.println(res);
        //result
        //与target最接近的和是 1 (0,0,1)
        //1
    }
}
