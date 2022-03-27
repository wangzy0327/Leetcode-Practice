public class leetcode_0215 {
    public class Solution {
        public int findKthLargest(int[] nums, int k) {
            //快速排序Qsort
            //要寻找位置的索引
            int target = nums.length - k;
            //只要目标target索引位置顺序定好后就可以返回对应元素
            qSortHelper2(nums,target,0,nums.length-1);
            return nums[target];
        }
        private void qSortHelper(int[] nums,int target,int start,int end){
            int pos = partition(nums,start,end);
            if(pos == target){
                return ;
            }else if(pos < target){
                qSortHelper(nums,target,pos+1,end);
            }else{
                //pos > target
                qSortHelper(nums,target,start,pos-1);
            }
        }
        private void qSortHelper2(int[] nums,int target,int start,int end){
            int[] pos = partition2(nums,start,end);
            if(target >= pos[0] && target <= pos[1]){
                return ;
            }else if(pos[1] < target){
                qSortHelper2(nums,target,pos[1]+1,end);
            }else{
                //pos > target
                qSortHelper2(nums,target,start,pos[0]-1);
            }
        }
        //找到对应位置
        private int partition(int[] nums,int start,int end){
            if(start == end)
                return start;
            int rand_idx = start + (int)(Math.random()*(end-start+1));
            swap(nums,start,rand_idx);
            int v = nums[start];
            int l = start + 1;int r = end;
            //nums[start+1,l) < v ,nums(r,end] > v
            while(l<=r){
                while(l<=r && nums[l]<v)
                    l++;
                while(l<=r && nums[r]>v)
                    r--;
                if(l > r)
                    break;
                swap(nums,l++,r--);
            }
            //调出循环的条件 l == r+1 nums[...r,l...]
            swap(nums,start,r);
            return r;
        }
        private int[] partition2(int[] nums,int start,int end){
            if(start == end)
                return new int[]{start,end};
            int rand_idx = start + (int)(Math.random()*(end-start+1));
            swap(nums,start,rand_idx);
            int v = nums[start];
            int l = start;int lt = l+1;int r = end+1;
            //nums[start+1,l] < v nums[l+1,lt) == v,nums[r,end] > v
            while(lt<r){
                if(nums[lt] < v)
                    swap(nums,++l,lt++);
                else if(nums[lt] == v)
                    lt++;
                else if(nums[lt] > v)
                    swap(nums,lt,--r);
            }
            //调出循环的条件 lt == r nums[...lt|r...]
            swap(nums,start,l);
            return new int[]{l,r-1};
        }
        private void swap(int[] nums,int idx1,int idx2){
            int tmp = nums[idx1];
            nums[idx1] = nums[idx2];
            nums[idx2] = tmp;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0215().new Solution();
        int[] nums = {3,2,1,5,6,4};
        int k = 2;
        //result 5
//        int[] nums = {3,2,3,1,2,4,5,5,6};
//        int k = 4;
        //result 4
        int kthLargest = solution.findKthLargest(nums, k);
        System.out.println(kthLargest);
    }
}
