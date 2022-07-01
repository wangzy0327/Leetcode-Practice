import java.util.Arrays;

public class leetcode_0452 {
    class Solution {
        public int findMinArrowShots(int[][] points) {
            //贪心算法：最少的箭引爆气球，那么每次让射出的箭引爆最多的气球数即可
            //贪心算法的条件：
        /*
        最优子结构：规模较大的问题的解由规模较小的子问题的解组成，规模较大的问题的解只由其中一个规模较小的子问题的解决定；
        无后效性：后面阶段的求解不会修改前面阶段已经计算好的结果；
        贪心选择性质：从局部最优解可以得到全局最优解
        */
            //1.所有气球先按照Xend 升序排序
            //2.如果多个气球重叠，射箭的位置要在Xend最小的位置上射箭 则跳过
            //3.然后往下走，直到找到下一个Xstart > 上一个Xend的位置时,更新Xend,ans + 1 (射箭数量+1)
            //4.继续上面的过程
            //排序
            //注意这里不要用加减法，正数-负数会越界
            //这里比较器必须考虑 两者相等的情况，否则在某些情况下会报错
            //java.lang.IllegalArgumentException: Comparison method violates its general contract
            Arrays.sort(points,(u, v) -> (u[1]<=v[1])?((u[1]<v[1])?-1:0):1);
            int ans = 1;
            int lastEnd = points[0][1];
            for(int[] point : points){
                if(point[0] > lastEnd){
                    lastEnd = point[1];
                    ans++;
                }
            }
            return ans;
        }
    }
    public static void main(String[] args) {
//        int[][] points = {{-2147483646,-2147483645},{2147483646,2147483647}};
        //result
        //2
//        int[][] points = {{3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8}};
        //result
        //2
        int[][] points = {{10,16},{2,8},{1,6},{7,12}};
        /*
        气球可以用2支箭来爆破:
        -在x = 6处射出箭，击破气球{2,8}和{1,6}。
        -在x = 11处发射箭，击破气球{10,16}和{7,12}
        * */
        //result
        //2
        leetcode_0452.Solution solution = new leetcode_0452().new Solution();
        int result = solution.findMinArrowShots(points);
        System.out.println(result);



    }
}
