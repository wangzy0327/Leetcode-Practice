import java.util.Arrays;

public class leetcode_1569 {
    class Node{
        int value;
        Node left;
        Node right;
        int sz;
        int ans;
        Node(int val){this.value = val;this.left = null;this.right = null;this.sz = 1;this.ans = 0;}
    }
    class Solution {
        private final int mod = 1000_000_007;
        public int numOfWays(int[] nums) {
            //思路：对于a0,a1,a2,a3,...,an由于保持相同二叉查找树，a0根节点是固定的
            //左子树即为小于a0的元素按照数组顺序依次插入左子树中
            //右子树即为大于a0的元素按照数组顺序依次插入右子树中
            //设f[ai]表示对ai(对应节点)为根节点的子树，将其包含的所有元素进行重排序得到的相同结果二叉排序树的排列数
            //设以ai 为根节点的子树对应的排列的长度为size(ai)
            //排列首个元素为ai
            //f[al]表示左子树对应排序数, f[ar]表示右子树对应的排序数
            //为了保证二叉查找树结果相同,需要在size(ai)-1个位置中找到size(al)个位置排列左子树，而右子树的位置也就随之而定
            //f[ai] = C(size(ai)-1,size(al))*f[al]*f[ar];
            //极端情况下，当以ai为根节点只有一个元素时, f[ai] = 1;当其某个子树为空时，size(子树)大小为0,f(子树)为1
            //由于求f[ai]需要事先知道 树中元素大小，以及左子树大小，所以首先需要构建树,并记录树中根节点子树sz大小
            //每个子树保留成员变量记录f[ai]的值
            // 求C(n,k) = C(n-1,k-1) + C(n-1,k); C(n,0) = 1;
            // 设 N = 10^9+7 , 乘法满足 a = (N*i)+p; b = (N*j)+q; (a*b)%N = (N*i*N*j+N*i*q+N*j*p+pq)%N = (a%N*b%N) = p*q

            //构建BST
            Node root = new Node(nums[0]);
            for(int i = 1;i < nums.length;i++)
                insert(root,nums[i]);

            //计算C(n,k),方便后面计算动态规划
            int[][] dp = new int[nums.length+1][nums.length+1];
            dp[0][0] = 1;
            dp[1][0] = 1;
            dp[1][1] = 1;
            //i 为 n, j 为 k  C(n,k) = C(n-1,k-1) + C(n-1,k) {k <= n-1}
            for(int i = 2;i <= nums.length;i++){
                dp[i][0] = 1;
                dp[i][i] = 1;
                for(int j = 1;j < i;j++){
                    dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%mod;
                }
            }
            for(int i = 0;i < dp.length;i++)
                System.out.println(Arrays.toString(dp[i]));


            //动态规划计算排列数
            dfs(root,dp);
            return root.ans-1;
        }
        private void insert(Node root,int val){
            Node cur = root;
            while(true){
                //增加子节点大小
                cur.sz++;
                if(val < cur.value){
                    if(cur.left == null){
                        cur.left = new Node(val);
                        return ;
                    }
                    else
                        cur = cur.left;
                }else{
                    if(cur.right == null){
                        cur.right = new Node(val);
                        return ;
                    }
                    else
                        cur = cur.right;
                }
            }
        }
        private void dfs(Node root,int[][] dp){
            //f[ai] = C(size(ai)-1,size(al))*f[al]*f[ar]
            if(root != null){
                if(root.left != null)
                    dfs(root.left,dp);
                if(root.right != null)
                    dfs(root.right,dp);
                int fl = (root.left==null)?1:root.left.ans;
                int fr = (root.right==null)?1:root.right.ans;
                int lsz = (root.left==null)?0:root.left.sz;
                long temp = (long)dp[root.sz-1][lsz]%mod*fl%mod*fr%mod;
                root.ans = (int)temp;
            }
        }
    }
    public static void main(String[] args) {
        leetcode_1569.Solution solution = new leetcode_1569().new Solution();
        int[] nums = {3,4,5,1,2};
        //result
        //5
        /*下面 5 个数组会得到相同的 BST：
        [3,1,2,4,5]
        [3,1,4,2,5]
        [3,1,4,5,2]
        [3,4,1,2,5]
        [3,4,1,5,2]
        * */
//        int[] nums = {1,2,3};
        //result
        //0
//        int[] nums = {9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18};
        //result
        //216212978
        System.out.println(solution.numOfWays(nums));
    }
}
