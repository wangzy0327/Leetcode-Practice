import java.lang.reflect.Array;
import java.util.Arrays;

public class Solution {
    public void moveZeroes(int[] nums) {
        int k = 0;  // [0,k)非零元素
        for(int i = 0;i < nums.length;i++){
            if(nums[i]!=0){
                if ( i != k ){
                    int tmp = nums[k];
                    nums[k++] = nums[i];
                    nums[i] = tmp;
                }
                else
                    k++;
            }
        }
    }

    public static void main(String[] args) {
        int[] nums = {0,1,0,3,12};
        new Solution().moveZeroes(nums);
        System.out.println(Arrays.toString(nums));
    }
}