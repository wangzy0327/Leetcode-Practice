import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class interview_0408 {
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
            //思路：递归求解：由于所有节点的值均为唯一的
            //递归左子树、右子树 ，如果存在p或q，则返回左子树根，或右子树根,否则返回null
            //如果递归返回的左右子树均不为null,则返回当前节点(说明p、q分别在左右子树找到了)
            //如果递归返回的左右子树任何一个为null,则返回当前节点
            if(root != null){
                TreeNode lNode = lowestCommonAncestor(root.left,p,q);
                TreeNode rNode = lowestCommonAncestor(root.right,p,q);
                if(lNode == null && root.val != p.val && root.val != q.val)
                    return rNode;
                else if(rNode == null && root.val != p.val && root.val != q.val)
                    return lNode;
                else{
                    //左右均不为null,说明 找到了了
                    //当前root.val == p.val || root.val == q.val
                    return root;
                }
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
        interview_0408.Solution solution = new interview_0408().new Solution();
        interview_0408.TreeNode root = new interview_0408().new TreeNode(3);
        interview_0408.TreeNode left = new interview_0408().new TreeNode(5);
        interview_0408.TreeNode right = new interview_0408().new TreeNode(1);
        interview_0408.TreeNode ll = new interview_0408().new TreeNode(6);
        interview_0408.TreeNode lr = new interview_0408().new TreeNode(2);
        interview_0408.TreeNode rl = new interview_0408().new TreeNode(0);
        interview_0408.TreeNode rr = new interview_0408().new TreeNode(8);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new interview_0408().new TreeNode(0);
//        lr.left = new interview_0408().new TreeNode(3);
        lr.left = new interview_0408().new TreeNode(7);
        lr.right = new interview_0408().new TreeNode(4);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
        interview_0408.TreeNode p = left;
        interview_0408.TreeNode q = right;
        TreeNode res = solution.lowestCommonAncestor(root, p, q);
        System.out.println(res.val);
        //result
        //3
    }
}
