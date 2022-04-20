public class leetcode_0303 {
    class NumArray {
        /*
        思路：由于数组不可变，且需要多次调用索引间的元素和
        使用前缀和进行处理(存储从0索引到指定索引的前缀和)
        */
        public NumArray(int[] nums) {
            //prefix_sum 存储从[0,i]的前缀和
            int sum = 0;
            //初始化
            prefixSum = new int[nums.length];
            for(int i = 0;i < nums.length;i++){
                sum += nums[i];
                prefixSum[i] = sum;
            }
        }

        public int sumRange(int left, int right) {
            //由于包含左右边界 所以左侧需要left-1 , [left,right]
            int pre = (left == 0)?0:prefixSum[left-1];
            return prefixSum[right] - pre;
        }
        private int[] prefixSum;
    }

    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray obj = new NumArray(nums);
     * int param_1 = obj.sumRange(left,right);
     */
    public static void main(String[] args) {
        int[] nums = new int[]{-2, 0, 3, -5, 2, -1};
        leetcode_0303.NumArray numArray = new leetcode_0303().new NumArray(nums);
        int left = 0;int right = 2;
        System.out.println(numArray.sumRange(left, right));
        //result 1
        left = 2;right = 5;
        System.out.println(numArray.sumRange(left, right));
        //result -1
        left = 0;right = 5;
        System.out.println(numArray.sumRange(left, right));
        //result -3
    }
}
