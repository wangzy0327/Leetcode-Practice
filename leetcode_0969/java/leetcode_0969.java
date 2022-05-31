import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class leetcode_0969 {
    class Solution {
        public List<Integer> pancakeSort(int[] arr) {
            //思路：理解题意 arr[i]的范围在1...arr.length之间 翻转操作符合递归性质
            //使用翻转的方式对arr[0...n-1]进行排序，关键点在于每轮递归需要将最大的元素arr[n-1]
            //放在数组的最后，然后递归向前排序arr[0...n-2]
            //如何才能将当前寻找数组arr[0...k-1]的最大值放在末尾
            //那就是如果当前值不在数组最后假设在i-1位置，则翻转前i个位置，将原i位置的翻转到了0的位置
            //接着翻转前k个元素，将最大值放在k-1的位置上，本轮递归结束
            int n = arr.length;
            res = new ArrayList();
            pancakeHelper(arr,n);
            return res;
        }
        private List<Integer> res;
        private void pancakeHelper(int[] arr,int k){
            if(k > 1){
                int idx = k - 1;
                while(arr[idx] != k)
                    idx--;
                if(idx == k - 1)
                    pancakeHelper(arr,k-1);
                else{
                    //不在首位
                    if(idx != 0){
                        rotate(arr,idx+1);
                        res.add(idx+1);
                    }
                    //在首位的话直接翻转k
                    rotate(arr,k);
                    res.add(k);
                    pancakeHelper(arr,k-1);
                }
            }
        }
        private void rotate(int[] arr,int m){
            int l = 0;
            int r = m - 1;
            while(l < r){
                int tmp = arr[l];
                arr[l++] = arr[r];
                arr[r--] = tmp;
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0969.Solution solution = new leetcode_0969().new Solution();
        int[] arr = {3,2,4,1};
        //result
        //[4,2,4,3]
        //我们执行 4 次煎饼翻转，k 值分别为 4，2，4，和 3。
        //初始状态 arr = [3, 2, 4, 1]
        //第一次翻转后（k = 4）：arr = [1, 4, 2, 3]
        //第二次翻转后（k = 2）：arr = [4, 1, 2, 3]
        //第三次翻转后（k = 4）：arr = [3, 2, 1, 4]
        //第四次翻转后（k = 3）：arr = [1, 2, 3, 4]，此时已完成排序

        //[3,4,2,3,2]
        //初始状态 arr = [3, 2, 4, 1]
        //第一次翻转后（k = 3）：arr = [4,2,3,1] 将最大值放在首位
        //第二次翻转后 (k = 4): arr = [1,3,2,4] 将最大值放在末尾 接着递归向下
        //第三次翻转后 (k = 2): arr = [3,1,2,4] 将次最大值放在首位
        //第四次翻转后 (k = 3): arr = [2,1,3,4] 将次最大值放在倒二末尾
        //第五次翻转后 (k = 2): arr = [1,2,3,4] 将2放在指定位置
        List<Integer> res = solution.pancakeSort(arr);
        System.out.println(Arrays.toString(res.toArray(new Integer[0])));
    }
}
