import java.util.Arrays;
import java.util.Comparator;

public class leetcode_0354 {
    class Solution {
        public int maxEnvelopes(int[][] envelopes) {
            //思路1:自定义排序+动态规划
            //思路2:自定义排序+贪心算法(二分查找)
            //首先会想到先进行信封排序 (排序规则将宽相同的高度高的排在前面，宽度小的排在前面)
            //这样的排序保证了 排在后面的信封只要高度比前面高度高，则一定可以嵌套前面的信封
            //排序过后就是找 信封嵌套数量dp[j]
            //重叠子问题:信封嵌套数量
            //初始Base:dp[0] = 1
            //状态为: 排序后的信封高度数组值大小 nums[i]
            //状态转移方程: dp[i] = max(dp[i],dp[j] + 1) | {j<i && nums[i]>nums[j] }
            //排序envelopes
            Arrays.sort(envelopes, new Comparator<int[]>() {
                @Override
                public int compare(int[] o1, int[] o2) {
                    return o1[0] == o2[0]?o2[1]-o1[1]:o1[0] - o2[0];
                }
            });
            Arrays.sort(envelopes,(int[] o1,int[] o2) -> o1[0] == o2[0]?o2[1]-o1[1]:o1[0] - o2[0]);
            int sz = envelopes.length;
            int[] nums = new int[sz];
            for(int i = 0;i < nums.length;i++)
                nums[i] = envelopes[i][1];
            return lengthOfEnv2(nums);
        }
        //Time of Exceeded
        private int lengthOfEnv(int[] nums){
            int[] dp = new int[nums.length];
            for(int i = 0;i < dp.length;i++)
                dp[i] = 1;
            int res = 1;
            for(int i = 0;i < dp.length;i++){
                for(int j = 0;j < i;j++){
                    if(nums[j] < nums[i]){
                        dp[i] = Math.max(dp[i],dp[j]+1);
                        res = Math.max(res,dp[i]);
                    }
                }
            }
            return res;
        }
        //贪心算法：保证每个信封个数，对应着最小的信封高度
        //最终可以放置的信封piles堆数
        //top用来存储嵌套数量n的最小元素,索引为嵌套数量
        //使用二分搜索来完成搜索 前面大于nums的元素
        private int lengthOfEnv2(int[] nums){
            int[] top = new int[nums.length];
            //堆数
            int piles = 0;
            for(int i = 0;i < nums.length;i++){
                int left = 0;int right = piles;
                //寻找第一个大于或等于待放元素的位置，摞在其上面
                //二分查找调出条件 left == right [left,right)
                while(left < right){
                    int mid = left + (right - left)/2;
                    if(top[mid] < nums[i]){
                        left = mid + 1;
                    }else{
                        //top[mid] >= nums[i]
                        right = mid;
                    }
                }
                //如果在指定区间没找到大于或等于其元素放置的位置则在后面新建
                if(left == piles)
                    piles++;
                top[left] = nums[i];
            }
            return piles;
        }
    }
    public static void main(String[] args) {
        leetcode_0354.Solution solution = new leetcode_0354().new Solution();
        int[][] envelopes = {
                {6,4},
                {6,5}
                //result
                //1
//                {5,4},
//                {6,4},
//                {6,7},
//                {2,3}
        };
        System.out.println(solution.maxEnvelopes(envelopes));
        //result
        //3 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]
    }
}
