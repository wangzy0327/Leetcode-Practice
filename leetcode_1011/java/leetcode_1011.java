public class leetcode_1011 {
    class Solution {
        public int shipWithinDays(int[] weights, int days) {
            //存在一个运载能力下限Xans,当运载能力X >= Xans,则可以在days天内完成运载
            //当 X < Xans,多于days天才能完成 运送货物。则Xans就是我们要找的运载能力下限
            // max(weights[])<= Xans <= Σ(weights[])
            // 这个范围是单调非递减，可以通过二分来找寻最合适的Xans
            // 对 Xans运载能力 判断是够能在指定时间内运送货物满足 贪心算法(只要连续的包裹不大于 Xans) 并在指定时间完成即可
            int maxW = maxWeight(weights);
            int sumW = sumWeight(weights);
            int left = maxW;
            int right = sumW;
            //二分查找 第一个满足 运载能力的重量
            //终止条件是 left == right, [left,right)为空
            //最终结束的right 位置就是刚满足的位置(向左偏移)
            while(left < right){
                int mid = left + (right - left)/2;
                if(canFinish(weights,mid,days)){
                    right--;
                }else{
                    left++;
                }
            }
            return left;
        }
        private boolean canFinish(int[] weights,int cap,int days){
            int capAns = cap;
            for(int i = 0;i < weights.length;){
                if(cap - weights[i] >= 0)
                    cap-=weights[i++];
                else{
                    days--;
                    cap = capAns;
                }
                if(days < 0)
                    return false;
            }
            //最后需要将运载天数减1
            return --days >= 0;
        }
        private int maxWeight(int[] weights){
            int maxWeight = weights[0];
            for(int i = 1;i < weights.length;i++)
                if(maxWeight < weights[i])
                    maxWeight = weights[i];
            return maxWeight;
        }
        private int sumWeight(int[] weights){
            int s = 0;
            for(int i = 0;i < weights.length;i++)
                s += weights[i];
            return s;
        }

    }
    public static void main(String[] args) {
        int[] arr = new int[]{3,2,2,4,1,4};
        int days = 3;
        Solution solution = new leetcode_1011().new Solution();
//        int maxW = solution.maxWeight(arr);
//        int sumW = solution.sumWeight(arr);
//        System.out.println(maxW);
//        System.out.println(sumW);
        //result
        //6
        System.out.println(solution.shipWithinDays(arr, days));
    }
}
