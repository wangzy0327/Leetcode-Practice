public class leetcode_0204 {
    class Solution {
        public int countPrimes(int n) {
            //采用高效实现方案：筛数法
            //如果一个数是素数，ep:2,那么所有2的倍数2x2 = 4,3x2 = 6,4x2 = 8...都不可能是素数
            int[] vec = new int[n];
            for(int i = 2;i*i < n;i++){
                //只有素数需要判断，合数已经判断过(减少重复判断)
                if(vec[i] == 0){
                    for(int j = i*i;j < n;j+=i)
                        vec[j] = 1;
                }
            }
            int count = 0;
            for(int i = 2;i < n;i++){
                if(vec[i] == 0)
                    count++;
            }
            return count;
        }
    }
    public static void main(String[] args) {
        leetcode_0204.Solution solution = new leetcode_0204().new Solution();
        int n = 10;
        int res = solution.countPrimes(n);
        System.out.println(res);
        //result
        //4
//        小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7
    }
}
