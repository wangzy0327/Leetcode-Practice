import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class leetcode_0124 {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    class Solution {
        public int maxPathSum(TreeNode root) {
            //思路：最大路径和求解 通过 当前节点与左右子树最大路径之和更新最大路径sum来递归求解
            //由于至少包含一个节点，且节点可能为负值，所以将最大路径和初值置为INT_MIN
            ans = Integer.MIN_VALUE;
            maxPathHelper(root);
            return ans;
        }
        private int ans;
        //返回包含当前节点的最大子路径
        private int maxPathHelper(TreeNode root){
            if(root != null){
                //这里需要注意如果返回的子路径为负值，则可以不使用子路径
                int leftSub = Math.max(0,maxPathHelper(root.left));
                int rightSub = Math.max(0,maxPathHelper(root.right));
                //更新记录的最大路径和
                ans = Math.max(ans,leftSub + rightSub + root.val);
                //返回最大子路径
                return Math.max(leftSub,rightSub)+root.val;
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
        leetcode_0124.Solution solution = new leetcode_0124().new Solution();
        leetcode_0124.TreeNode root = new leetcode_0124().new TreeNode(-10);
        leetcode_0124.TreeNode left = new leetcode_0124().new TreeNode(9);
        leetcode_0124.TreeNode right = new leetcode_0124().new TreeNode(20);
        leetcode_0124.TreeNode ll = null;
        leetcode_0124.TreeNode lr = null;
        leetcode_0124.TreeNode rl = new leetcode_0124().new TreeNode(15);
        leetcode_0124.TreeNode rr = new leetcode_0124().new TreeNode(7);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new leetcode_0124().new TreeNode(0);
//        lr.left = new leetcode_0124().new TreeNode(3);
//        lr.left = new leetcode_0124().new TreeNode(7);
//        lr.right = new leetcode_0124().new TreeNode(4);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [-10, 9, 20, null, null, 15, 7]
        int res = solution.maxPathSum(root);
        System.out.println(res);
        //result
        //42
        //最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
    }
}
