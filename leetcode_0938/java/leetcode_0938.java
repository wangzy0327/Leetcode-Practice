import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0938 {
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
        public int rangeSumBST(TreeNode root, int low, int high) {
            sum = 0;
            //采用先序遍历 在[low,high]区间内 累加sum
            rangeSumHelper(root,low,high);
            return sum;
        }
        private int sum;
        private void rangeSumHelper(TreeNode root,int low,int high){
            if(root != null){
                if(root.val >= low && root.val <= high)
                    sum += root.val;
                //采用先序遍历如果当前节点的值小于low,那左子树不用遍历
                //可以避免一半的遍历
                //右子树同理
                if(root.val > low)
                    rangeSumHelper(root.left,low,high);
                if(root.val < high)
                    rangeSumHelper(root.right,low,high);
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
        leetcode_0938.Solution solution = new leetcode_0938().new Solution();
        leetcode_0938.TreeNode root = new leetcode_0938().new TreeNode(10);
        leetcode_0938.TreeNode left = new leetcode_0938().new TreeNode(5);
        leetcode_0938.TreeNode right = new leetcode_0938().new TreeNode(15);
        leetcode_0938.TreeNode ll = new leetcode_0938().new TreeNode(3);
        leetcode_0938.TreeNode lr = new leetcode_0938().new TreeNode(7);
        leetcode_0938.TreeNode rl = null;
        leetcode_0938.TreeNode rr = new leetcode_0938().new TreeNode(18);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new leetcode_0938().new TreeNode(0);
//        lr.left = new leetcode_0938().new TreeNode(3);
//        lr.left = new leetcode_0938().new TreeNode(5);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [10,5,15,3,7,null,18], low = 7, high = 15
        int low = 7;
        int high = 15;
        int res = solution.rangeSumBST(root,low,high);
        System.out.println(res);
        //result
        //32
    }
}
