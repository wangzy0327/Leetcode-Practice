import java.util.Arrays;
import java.util.PriorityQueue;

public class leetcode_1005 {
    /**
     * 贪心的思路：局部最优可以推出全局最优
     *           让绝对值大的负数变成正数，当前数值达到最大，整个数组和达到最大
     *
     *           如果将负数都转变成正数了，k值依然大于0，此时的问题是一个有序的正整数序列，如何转变k次正负，让数组和达到最大
     *           又是一个贪心：找到最小的正整数进行反转，当前数值可以达到最大
     *
     * 解题步骤：
     * 1、将数组按照绝对值从大到小排序，注意按照绝对值大小 从大到小排序
     * 2、从前向后遍历，遇到负值转为正数，同时k--
     * 3、如果k还大于0，则反复转变数值最小的元素，将k用完
     * 4、求和
     *
     */
    class Solution {
        public int largestSumAfterKNegations(int[] nums, int k) {
            Integer[] newNums = new Integer[nums.length];
            for(int i = 0; i < nums.length ; i++)
                newNums[i] = nums[i];
            //step 1 从大到小排序
            Arrays.sort(newNums,(a,b)-> (int)(Math.abs((double)b) - Math.abs((double)a)) );
            int res = 0;
            //step 2
            for(int i = 0;i < newNums.length;i++){
                if(k > 0 && newNums[i] < 0) {
                    newNums[i] = -newNums[i];
                    k--;
                }
            }
            //step 3
            if(k % 2 == 1) newNums[newNums.length - 1] *= -1;
            //step 4
            for(Integer ele : newNums)
                res += ele.intValue();
            return res;
        }
    }

    /**
     * 采用优先队列 来处理 时间复杂度 O(nlogk)
     */
    class Solution2 {
        public int largestSumAfterKNegations(int[] nums, int k) {
            Integer[] newNums = new Integer[nums.length];
            for(int i = 0; i < nums.length ; i++)
                newNums[i] = nums[i];
            //大顶堆 记录最小的一批值  将最小的一批值按照从大到小排序
            PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a,b)-> b - a);
            //小顶堆 将最小的一批值 按照 从小到大排序
            PriorityQueue<Integer> minHeap = new PriorityQueue<>();
            int sum = 0;
            //记录最小的绝对值
            int min_abs = Integer.MAX_VALUE;
            //防止k 大于 nums的长度产生越界
            int sz = Math.min(nums.length,k);
            for(Integer each : newNums){
                sum += each.intValue();
                if(Math.abs(min_abs) > Math.abs(each))
                    min_abs = each;
                if(maxHeap.size() == sz && maxHeap.peek() > each){
                    maxHeap.poll();
                    maxHeap.offer(each);
                }else if(maxHeap.size() < sz){
                    maxHeap.offer(each);
                }
            }
            for(int i = 0;i < sz;i++){
                minHeap.offer(maxHeap.peek());
                maxHeap.poll();
            }
            int preTop = 0;
            while(sz > 0){
                int t = minHeap.peek();
                if(t < 0){
                    sum -= 2*t;
                    preTop = minHeap.peek();
                    minHeap.poll();
                    sz--;
                    k--;
                }else
                    break;
            }
            //说明还有剩余k
            int _k = (k == 0)?sz:k;
            if(_k > 0){
                //需要注意的是，在之前将负数修改为正数的过程中，可能出现了（相较于原始数组中最小的正数）更小的正数，这一点不能忽略
                min_abs = (Math.abs(preTop) == Math.abs(min_abs))?Math.abs(preTop):min_abs;
                if(_k%2 == 1 && min_abs > 0)
                    sum -= 2*min_abs;
                if(_k%2 == 0 && min_abs < 0)
                    sum += 2*min_abs;
            }
            return sum;
        }
    }

    public static void main(String[] args) {
//        Solution solution = new leetcode_1005().new Solution();
        Solution2 solution = new leetcode_1005().new Solution2();
//        int[] nums = new int[]{8,-7,-3,-9,1,9,-6,-9,3};
//        int k = 8;
//        int[] nums = new int[]{-2,5,0,2,-2};
//        int k = 3;
//        int[] nums = new int[]{-4,-2,-3};
//        int k = 4;
        int[] nums = new int[]{2,-3,-1,5,-4};
        int k = 2;
        int res = solution.largestSumAfterKNegations(nums,k);
        System.out.println(res);
        //result
        //53
    }
}
