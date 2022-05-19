import java.util.Arrays;
import java.util.List;

public class leetcode_0494 {
    class Solution {
        public int findTargetSumWays(int[] nums, int target) {
            //思路：重叠子结构
            //记录 表达式累加和结果 如果到最后达到target则表达式数目+1
            //如果前面 子表达式(1...i)的累加和集合 X , 第i+1个数字为y,目标为target
            //则dp(i)代表前i个表达式的累加和等于target的数量
            //状态转移方程:dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
            //初始状态: dp(0,0) = 1 没有元素时,只取0个元素,得到的值为0
            //由于nums个数字能够达到的最大数字为 nums均为正数，最小数字为 nums均为负数

            int max_target = 0;
            for(int ele:nums)
                max_target += ele;

            //target 大于最大范围 则取不到 直接返回0
            if(Math.abs(target) > Math.abs(max_target))
                return 0;

            int n = nums.length;
            //二维数组的区间列
            int col = 2*max_target+1;
            //dp[i][target] target的范围从[-max_target,max_target] 包括0
            //需要整体向右扩展 2*max_target+1
            int[][] dp = new int[n+1][col+1];
            //状态压缩 由于 只与上一行有关

            //dp[i][max_target + 1] 相当于dp[i][0]
            //初始化 dp(1,nums[0]) dp(1,-nums[0])
            dp[0][max_target+1] = 1;
            for(int i = 1;i <= n;i++){
                for(int j = 1;j <= col;j++){
                    //dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
                    //二维数组 索引边界 [1,max_target*2+1]
                    //超出索引边界就取0索引 0索引列的值为0
                    int left = (j-nums[i-1] >= 1)?j-nums[i-1]:0;
                    int right = (j+nums[i-1] <= col)?(j+nums[i-1]):0;
                    dp[i][j] = dp[i-1][left]+dp[i-1][right];
                }
                Arrays.toString(dp[i]);
            }
            return dp[n][target+max_target+1];
        }
        public int findTargetSumWays2(int[] nums, int target) {
            //思路：重叠子结构
            //记录 表达式累加和结果 如果到最后达到target则表达式数目+1
            //如果前面 子表达式(1...i)的累加和集合 X , 第i+1个数字为y,目标为target
            //则dp(i)代表前i个表达式的累加和等于target的数量
            //状态转移方程:dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
            //初始状态: dp(0,0) = 1 没有元素时,只取0个元素,得到的值为0
            //由于nums个数字能够达到的最大数字为 nums均为正数，最小数字为 nums均为负数

            int max_target = 0;
            for(int ele:nums)
                max_target += ele;

            //target 大于最大范围 则取不到 直接返回0
            if(Math.abs(target) > Math.abs(max_target))
                return 0;

            int n = nums.length;
            //二维数组的区间列
            int col = 2*max_target+1;
            //dp[i][target] target的范围从[-max_target,max_target] 包括0
            //需要整体向右扩展 2*max_target+1
//            int[][] dp = new int[n+1][col+1];
            //状态压缩 由于 只与上一行有关
            int[] dp = new int[col+1];
            //上一行
            int[] prev = new int[col+1];
            //dp[i][max_target + 1] 相当于dp[i][0]
            //初始化 dp(1,nums[0]) dp(1,-nums[0])
//            dp[0][max_target+1] = 1;
            prev[max_target+1] = 1;
            for(int i = 1;i <= n;i++){
                for(int j = 1;j <= col;j++){
                    //dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
                    //二维数组 索引边界 [1,max_target*2+1]
                    //超出索引边界就取0索引 0索引列的值为0
                    int left = (j-nums[i-1] >= 1)?j-nums[i-1]:0;
                    int right = (j+nums[i-1] <= col)?(j+nums[i-1]):0;
//                    dp[i][j] = dp[i-1][left]+dp[i-1][right];
                    dp[j] = prev[left] + prev[right];
                }
                int[] tmp = prev;
                //将dp赋值给prev
//                prev = Arrays.copyOf(dp,col+1);
                prev = dp;
                //dp置为0
                Arrays.fill(tmp,0);
                dp = tmp;
                Arrays.toString(prev);
            }
//            return dp[n][target+max_target+1];
            return prev[target+max_target+1];
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
    }
    public static void main(String[] args) {
        leetcode_0494.Solution solution = new leetcode_0494().new Solution();
        int[] nums = {1,1,1,1,1};
        int target = 3;
        //result
        //5
        /**
         * 一共有 5 种方法让最终目标和为 3
         -1 + 1 + 1 + 1 + 1 = 3
         +1 - 1 + 1 + 1 + 1 = 3
         +1 + 1 - 1 + 1 + 1 = 3
         +1 + 1 + 1 - 1 + 1 = 3
         +1 + 1 + 1 + 1 - 1 = 3

         状态转移数组
         [0,0,0,0,0,1,0,1,0,0,0,0]
         [0,0,0,0,1,0,2,0,1,0,0,0]
         [0,0,0,1,0,3,0,3,0,1,0,0]
         [0,0,1,0,4,0,6,0,4,0,1,0]
         [0,1,0,5,0,10,0,10,0,5,0,1]
         *
         */
//        System.out.println(solution.findTargetSumWays(nums, target));
        System.out.println(solution.findTargetSumWays2(nums, target));
    }
}
