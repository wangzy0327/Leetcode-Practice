import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class offer_1_0068_1 {
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
        public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
            //因为p,q节点均存在在树中，且在BST中可以确定其在哪个子树里
            //分为3中情况:
            //1、如果p在root的左子树中，q在root的右子树中，则返回root
            //2、如果p、q均在root的左子树中,则递归返回左子树的调用
            //3、如果p、q均在root的右子树中,则递归返回右子树的调用
            if(p.val <= root.val && q.val >= root.val || p.val >= root.val && q.val <= root.val)
                return root;
            else if(p.val < root.val && q.val < root.val)
                return lowestCommonAncestor(root.left,p,q);
            else
                // if (p.val > root.val && q.val > root.val)
                return lowestCommonAncestor(root.right,p,q);

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
        offer_1_0068_1.Solution solution = new offer_1_0068_1().new Solution();
        offer_1_0068_1.TreeNode root = new offer_1_0068_1().new TreeNode(6);
        offer_1_0068_1.TreeNode left = new offer_1_0068_1().new TreeNode(2);
        offer_1_0068_1.TreeNode right = new offer_1_0068_1().new TreeNode(8);
        offer_1_0068_1.TreeNode ll = new offer_1_0068_1().new TreeNode(0);
        offer_1_0068_1.TreeNode lr = new offer_1_0068_1().new TreeNode(4);
        offer_1_0068_1.TreeNode rl = new offer_1_0068_1().new TreeNode(7);
        offer_1_0068_1.TreeNode rr = new offer_1_0068_1().new TreeNode(9);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        lr.left = new offer_1_0068_1().new TreeNode(3);
        lr.left = new offer_1_0068_1().new TreeNode(5);
//      root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
        //[6, 2, 8, 0, 4, 7, 9, null, null, 5, null, null, null, null, null]
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        TreeNode ancestor = solution.lowestCommonAncestor(root, left, right);
        System.out.println(ancestor.val);
        //result
        //6
    }
}
