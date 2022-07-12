public class leetcode_0292 {
    class Solution {
        public boolean canWinNim(int n) {
            //思路：由于每次可以取1-3块石头
            //所以后手可以控制每个周期（轮流取）石块减少4
            //ep 1->3 2->2 3->1
            //所以如果石头是4的倍数，则按照最优解法（保持石块按照4的倍数周期递减） 后手肯定赢
            //如果石头不是4的倍数，则先手可以调控取1-3个石子，让剩余石子为4的倍数，则自己可按照4的倍数（周期中最后取）制胜
            //ep 7 = 4 + 3 可先取3，然后后面无论如何都是自己赢
            return n%4 != 0;
        }
    }
    public static void main(String[] args) {
        leetcode_0292.Solution solution = new leetcode_0292().new Solution();
        int n = 4;
        boolean res = solution.canWinNim(n);
        System.out.println(res);
        //result false
        /*
        解释：以下是可能的结果:
        1. 移除1颗石头。你的朋友移走了3块石头，包括最后一块。你的朋友赢了。
        2. 移除2个石子。你的朋友移走2块石头，包括最后一块。你的朋友赢了。
        3.你移走3颗石子。你的朋友移走了最后一块石头。你的朋友赢了。
        在所有结果中，你的朋友是赢家。
         */
    }
}
