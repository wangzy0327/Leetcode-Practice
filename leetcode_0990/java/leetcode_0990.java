public class leetcode_0990 {
    class Solution {
        public boolean equationsPossible(String[] equations) {
            //思路：通过并查集 先将有连接关系的 变量放入并查集中
            //而后判断不连接的 变量如果之前判断是连接的，则返回false
            // 否则 返回true

            //因为都是小写字母所以并查集数量设置为26
            parents = new int[26];
            sz = new int[26];
            for(int i = 0;i < parents.length;i++){
                parents[i] = i;
                sz[i] = 1;
            }
            for(int i = 0;i < equations.length;i++){
                if(equations[i].charAt(1) == '='){
                    int p = equations[i].charAt(0) - 'a';
                    int q = equations[i].charAt(3) - 'a';
                    unionElements(p,q);
                }
            }
            for(int i = 0;i < equations.length;i++){
                if(equations[i].charAt(1) == '!'){
                    int p = equations[i].charAt(0) - 'a';
                    int q = equations[i].charAt(3) - 'a';
                    if(isConnected(p,q))
                        return false;
                }
            }
            return true;
        }
        private int[] parents;
        private int[] sz;
        private int find(int p){
            while(p != parents[p]){
                //压缩路径
                parents[p] = parents[parents[p]];
                p = parents[p];
            }
            return p;
        }
        private boolean isConnected(int p,int q){
            return find(p) == find(q);
        }
        private void unionElements(int p,int q){
            int pRoot = find(p);
            int qRoot = find(q);
            if(pRoot == qRoot)
                return ;
            //如果p根节点孩子多的话，将q根节点的接入p根节点
            if(sz[pRoot] >= sz[qRoot]){
                parents[qRoot] = pRoot;
                sz[pRoot] += sz[qRoot];
            }else{
                //sz[pRoot] < sz[qRoot]
                parents[pRoot] = qRoot;
                sz[qRoot] += sz[pRoot];
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0990.Solution solution = new leetcode_0990().new Solution();
        String[] equations = {
//                "a==b",
//                "b==a"

                "a==b","b!=c","c==a"
        };
        System.out.println(solution.equationsPossible(equations));
        //result
        //true

        //result
        //false
    }
}
