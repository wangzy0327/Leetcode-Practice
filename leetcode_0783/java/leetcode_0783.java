import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0783 {
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
        public int getMinimumDifference(TreeNode root) {
            this.min_diff = Integer.MAX_VALUE;
            //方法1.中序遍历(BST中序是单调递增 所以 最小差值一定在相邻节点间)
            pre = -1;
            inOrderDiff(root);
            //因为是二叉搜索树，所以最小差值必定是左子树的最大值与当前节点 或者 当前节点与右子树最小节点之间
            //这里采用后序遍历寻找最小差值
            // getMinHelper(root);
            return min_diff;
        }
        private int pre;
        private int min_diff;
        private void inOrderDiff(TreeNode root){
            if(root != null){
                inOrderDiff(root.left);
                if(pre == -1)
                    pre = root.val;
                else{
                    min_diff = Math.min(min_diff,Math.abs(root.val-pre));
                    pre = root.val;
                }
                inOrderDiff(root.right);
            }
        }
        private TreeNode[] getMinHelper(TreeNode root){
            if(root!=null){
                TreeNode[] leftPair = getMinHelper(root.left);
                TreeNode[] rightPair = getMinHelper(root.right);
                if(leftPair[1]!=null)
                    min_diff = Math.min(Math.abs(root.val-leftPair[1].val),min_diff);
                if(rightPair[0]!=null)
                    min_diff = Math.min(Math.abs(root.val-rightPair[0].val),min_diff);
                //返回当前最大最小节点
                TreeNode maxNode = (rightPair[1]!=null)?rightPair[1]:root;
                TreeNode minNode = (leftPair[0]!=null)?leftPair[0]:root;
                return new TreeNode[]{minNode,maxNode};
            }
            return new TreeNode[]{null,null};
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
        leetcode_0783.Solution solution = new leetcode_0783().new Solution();
        leetcode_0783.TreeNode root = new leetcode_0783().new TreeNode(236);
        leetcode_0783.TreeNode left = new leetcode_0783().new TreeNode(104);
        leetcode_0783.TreeNode right = new leetcode_0783().new TreeNode(701);
        leetcode_0783.TreeNode ll = null;
        leetcode_0783.TreeNode lr = new leetcode_0783().new TreeNode(227);
        leetcode_0783.TreeNode rl = null;
        leetcode_0783.TreeNode rr = new leetcode_0783().new TreeNode(911);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//      [236,104,701,null,227,null,911]
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        int res = solution.getMinimumDifference(root);
        System.out.println(res);
        //result
        //9
    }
}
