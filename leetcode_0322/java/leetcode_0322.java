public class leetcode_0322 {
    class Solution {
        public int coinChange(int[] coins, int amount) {
            //思路：动态规划
            //整数amount总金额所需最少的硬币个数，由前面重叠子问题amount-coin[i]所需的硬币个数+1构成
            //dp[i]表示金额i所需最少的硬币个数
            //初始状态 base case dp[0] = 0 不需要硬币就能组成
            //状态转移方程 dp[i] = min(dp[i- coins[j]] + 1) {j -[1,coins.size()] && i - coins[j] >= 0}
            //初始化所有dp为amount+1 硬币数量
            int[] dp = new int[amount+1];
            for(int i = 0;i < dp.length;i++)
                dp[i] = amount + 1;
            //dp[0]
            dp[0] = 0;
            for(int i = 1;i <= amount;i++){
                for(int j = 0;j < coins.length;j++){
                    if(i - coins[j] >= 0)
                        dp[i] = Math.min(dp[i],dp[i - coins[j]]+1);
                }
            }
            return (dp[amount] == amount+1)?-1:dp[amount];
        }
    }
    public static void main(String[] args) {
        leetcode_0322.Solution solution = new leetcode_0322().new Solution();
        int[] coins = {1,2,5};
        int amount = 11;
        //result
        //3
        //11 = 5 + 5 + 1
//        int[] coins = {2};
//        int amount = 3;
        //result
        //-1
        //int[] coins = {2};
        //int amount = 3;
        //result
        //0
        System.out.println(solution.coinChange(coins, amount));
    }
}
