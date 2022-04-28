public class leetcode_0042 {
    class Solution {
        public int trap(int[] height) {
//思路：根据题意，需要整理出计算i位置的单位雨水量cap的计算公式
            //i位置的雨水量计算取决于左边界最大高度与右边界最大高度，两者的最小值
            //cap[i] = min(max(height[0,i)),max(height(i,length-1)) - height[i]

            //由此可以知道每次需要去求 左侧柱子最大值与右侧柱子最大

            //空间优化思考：由于每次求取i位置的雨水容量只跟左右侧最大值中的最小高度有关
            //可以通过左右双指针来优化（当左边界最大值小于右边界最大值，左指针向右移动(因为有右边界托底，所以i位置的雨水容量只跟左边界有关(左边界最大值小于右边界最大值))）
            //反之则是 左侧边界托底，先入右侧right-1位置的雨水量
            //左右指针结束条件为 leftPos == rightPos

            //左右指针
            int left = 0;
            int right = height.length-1;
            //0位置和height.size()-1位置肯定没有雨水
            //初始化左右边界最大值 左 (..,0]  右 [height.size()-1,...)
            int leftMax = height[left];
            int rightMax = height[right];
            //循环退出条件left== right
            int ans = 0;
            while(left < right){
                if(leftMax < rightMax){
                    int diff = leftMax - height[++left];
                    ans += (diff > 0)?diff:0;
                    //向右移动后更新左侧边界最大值
                    leftMax = Math.max(leftMax,height[left]);
                }else{
                    int diff = rightMax - height[--right];
                    ans += (diff > 0)?diff:0;
                    //向左移动后更新右侧边界最大值
                    rightMax = Math.max(rightMax,height[right]);
                }
            }
            return ans;
        }
    }
    public static void main(String[] args) {
        leetcode_0042.Solution solution = new leetcode_0042().new Solution();
        int[] height = {0,1,0,2,1,0,1,3,2,1,2,1};
        System.out.println(solution.trap(height));
        //result
        //6
    }
}
