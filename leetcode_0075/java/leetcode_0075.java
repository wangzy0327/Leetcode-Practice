import java.util.Arrays;

public class leetcode_0075 {
    class Solution {
        public void sortColors(int[] nums) {
            //由于只含有三个元素
            //采用三路快排的思想 遍历一遍完成排序
            //[start,l] == 0 [l+1,lt)==1 [r,end]==2
            //start==0 end==nums.size()-1
            int l = -1,r = nums.length;
            int lt = 0;
            int v = 1;
            while(lt < r){
                if(nums[lt]<v)
                    swap(nums,++l,lt++);
                else if(nums[lt]==v)
                    lt++;
                else if(nums[lt]>v)
                    swap(nums,lt,--r);
            }
        }
        private void swap(int[] nums,int idx1,int idx2){
            int tmp = nums[idx1];
            nums[idx1] = nums[idx2];
            nums[idx2] = tmp;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0075().new Solution();
        int[] nums = {2,0,2,1,1,0};
        System.out.println(Arrays.toString(nums));
        solution.sortColors(nums);
        System.out.println(Arrays.toString(nums));
        //result
        //[0,0,1,1,2,2]
    }
}
