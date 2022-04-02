import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class leetcode_0701 {
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
        public TreeNode insertIntoBST(TreeNode root, int val) {
            if(root == null)
                return new TreeNode(val);
            if(root != null){
                if(val < root.val)
                    root.left = insertIntoBST(root.left,val);
                else if(val > root.val)
                    root.right = insertIntoBST(root.right,val);
            }
            return root;
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
        leetcode_0701.Solution solution = new leetcode_0701().new Solution();
        leetcode_0701.TreeNode root = new leetcode_0701().new TreeNode(4);
        leetcode_0701.TreeNode left = new leetcode_0701().new TreeNode(2);
        leetcode_0701.TreeNode right = new leetcode_0701().new TreeNode(7);
        leetcode_0701.TreeNode ll = new leetcode_0701().new TreeNode(1);
        leetcode_0701.TreeNode lr = new leetcode_0701().new TreeNode(3);
        leetcode_0701.TreeNode rl = null;
        leetcode_0701.TreeNode rr = null;
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//      root = [4,2,7,1,3], val = 5
        //[4, 2, 7, 1, 3, null, null]
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        int val = 5;
        TreeNode anoRoot = solution.insertIntoBST(root, val);
        List<String> anoStr = solution.levelOrderStr(anoRoot);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
        //result
        //[4, 2, 7, 1, 3, 5, null]
    }
}
