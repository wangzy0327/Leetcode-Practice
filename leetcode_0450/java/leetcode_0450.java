import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0450 {
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
        public TreeNode deleteNode(TreeNode root, int key) {
            //1.找到指定节点(判断指定节点有无孩子) 若无孩子则直接返回
            //2.如果只有左孩子，返回左孩子，如果只有有孩子返回右孩子
            //3.如果左右两个孩子都有，则有两种结果
            //1).返回右节点，并将左子树放到右子树最小节点的左边
            //2).返回左节点，并将右子树放到左子树最大节点的右边
            //这里采用2)
            if (root == null)
                return null;
            else if (root.val > key) {
                //左子树寻找
                root.left = deleteNode(root.left, key);
                return root;
            } else if (root.val < key) {
                //右孩子寻找
                root.right = deleteNode(root.right, key);
                return root;
            } else {
                //root.val == key
                if (root.left == null) {
                    //左子树为空
                    TreeNode right = root.right;
                    root = null;
                    return right;
                } else if (root.right == null) {
                    //右子树为空
                    TreeNode left = root.left;
                    root = null;
                    return left;
                } else {
                    //左右子树均不为空
                    TreeNode left = root.left;
                    TreeNode right = root.right;
                    TreeNode rMin = minNode(right);
                    rMin.left = left;
                    root = null;
                    return right;
                }
            }
        }

        private TreeNode minNode(TreeNode root) {
            TreeNode node = root;
            while (node.left != null)
                node = node.left;
            return node;
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

        public void traversePreTree(StringBuilder sb, TreeNode root) {
            if (root != null) {
                sb.append(root.val + ",");
                traversePreTree(sb, root.left);
                traversePreTree(sb, root.right);
            }
        }

        public void printTree(TreeNode root) {
            StringBuilder res = new StringBuilder();
            traversePreTree(res, root);
            System.out.printf("[");
            String substring = res.substring(0, res.length() - 1);
            System.out.printf(substring);
            System.out.println("]");
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
        leetcode_0450.Solution solution = new leetcode_0450().new Solution();
        leetcode_0450.TreeNode root = new leetcode_0450().new TreeNode(5);
        leetcode_0450.TreeNode left = new leetcode_0450().new TreeNode(3);
        leetcode_0450.TreeNode right = new leetcode_0450().new TreeNode(6);
        leetcode_0450.TreeNode ll = new leetcode_0450().new TreeNode(2);
        leetcode_0450.TreeNode lr = new leetcode_0450().new TreeNode(4);
        leetcode_0450.TreeNode rl = null;
        leetcode_0450.TreeNode rr = new leetcode_0450().new TreeNode(7);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        root = [5,3,6,2,4,null,7], key = 3
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        int key = 3;
        TreeNode anoNode = solution.deleteNode(root, key);
        List<String> anoStr = solution.levelOrderStr(anoNode);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
//        [5,4,6,2,null,null,7]
    }
}
