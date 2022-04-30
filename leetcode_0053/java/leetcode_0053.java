public class leetcode_0053 {
    class Solution {
        public int maxSubArray(int[] nums) {
            //思路：设置arr(start,end)为子数组
            //如果arr[start,end]<0,则start++,否则end++,更新最大和
            if(nums.length == 0)
                return 0;
            int max_sum = Integer.MIN_VALUE;
            int sub_arr = nums[0];
            int start = 0;
            int end = 0;
            //[start,end]
            while(start <= end && end < nums.length){
                if(start <= end && sub_arr < 0){
                    max_sum = Math.max(max_sum,sub_arr);
                    sub_arr -= nums[start++];
                    if(start > end ){
                        if(end < nums.length - 1)
                            sub_arr += nums[end+1];
                        end++;
                    }
                }else if(start <= end && sub_arr >= 0){
                    //start <= end && sub_arr >= 0
                    max_sum = Math.max(max_sum,sub_arr);
                    if(end < nums.length - 1)
                        sub_arr += nums[++end];
                    else
                        end++;
                }
            }
            return max_sum;
        }
        public int maxSubArray2(int[] nums) {
            //思路：动态规划
            //假设nums的长度为n,下标从0到n-1
            //我们用 f(i)代表以第 i 个数结尾的「连续子数组的最大和」
            //我们要求的答案就是 max{f(i)} 0<i<n-1
            //如何求出f(i) = max{f(i-1)+nums[i] | nums[i]}
            //即如果f(i-1)为负,则f(i) = nums[i] 否则f(i) = f(i-1)+nums[i]
            //因为f(i)只跟f(i-1)有关，则可以用pre来存储f(i-1)
            if(nums.length == 0)
                return 0;
            int pre = 0;
            int maxSum = nums[0];
            for(int ele:nums){
                pre = Math.max(pre+ele,ele);
                maxSum = Math.max(maxSum,pre);
            }
            return maxSum;
        }
    }
    public static void main(String[] args) {
        leetcode_0053.Solution solution = new leetcode_0053().new Solution();
        int[] nums = {-2,1,-3,4,-1,2,1,-5,4};
        //result
        //6 最大子数组 {4,-1,2,1}
//        int[] nums = {1};
        //result
        //1 最大子数组 {1}
        System.out.println(solution.maxSubArray2(nums));
    }
}
