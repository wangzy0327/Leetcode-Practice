import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_1038 {
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
        public TreeNode convertBST(TreeNode root) {
            //累加向左
            //遍历方式，先遍历右子树，后遍历左子树,返回
            this.sum = 0;
            accumulateBST(root);
            return root;
        }
        private int sum;
        private void accumulateBST(TreeNode root){
            if(root!=null){
                accumulateBST(root.right);
                root.val += sum;
                sum = root.val;
                accumulateBST(root.left);
            }
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
        leetcode_1038.Solution solution = new leetcode_1038().new Solution();
        leetcode_1038.TreeNode root = new leetcode_1038().new TreeNode(4);
        leetcode_1038.TreeNode left = new leetcode_1038().new TreeNode(1);
        leetcode_1038.TreeNode right = new leetcode_1038().new TreeNode(6);
        leetcode_1038.TreeNode ll = new leetcode_1038().new TreeNode(0);
        leetcode_1038.TreeNode lr = new leetcode_1038().new TreeNode(2);
        leetcode_1038.TreeNode rl = new leetcode_1038().new TreeNode(5);
        leetcode_1038.TreeNode rr = new leetcode_1038().new TreeNode(7);
        leetcode_1038.TreeNode lrr = new leetcode_1038().new TreeNode(3);
        leetcode_1038.TreeNode rrr = new leetcode_1038().new TreeNode(8);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        lr.right = lrr;
        rr.right = rrr;
//      [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        solution.accumulateBST(root);
        List<String> anoStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
        //result
        //[30, 36, 21, 36, 35, 26, 15, null, null, null, 33, null, null, null, 8]
    }
}
