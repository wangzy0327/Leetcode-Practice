public class leetcode_0287 {
    class Solution {
        public int findDuplicate(int[] nums) {
            int n = nums.length;
            if(n == 0)
                return -1;
            int[] record = new int[n + 1];
            for(int ele : nums){
                if(record[ele] == 0)
                    record[ele] = 1;
                else
                    return ele;
            }
            return -1;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0287().new Solution();
        int[] nums = new int[]{1,3,4,2,2};
        int res = solution.findDuplicate(nums);
        //result
        //2
        System.out.println(res);
    }
}
