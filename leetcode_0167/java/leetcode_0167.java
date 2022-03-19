import java.util.Arrays;

public class leetcode_0167 {
    class Solution {
        public int[] twoSum(int[] numbers, int target) {
            int left = 0;
            int right = numbers.length - 1;
            int sum = 0;
            while(left < right){
                sum = numbers[left] + numbers[right];
                if(sum == target){
                    return new int[]{left+1,right+1};
                }else if(sum < target){
                    left++;
                }else{
                    right--;
                }
            }
            return new int[]{-1,-1};
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0167().new Solution();
        int[] numbers = new int[]{2,7,11,15};
        int target = 9;
        System.out.println(Arrays.toString(solution.twoSum(numbers, target)));
        //result
        //下标从1 开始 [1,2]

    }
}
