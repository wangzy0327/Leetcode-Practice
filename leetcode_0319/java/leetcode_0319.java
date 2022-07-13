public class leetcode_0319 {
    class Solution {
        public int bulbSwitch(int n) {
            return (int)Math.sqrt(n);
        }
    }
    class Solution2{
        public int bulbSwitch(int n){
            if(n == 0)
                return 0;
            //第一次Switch灯
            int[] arr = new int[n];
            for(int i = 0;i < n;i++)
                arr[i] = 1;
            for(int i = 2;i <= n;i++){
                for(int j = i-1;j < n;j += i){
                    arr[j] = (arr[j] == 1)?0:1;
                }
            }
            int count = 0;
            for(int i = 0;i < arr.length;i++)
                if(arr[i] == 1)
                    count++;
            return count;
        }
    }
    public static void main(String[] args) {
//        int n = 3;
        //result 1
        /**
         * 解释：
         初始时, 灯泡状态 [关闭, 关闭, 关闭].
         第一轮后, 灯泡状态 [开启, 开启, 开启].
         第二轮后, 灯泡状态 [开启, 关闭, 开启].
         第三轮后, 灯泡状态 [开启, 关闭, 关闭].

         你应该返回 1，因为只有一个灯泡还亮着
         *
         */
        int n = 10000000;
        //result 3162
        leetcode_0319.Solution solution = new leetcode_0319().new Solution();
        leetcode_0319.Solution2 solution2 = new leetcode_0319().new Solution2();
        int res1 = solution.bulbSwitch(n);
        int res2 = solution2.bulbSwitch(n);
        System.out.println(res1);
        System.out.println(res2);
    }
}
