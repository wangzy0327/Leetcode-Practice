import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0669 {
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
        public TreeNode trimBST(TreeNode root, int low, int high) {
            //修剪节点 递归判定，如果存在当前节点在[low,high]范围内则继续遍历子树
            //如果当前节点小于low,则返回 右子树满足的节点
            //如果当前节点大于high,则返回 左子树满足的节点
            if(root != null){
                if(root.val >= low && root.val <= high){
                    root.left = trimBST(root.left,low,high);
                    root.right = trimBST(root.right,low,high);
                    return root;
                }else if(root.val < low)
                    return trimBST(root.right,low,high);
                else if(root.val > high)
                    return trimBST(root.left,low,high);
            }
            return null;
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
                    System.out.println(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " , ");
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0669.Solution solution = new leetcode_0669().new Solution();
        leetcode_0669.TreeNode root = new leetcode_0669().new TreeNode(1);
        leetcode_0669.TreeNode left = new leetcode_0669().new TreeNode(0);
        leetcode_0669.TreeNode right = new leetcode_0669().new TreeNode(2);
//        leetcode_0669.TreeNode ll = null;
//        leetcode_0669.TreeNode lr = null;
//        leetcode_0669.TreeNode rl = new leetcode_0669().new TreeNode(3);
//        leetcode_0669.TreeNode rr = new leetcode_0669().new TreeNode(6);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//      root = [1,0,2], low = 1, high = 2
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));

        int low = 1;int high = 2;
        TreeNode anoRoot = solution.trimBST(root, low, high);
        List<String> anoStr = solution.levelOrderStr(anoRoot);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));

        //result
        //[1,null,2]
    }
}
