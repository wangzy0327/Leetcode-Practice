public class leetcode_0372 {
    class Solution {
        public int superPow(int a, int[] b) {
            // 先验知识 (a*b) mod m = (a mod m)*(b mod m) mod m
            // a^(m+n) = a^m * a^n % mod
            // 快速幂： 3*9 = ((3*3)^2)^2 * 3  循环次数为log n (n为指数)
            //解题思路：分治 ep: 99^(2345) = (99^(234))^10 * 99^5
            // 99^(k) ( 0 < k < 10) 可以采用分治思想求解
            return dfs(a,b,b.length);
        }
        private int MOD = 1337;
        //u为索引
        private int dfs(int a,int[] b,int u){
            if(u == 0)
                return 1;
            //a^(10*k+b) = (a^k)^10 * a^b
            return quickPow(dfs(a,b,u-1),10) * quickPow(a,b[u-1]) % MOD;
        }
        //快速幂计算 a^b
        private int quickPow(int a,int b){
            int ans = 1;
            a %= MOD;
            while(b != 0){
                if((b&1) != 0)
                    ans = ans*a % MOD;
                a = a*a % MOD;
                b >>= 1;
            }
            return ans;
        }
    }
    public static void main(String[] args) {
        leetcode_0372.Solution solution = new leetcode_0372().new Solution();
//        int a = 2;
//        int[] b = {1,0};
        //result 1024
        int a = 2147483647;
        int[] b = {2,0,0};
        int result = solution.superPow(a, b);
        System.out.println(result);
        //result 1198

    }
}
