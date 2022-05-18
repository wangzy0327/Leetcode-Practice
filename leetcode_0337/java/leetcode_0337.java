import java.util.*;

public class leetcode_0337 {
    /**
     * Definition for a binary tree node.
     */
     public class TreeNode {
         int val;
         TreeNode left;
         TreeNode right;
         TreeNode() {}
         TreeNode(int val) { this.val = val; }
         TreeNode(int val, TreeNode left, TreeNode right) {
              this.val = val;
              this.left = left;
              this.right = right;
         }
     }
    class Solution {
        public int rob(TreeNode root) {
            //错误！！！初始错误思路：由于是树状结构，可知达到最大金额必定是隔层累加 愚蠢的进行层次遍历，隔行求和
            //反例 下图中最高金额为 3+4 ，并不是隔行取
            //    2
            //   / \
            //  1   3
            //   \
            //   4
            //
            //正确思路：由于父子不能同时取，所以每个节点有两种状态，偷或者不偷
            //1.当偷当前节点时，那么两个孩子节点就不能偷了
            //2.当不偷当前节点时，获取两个孩子子树所能达到的最大金额就行
            //用数组来表示节点选择哪种状态，0表示不偷，1表示偷
            //任何一个节点能偷到的最大钱的状态可以定义为
            //1.当前节点选择不偷：当前节点能偷到的最大钱数 = 左孩子能偷到的钱+右孩子能偷到的钱
            //2.当前节点选择偷：当前节点能偷到的最大钱数 = 左孩子选择自己不偷时能得到的钱 + 右孩子选择不偷时能得到的钱 + 当前节点的钱数
            // root[0] = max(root.left[0],root.left[1]) + max(root.right[0],root.right[1])
            // root[1] = root.val + root.left[0] + root.right[0]
            // return max(root[0],root[1])
            //初始状态 只有一个节点 root[0] = 0;root[1] = root.val;
            int[] res = robHelper(root);
            return Math.max(res[0],res[1]);
        }
        public int rob2(TreeNode root) {
            //思路：采用 记忆化搜索+重复子结构
            //采用unordered_map<TreeNode*,int>来记录 某个节点所能达到的最高金额
            //如果TreeNode* 在记录中直接返回，不在的话求解
            //求解过程，root节点的最高金额 分为 取当前节点 和 不取当前节点 两种情况
            // dp(表示取当前节点)
            record = new HashMap<>();
            return dp(root);
        }
        private int[] robHelper(TreeNode root){
            int[] status = {0,0};
            int[] left = {0,0};
            int[] right = {0,0};
            if(root.left != null)
                left = robHelper(root.left);
            if(root.right != null)
                right = robHelper(root.right);
            //不取当前节点
            status[0] = Math.max(left[0],left[1]) + Math.max(right[0],right[1]);
            //取当前节点
            status[1] = root.val + left[0] + right[0];
            return status;
        }
        private Map<TreeNode,Integer> record;
        int dp(TreeNode root){
            if(root != null){
                if(record.containsKey(root))
                    return record.get(root);
                //取当前节点
                int val = root.val;
                //左子树最大金额
                int lVal = dp(root.left);
                //右子树最大金额
                int rVal = dp(root.right);
                //当前节点子树最大金额为 max(val + sum(dp(root->left->left),dp(root->left->right)) +dp(root->right),lVal+rVal)
                //左子树下不包含root->left的最大金额
                int llVal = (root.left == null)?0:dp(root.left.left)+dp(root.left.right);
                //右子树下不包含root->right的最大金额
                int rrVal = (root.right == null)?0:dp(root.right.left)+dp(root.right.right);
                int res = Math.max(lVal+rVal,val+llVal+rrVal);
                record.put(root,res);
                return res;
            }
            return 0;
        }
        public List<List<Integer>> levelOrder(TreeNode root) {
            List<TreeNode> cur = new ArrayList();
            List<TreeNode> next = new ArrayList();
            if (root == null)
                return new LinkedList();
            if (root != null)
                cur.add(root);
            List<List<Integer>> res = new LinkedList();
            List<Integer> curEles = new LinkedList();
            while (cur.size() > 0) {
                for (int i = 0; i < cur.size(); i++) {
                    curEles.add(cur.get(i).val);
                    if (cur.get(i).left != null)
                        next.add(cur.get(i).left);
                    if (cur.get(i).right != null)
                        next.add(cur.get(i).right);
                }
                res.add(new LinkedList(curEles));
                cur = new LinkedList(next);
                curEles.clear();
                next.clear();
            }
            return res;
        }

        public List<String> levelOrderStr(TreeNode root) {
            List<TreeNode> cur = new ArrayList();
            List<TreeNode> next = new ArrayList();
            if (root == null)
                return new LinkedList();
            if (root != null)
                cur.add(root);
            List<String> res = new LinkedList();
            while (cur.size() > 0) {
                int flag = 0;
                for (int i = 0; i < cur.size(); i++) {
                    if (cur.get(i) == null) {
                        res.add("null");
                        continue;
                    } else
                        res.add(String.valueOf(cur.get(i).val));
                    TreeNode left = cur.get(i).left;
                    TreeNode right = cur.get(i).right;
                    if (left != null || right != null)
                        flag++;
                    next.add(left);
                    next.add(right);
                }
                cur = new LinkedList(next);
                if (flag == 0)
                    cur.clear();
                next.clear();
            }
            return res;
        }

        public <T> void printListArr(List<List<T>> list) {
            for (int i = 0; i < list.size(); i++) {
                if (i == list.size() - 1) {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.println(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " , ");
                }
            }
        }
    }

    public static void main(String[] args) {
        leetcode_0337.Solution solution = new leetcode_0337().new Solution();
        leetcode_0337.TreeNode root = new leetcode_0337().new TreeNode(2);
        leetcode_0337.TreeNode left = new leetcode_0337().new TreeNode(1);
        leetcode_0337.TreeNode right = new leetcode_0337().new TreeNode(3);
        leetcode_0337.TreeNode ll = null;
        leetcode_0337.TreeNode lr = new leetcode_0337().new TreeNode(4);
        left.left = ll;
        left.right = lr;
        root.left = left;
        root.right = right;
        //[2,1,3,null,4]
        //result
        //7 = 3 + 4
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[2, 1, 3, null, 4, null, null]
        System.out.println(solution.rob2(root));

    }
}
