import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class offer_1_0033 {
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
        public boolean verifyPostorder(int[] postorder) {
            //验证BST的后序结果(左右根)
            //可以根据BST性质 根节点小于 右子树 划分出 左子树和右子树 范围
            //而后递归验证 左子树(<)和右子树(>) 是否满足BST性质
            //时间复杂度O(nlogn)
            return verifyPostorder(postorder,0,postorder.length-1);
        }
        private boolean verifyPostorder(int[] postorder,int start,int end){
            if(start >= end)
                return true;
            int target = postorder[end];
            //右边子树第一个索引
            int idx = start;
            while(idx < end){
                if(postorder[idx] > target)
                    break;
                idx++;
            }
            //两段有任何一个不满足 则返回false
            if(!isMoreThan(postorder,idx,end-1,target) || !isLessThan(postorder,start,idx-1,target))
                return false;
            return verifyPostorder(postorder,start,idx-1) && verifyPostorder(postorder,idx,end-1);
        }
        private boolean isMoreThan(int[] postorder,int start,int end,int target){
            for(int i = start;i <= end;i++)
                if(postorder[i] <= target)
                    return false;
            return true;
        }
        private boolean isLessThan(int[] postorder,int start,int end,int target){
            for(int i = start;i <= end;i++)
                if(postorder[i] >= target)
                    return false;
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
        offer_1_0033.Solution solution = new offer_1_0033().new Solution();
        offer_1_0033.TreeNode root = new offer_1_0033().new TreeNode(5);
        offer_1_0033.TreeNode left = new offer_1_0033().new TreeNode(2);
        offer_1_0033.TreeNode right = new offer_1_0033().new TreeNode(6);
        offer_1_0033.TreeNode ll = new offer_1_0033().new TreeNode(1);
        offer_1_0033.TreeNode lr = new offer_1_0033().new TreeNode(3);
//        offer_1_0033.TreeNode rl = new offer_1_0033().new TreeNode(7);
//        offer_1_0033.TreeNode rr = new offer_1_0033().new TreeNode(9);
        left.left = ll;
        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        lr.left = new offer_1_0033().new TreeNode(3);
//        lr.left = new offer_1_0033().new TreeNode(5);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[5, 2, 6, 1, 3, null, null]
        /**
         *              5
         *             / \
         *            2   6
         *           / \
         *          1   3
         *
         *
         */

//        int[] postorder = {1,6,3,2,5};
        //false
        int[] postorder = {1,3,2,6,5};
        //true
        boolean res = solution.verifyPostorder(postorder);
        System.out.println(res);
        //result
        //true
    }
}
