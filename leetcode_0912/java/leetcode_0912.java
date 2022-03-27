import java.util.Arrays;

public class leetcode_0912 {
    public class Solution {
        public int[] sortArray(int[] nums) {
            qSort(nums,0,nums.length-1);
            return nums;
        }
        private void qSort(int[] nums,int start,int end){
            if(start >= end)
                return ;
            int pos = partition(nums,start,end);
            qSort(nums,start,pos-1);
            qSort(nums,pos+1,end);
        }
        private int partition(int[] nums,int start,int end){
            int randIdx = start+(int)(Math.random()*(end-start+1));
            swap(nums,start,randIdx);
            int v = nums[start];
            int l = start + 1;int r = end;
            //nums[start,l)<v   nums(r,end]>v
            while(l <= r){
                while(l<=r && nums[l]<v)
                    l++;
                while(l<=r && nums[r]>v)
                    r--;
                if(l > r)
                    break;
                swap(nums,l++,r--);
            }
            // l = r+1
            swap(nums,start,r);
            return r;
        }
        private void swap(int[] nums,int idx1,int idx2){
            int tmp = nums[idx1];
            nums[idx1] = nums[idx2];
            nums[idx2] = tmp;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0912().new Solution();
        int[] nums = {5,1,1,2,0,0};
        System.out.println(Arrays.toString(nums));
        nums = solution.sortArray(nums);
        System.out.println(Arrays.toString(nums));
        //result
        //[0, 0, 1, 1, 2, 5]
    }
}
