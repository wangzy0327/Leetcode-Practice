public class leetcode_0198 {
    class Solution {
        public int rob(int[] nums) {
            //思路：动态规划，由于都是非负整数，且不能相邻取数
            //用 dp[i] 表示前 i间房屋能偷窃到的最高总金额
            //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
            //最简单的情况，只有一间房dp[i] = nums[0];
            if(nums.length == 1)
                return nums[0];
            //dp[i-2]
            int prevv = 0;
            //dp[i-1]
            int prev = nums[0];
            //dp[i]
            int dp = 0;
            for(int i = 1;i < nums.length;i++){
                //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
                dp = Math.max(prevv+nums[i],prev);
                //更新下一个dp[i-2] 为当前dp[i-1]
                prevv = prev;
                //更新下一个dp[i-1] 为当前dp[i]
                prev = dp;
            }
            return dp;

        }
    }

    public static void main(String[] args) {
        leetcode_0198.Solution solution = new leetcode_0198().new Solution();
        int[] nums = {2,7,9,3,1};
        //result
        //12
        //偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)
        //偷窃到的最高金额 = 2 + 9 + 1 = 12
//    int[] nums = {1,2,3,1};
        //result
        //4
        //偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)
        //偷窃到的最高金额 = 1 + 3 = 4
        System.out.println(solution.rob(nums));
    }
}
