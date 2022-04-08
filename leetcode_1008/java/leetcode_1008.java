import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_1008 {
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
        public TreeNode bstFromPreorder(int[] preorder) {
            //根据BST树的性质，分割左右子树区间
            return builderBST(preorder,0,preorder.length-1);
        }
        private TreeNode builderBST(int[] preorder,int start,int end){
            if(start > end)
                return null;
            else if(start == end)
                return new TreeNode(preorder[start]);
            TreeNode root = new TreeNode(preorder[start]);
            int target = root.val;
            //右子树起始索引
            int idx = start + 1;
            while(idx <= end){
                if(preorder[idx] > target)
                    break;
                idx++;
            }
            root.left = builderBST(preorder,start+1,idx-1);
            root.right = builderBST(preorder,idx,end);
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
        leetcode_1008.Solution solution = new leetcode_1008().new Solution();
//        leetcode_1008.TreeNode root = new leetcode_1008().new TreeNode(10);
//        leetcode_1008.TreeNode left = new leetcode_1008().new TreeNode(5);
//        leetcode_1008.TreeNode right = new leetcode_1008().new TreeNode(15);
//        leetcode_1008.TreeNode ll = new leetcode_1008().new TreeNode(3);
//        leetcode_1008.TreeNode lr = new leetcode_1008().new TreeNode(7);
//        leetcode_1008.TreeNode rl = null;
//        leetcode_1008.TreeNode rr = new leetcode_1008().new TreeNode(18);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
//        root.left = left;
//        root.right = right;
//        ll.left = new leetcode_1008().new TreeNode(0);
//        lr.left = new leetcode_1008().new TreeNode(3);
//        lr.left = new leetcode_1008().new TreeNode(5);
        int[] preorder = {8,5,1,7,10,12};
        //[8,5,1,7,10,12]
        TreeNode root = solution.bstFromPreorder(preorder);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //result
        //[8, 5, 10, 1, 7, null, 12]
    }
}
