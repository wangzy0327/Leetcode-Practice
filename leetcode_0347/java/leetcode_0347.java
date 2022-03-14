import java.util.*;

public class leetcode_0347 {
    class Solution {
        class Pair<K,V>{
            public K key;
            public V value;
            public Pair(K _key,V _value){
                key = _key;
                value = _value;
            }
        }
        public int[] topKFrequent(int[] nums, int k) {
            Map<Integer,Integer> map = new HashMap<Integer,Integer>();
            for(int i = 0;i < nums.length;i++)
                map.put(nums[i],map.getOrDefault(nums[i],0) + 1);
            //Jdk中默认PriorityQueue为小顶堆
            //这里采用小顶堆 ，堆顶为最小的频率
//            new Comparator<>()
            PriorityQueue<Pair<Integer,Integer>> pq = new PriorityQueue<>((Pair<Integer,Integer> o1, Pair<Integer,Integer> o2) -> {return o1.value - o2.value;});
            for(Map.Entry<Integer,Integer> entry : map.entrySet()) {
                if (pq.size() < k) {
                    pq.add(new Pair(entry.getKey(), entry.getValue()));
                } else if (entry.getValue() > pq.peek().value){
                    pq.poll();
                    pq.offer(new Pair<>(entry.getKey(),entry.getValue()));
                }
            }
            int[] res = new int[Math.min(nums.length,k)];
            for(int i = 0;i < res.length;i++)
                res[i] = pq.poll().key;
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0347().new Solution();
        int[] nums = {1,1,1,2,2,3};
        int k = 2;
        int[] res = solution.topKFrequent(nums,k);
        System.out.println(Arrays.toString(res));
    }
}
