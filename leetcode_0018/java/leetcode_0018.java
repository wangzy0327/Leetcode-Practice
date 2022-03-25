import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0018 {
    class Solution {
        public List<List<Integer>> fourSum(int[] nums, int target) {
            //暴力解法是 O(n^4)
            //这里先排序O(nlogn)，然后再根据双指针找到合适的组合 O(n^3)
            List<List<Integer>> res = new LinkedList();
            LinkedList<Integer> sub = new LinkedList();
            //1.排序
            Arrays.sort(nums);
            for(int i = 0;i < nums.length;i++){
                //去除重复元素
                if(i == 0 || nums[i] != nums[i-1]){
                    for(int j = i+1;j < nums.length;j++){
                        //去除重复元素
                        if(j == i+1 || nums[j] != nums[j-1]){
                            sub.clear();
                            sub.add(nums[i]);
                            sub.add(nums[j]);
                            bfs(res,sub,target-nums[i]-nums[j],nums,j+1,nums.length - 1);
                        }
                    }
                }
            }
            return res;
        }
        private void bfs(List<List<Integer>> res,LinkedList<Integer> sub,int target,int[] nums,int start,int end){
            while(start < end){
                if(nums[start] + nums[end] > target)
                    end--;
                else if(nums[start] + nums[end] < target)
                    start++;
                else{
                    sub.add(nums[start]);
                    sub.add(nums[end]);
                    res.add(new LinkedList(sub));
                    sub.removeLast();
                    sub.removeLast();
                    while(start < end && nums[start] == nums[start+1])
                        start++;
                    start++;
                    while(start < end && nums[end] == nums[end-1])
                        end--;
                    end--;
                }
            }
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0018().new Solution();
//        int[] nums = {1,0,-1,0,-2,2};
//        int target = 0;
        //result
        //[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
        int[] nums = {-2,-1,-1,1,1,2,2};
        int target = 0;
        //result
        //[[-2,-1,1,2],[-1,-1,1,1]]
        // int[] nums = {2,2,2,2,2};
        // int target = 8;
        //result
        //[[2,2,2,2]]
        List<List<Integer>> res = solution.fourSum(nums,target);
        for(int i = 0;i < res.size();i++){
            if(i == res.size() - 1){
                if(i == 0)
                    System.out.printf("[ ");
                System.out.println(Arrays.toString(res.get(i).toArray(Integer[]::new))+" ] ");
            }else{
                if(i == 0)
                    System.out.printf("[ ");
                System.out.printf(Arrays.toString(res.get(i).toArray(Integer[]::new))+" , ");
            }
        }
    }
}
