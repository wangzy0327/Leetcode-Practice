import java.util.Arrays;
import java.util.List;

public class leetcode_0309 {
    class Solution {
        public int maxProfit(int[] prices) {
            //思路：采用动态规划
            //分析题意能得出 第i天的交易状态有三种，持有股票，卖出股票且不含有股票，不操作且不含有股票(包括冷冻)
            //i天最大利润 状态转移方程 跟i-1天在持有股票，卖出股票且不含有股票，不操作且不含有股票三种状态下的最大利润相关
            //所以用二维数组来标识 第i天的状态 0表示持有股票，1表示不操作 , 2表示卖出
            //如果第i天持有股票，说明前一天必须是不操作状态(包含冷冻且不能重复买入)，否则不能买入,或者i-1天就持有股票
            // dp(i,0) = max(dp(i-1,1)-prices[i-1],dp(i-1,0))
            //如果第i天不操作且不含有股票, 说明要么是最大利润为前一天不操作，要么是前一天卖出，二者的最大值
            // dp(i,1) = max(dp(i-1,1),dp(i-1,2))
            //如果第i天卖出股票且不含有股票，说明最大利润必定为 前一天持有股票
            //dp(i,2) = dp(i-1,0) + prices[i-1]
            //初始状态 dp(1,0) = -prices[0], dp(1,1) = 0,dp(1,2) = 0

            //i天能达到的最大利润，则第i天的状态只能是冷冻期或者卖出，不可能是买入

            //由于dp只与上一行的状态相关,所以状态压缩只需要保留上一行的0,1,2 三个状态

            int n = prices.length;
            int[][] dp = new int[n+1][3];
            dp[1][0] = -prices[0];dp[1][1] = 0;dp[1][2] = 0;
            for(int i = 2;i <= n;i++){
                dp[i][0] = Math.max(dp[i-1][1] - prices[i-1],dp[i-1][0]);
                dp[i][1] = Math.max(dp[i-1][1],dp[i-1][2]);
                dp[i][2] = dp[i-1][0] + prices[i-1];
            }
            //打印状态表
            /**
             *
             [-1,0,0]
             [-1,0,1]
             [-1,1,2]
             [1,2,-1]
             [1,2,3]
             *
             */
            for(int i = 1;i <= n;i++)
                Arrays.toString(dp[i]);
            return Math.max(dp[n][1],dp[n][2]);
        }
    }
    public <T> void printListArr(List<List<T>> list) {
        for (int i = 0; i < list.size(); i++) {
            if (i == list.size() - 1) {
                if (i == 0)
                    System.out.printf("[ ");
                System.out.println(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " ] ");
            } else {
                if (i == 0)
                    System.out.printf("[ ");
                System.out.printf(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " , ");
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0309.Solution solution = new leetcode_0309().new Solution();
        int[] prices = {1,2,3,0,2};
        //result
        //3
        //对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
//    int[] prices = {1,2,4};
        //result
        //3
        //对应的交易状态:[买入，不操作，卖出]
        System.out.println(solution.maxProfit(prices));
    }
}
