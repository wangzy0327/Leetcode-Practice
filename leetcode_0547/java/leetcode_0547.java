import java.util.HashSet;
import java.util.Set;

public class leetcode_0547 {
    class Solution {
        public int findCircleNum(int[][] isConnected) {
            //思路：采用并查集（主要解决连接和合并问题）
            //进行合并连接操作后，对每个城市进行根节点判断去重(无序集合)
            int n = isConnected.length;
            parents = new int[n];
            sz = new int[n];
            for(int i = 0;i < n;i++){
                parents[i] = i;
                sz[i] = 1;
            }
            for(int i = 0;i < n;i++){
                //注意这里由于连通性 只需要判断一半即可
                for(int j = i+1;j < n;j++){
                    if(isConnected[i][j] == 1){
                        unionElements(i,j);
                    }
                }
            }
            Set<Integer> set = new HashSet();
            for(int i = 0;i < n;i++)
                set.add(find(i));
            return set.size();
        }
        private int[] parents;
        private int[] sz;
        private int find(int p){
            if(p != parents[p])
                parents[p] = find(parents[p]);
            return parents[p];
        }
        private void unionElements(int p,int q){
            int pRoot = find(p);
            int qRoot = find(q);
            int szP = sz[pRoot];
            int szQ = sz[qRoot];
            if(pRoot == qRoot)
                return ;
            else{
                //路径根据根节点含有的孩子数量压缩
                if(szP >= szQ){
                    parents[qRoot] = pRoot;
                    sz[pRoot] += sz[qRoot];
                }else{
                    parents[pRoot] = qRoot;
                    sz[qRoot] += sz[pRoot];
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0547.Solution solution = new leetcode_0547().new Solution();
        int[][] isConnected = {
                {1,1,0},
                {1,1,0},
                {0,0,1}
        };
        int circleNum = solution.findCircleNum(isConnected);
        System.out.println(circleNum);
        //result
        //2
    }
}
