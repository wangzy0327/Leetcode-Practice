import java.util.Arrays;

public class leetcode_0312 {
    class Solution {
        public int maxCoins(int[] nums) {
            //思路：可以通过给边界两边补充nums[-1]=1,nums[n]=1,可以认为是“虚拟气球”
            //首先可以想到极限状态下，只有一个气球的话, 1*nums[i]*1
            //题目可以改变为，在nums中，戳破气球0到气球n+1中间的所有气球（不包括0和n+1）
            //使得最终只剩下0和n+1气球，最多能得到多少分
            //定义数组dp[i][j] 表示 (i,j) 戳破开区间所有气球，可以获得的最高分数x
            //初始状态dp[i][j] = 0,其中0<=i<=n+1,j <= i+1
            //状态转移方程dp[i][j] = max(dp[i][k]+nums[k]*nums[i]*nums[j]+dp[k][j])
            //k表示最后戳破第k个气球,在戳破气球中选择最多可以得到多少分
            //由于k>=i,k<=j ,所以状态转移方程是从左往右，从下往上
            int n = nums.length;
            int[] scores = new int[n+2];
            //初始化边界
            scores[0] = 1;scores[n+1] = 1;
            for(int i = 0;i < n;i++)
                scores[i+1] = nums[i];
            int[][] dp = new int[n+2][n+2];
            for(int i = 0;i < dp.length;i++)
                Arrays.fill(dp[i],0);
            for(int i = n;i >= 0;i--){
                for(int j = i+1;j <= n+1;j++){
                    //找寻最后一个戳破的气球
                    for(int k = i+1;k < j;k++)
                        dp[i][j] = Math.max(dp[i][j],dp[i][k]+scores[k]*scores[i]*scores[j]+dp[k][j]);
                }
            }
            return dp[0][n+1];
        }
    }
    public static void main(String[] args) {
        leetcode_0312.Solution solution = new leetcode_0312().new Solution();
        int[] nums = {3,1,5,8};
        //result
        //167
        //nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
        //coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
        System.out.println(solution.maxCoins(nums));
    }
}
