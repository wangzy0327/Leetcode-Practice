import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class leetcode_0098 {
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
        public boolean isValidBST(TreeNode root) {
            //检测合法BST，可用中序遍历来检测
            pre = null;
            return inOrder(root);
        }
        private TreeNode pre;
        private boolean inOrder(TreeNode root){
            if(root!=null){
                boolean leftValid = inOrder(root.left);
                if(!leftValid)
                    return false;
                if(pre == null)
                    pre = root;
                else if(pre.val >= root.val)
                    return false;
                else{
                    //pre.val < root.val
                    pre = root;
                }
                boolean rightValid = inOrder(root.right);
                if(!rightValid)
                    return false;
            }
            return true;
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
        leetcode_0098.Solution solution = new leetcode_0098().new Solution();
        leetcode_0098.TreeNode root = new leetcode_0098().new TreeNode(5);
        leetcode_0098.TreeNode left = new leetcode_0098().new TreeNode(1);
        leetcode_0098.TreeNode right = new leetcode_0098().new TreeNode(4);
        leetcode_0098.TreeNode ll = null;
        leetcode_0098.TreeNode lr = null;
        leetcode_0098.TreeNode rl = new leetcode_0098().new TreeNode(3);
        leetcode_0098.TreeNode rr = new leetcode_0098().new TreeNode(6);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//      root = [5, 1, 4, null, null, 3, 6]
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        /**
         * 解释: 输入为: [5,1,4,null,null,3,6]。
         *      根节点的值为 5 ，但是其右子节点值为 4 。
         */
        boolean validBST = solution.isValidBST(root);
        System.out.println(validBST);
        //result
        //false
    }
}
