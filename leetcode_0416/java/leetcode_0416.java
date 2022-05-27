public class leetcode_0416 {
    class Solution {
        public boolean canPartition(int[] nums) {
            //思路：背包问题，动态规划
            //将数组划分为两个相等子集，可以通过先求数组的和
            //如果数组的和为奇数，则只包含正整数的非空数组不可能分割成两个相等的子集
            //数组和Sum为偶数的话，其和的一半target即为 从数组中找到集合等于target
            //转化为背包问题，每个数组的数字有两个选择，放进或者不放，背包的和为target
            //状态dp(i,sub_sum) = x 表示对于前i个数字，当容量为sub_sum时，若x为true时，则更好可以将背包装满
            //如果x为false时，则不能将背包装满
            //状态就是 背包的容量和可选择的物品，选择就是放进背包或者不放进背包
            //状态转移 dp(i,sub_sum) = dp(i-1,sub_sum-nums[i-1]) {i不放进背包} || dp(i-1,sub_sum) {i不放进背包}
            //初始状态 base case : dp(...,0) = true (背包容量为0) dp(0,...) = false (没有可选的物品)

            int sum = 0;
            for(int ele:nums)
                sum += ele;
            //如果是奇数直接返回
            if(sum % 2 == 1)
                return false;

            //集合目标target
            int target = sum/2;
            int n = nums.length;
            // boolean[][] dp = new boolean[n+1][target+1];
            // //初始化
            // for(int i = 0;i <= n;i++)
            //     dp[i][0] = true;
            //状态压缩
            boolean[] dp = new boolean[target+1];
            dp[0] = true;

            for(int i = 1;i <= n;i++){
                //每一行只与上一行相关
                //遍历直到背包容量为1
                //由于后面跟上一层的前面相关所以 从后往前遍历
                for(int j = target;j >= 1;j--){
                    if(j - nums[i-1] >= 0)
                        dp[j] = dp[j]||dp[j-nums[i-1]];
                    //j - nums[i-1] < 0 保持与上一行内容不变
                    // else
                    //     dp[i][j] = dp[i-1][j];
                }
            }
            return dp[target];
        }
    }
    public static void main(String[] args) {
        leetcode_0416.Solution solution = new leetcode_0416().new Solution();
        int[] nums = {1,5,11,5};
        //result
        //true
        //数组可以分割成 [1, 5, 5] 和 [11]
        solution.canPartition(nums);
    }
}
