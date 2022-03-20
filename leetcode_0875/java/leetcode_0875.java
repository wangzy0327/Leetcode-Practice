public class leetcode_0875 {
    class Solution {
        public int minEatingSpeed(int[] piles, int h) {
            //思路：二分搜索，吃香蕉速度为[1,max[piles]+1)
            int left = 1;
            int right = maxPiles(piles) + 1;
            //[left,right]
            //循环退出条件 left == right [x,x)为空，取不到
            while(left < right){
                int mid = left + (right - left)/2;
                if(canFinish(piles,mid,h)){
                    right = mid;
                }else{
                    left = mid + 1;
                }
            }
            return left;
        }
        private boolean canFinish(int[] piles,int k,int h){
            for(int i = 0;i < piles.length;i++){
                int speed = piles[i]/k + ((piles[i]%k == 0)?0:1);
                if(h - speed >= 0){
                    h-=speed;
                }else{
                    return false;
                }
            }
            return true;
        }
        private int maxPiles(int[] piles){
            int res = piles[0];
            for(int i = 1;i < piles.length;i++){
                if(res < piles[i])
                    res = piles[i];
            }
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0875().new Solution();
        int[] piles = new int[]{3,6,7,11};
        int h = 8;
        int res = solution.minEatingSpeed(piles,h);
        System.out.println(res);
        //result
        //4
    }
}
