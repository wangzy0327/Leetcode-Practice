public class leetcode_0300 {
    class Solution {
        public int lengthOfLIS(int[] nums) {
            //错误思路：使用栈来存储记录每个子序列长度
            //可能会出现递减导致不是以i开始的最长子序列
            //ep:[0,1,0,3,2,3] 本来以0开始的最长子序列应该为[0,1,2,3],但是由于有3则会导致最后统计出现[0,1,3]不是最长子序列

            //思路：
            //由于题目要求 求最值问题，可考虑使用动态规划
            //针对i位置元素的状态可以记录为以nums[i]结尾的最长递增子序列长度为dp[i]
            //最重要的就是找出状态转移方程
            //可知每个位置的状态定义：以nums[i]结尾的最长递增子序列
            //状态转移方程
            //dp[i]=max(dp[j])+1,其中0≤j<i且num[j]<num[i]

            int[] dp = new int[nums.length];
            for(int i = 0;i < dp.length;i++)
                dp[i] = 1;
            //最长递增子序列最小为1
            int maxLen = 1;
            for(int i = 1;i < dp.length;i++){
                for(int j = 0;j < i;j++){
                    if(nums[j] < nums[i])
                        dp[i] = Math.max(dp[i],dp[j]+1);
                }
            }
            for(int i = 0;i < dp.length;i++)
                maxLen = Math.max(maxLen,dp[i]);
            return maxLen;
        }
    }
    public static void main(String[] args) {
        int[] nums = {0,1,0,3,2,3};
        //result 4  [0,1,2,3]
//    int[] nums = {10,9,2,5,3,7,101,18};
        //result 4  [2,3,7,101]
//    int[] nums = {7,7,7,7,7,7,7};
        //result 1
        leetcode_0300.Solution solution = new leetcode_0300().new Solution();
        System.out.println(solution.lengthOfLIS(nums));
    }
}
