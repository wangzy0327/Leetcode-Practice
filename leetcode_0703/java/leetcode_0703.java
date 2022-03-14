
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

public class leetcode_0703 {
    class KthLargest {
        //创建小顶堆 最小的在堆顶
        private PriorityQueue<Integer> pq;
        private int k;
        public KthLargest(int k, int[] nums) {
            pq = new PriorityQueue();
            this.k = k;
            for(int i = 0;i < nums.length;i++)
                add(nums[i]);
        }

        public int add(int val) {
            if(pq.size() < k)
                pq.offer(val);
            else if(val > pq.peek()){
                pq.poll();
                pq.offer(val);
            }
            return pq.peek();
        }
    }
    public static void main(String[] args) {
        int k = 3;
        int[] nums = {4,5,8,2};
        KthLargest kthLargest = new leetcode_0703().new KthLargest(k, nums);
        List<Integer> res = new LinkedList<>();
        res.add(kthLargest.add(3));
        res.add(kthLargest.add(5));
        res.add(kthLargest.add(10));
        res.add(kthLargest.add((9)));
        res.add(kthLargest.add(4));
        System.out.println(Arrays.toString(res.toArray(Integer[]::new)));
    }
}
