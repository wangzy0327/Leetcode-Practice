public class leetcode_0050 {
    class Solution {
        public double myPow(double x, int n) {
            //思路：快速幂计算
            // m^(k) = (m^2)^(k/2) {k%2 == 0} | (m)*(m^2)^(k/2) {k%2 == 1}
            // 设M = (m^2),递归求解 M^(k/2)的解，直到指数为0
            double ans = 1.0d;
            int flag = 0; //判断是正或者负
            if(n < 0){
                //防止Integer.MIN_VALUE 取相反数出现越界
                ans = x;
                n++;
                n = -n;
                flag = 1;
            }
            while(n != 0){
                //奇数
                if((n & 1) != 0)
                    ans = ans * x;
                x = x*x;
                n >>= 1;
            }
            return (flag==1)?1/ans:ans;
        }
    }
    public static void main(String[] args) {
        double x = 2.0;
        int n = 10;
        //result 1024
//    double x = 2.0;
//    int n = -2;
        //result 0.25
//    double x = 1.0;
//    int n = -2147483648;
        //result 1.0
        leetcode_0050.Solution solution = new leetcode_0050().new Solution();
        double res = solution.myPow(x,n);
        System.out.println(res);
        //result
        //1024.0
    }
}
