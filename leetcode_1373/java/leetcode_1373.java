import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_1373 {
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
        public int maxSumBST(TreeNode root) {
            //每个子树返回最大和最小值
            //然后比较左右子树的最大最小值来确定是否为BST,每层递归需要保存最大最小节点，是否为BST，BST的累加和，4个状态
            //初始化
            ans = 0;
            minNode = null;
            maxNode = null;
            helper(root);
            return ans;
        }
        //当前子树最大最小节点
        private TreeNode minNode;
        private TreeNode maxNode;
        private int ans;
        //每次递归返回需要保存当前子树是否是BST以及其BST累加和
        //返回是否是BST用1或0表示
        private int[] helper(TreeNode root){
            //第一个元素保存是否为BST,第二个元素保存累加和
            if(root != null){
                //后序遍历
                int[] lRes = helper(root.left);
                TreeNode lMinNode = minNode;
                TreeNode lMaxNode = maxNode;
                //为了不影响右子树的最大最小节点，重置TreeNode值
                minNode = null;maxNode = null;
                int[] rRes = helper(root.right);
                TreeNode rMinNode = minNode;
                TreeNode rMaxNode = maxNode;
                //如果左右子树有一个不是BST则直接返回
                if(lRes[0]==0 || rRes[0]==0 )
                    return new int[]{0,-1};
                //左子树最大值大于等于当前节点值 或 右子树最小值小于等于当前节点值 直接返回
                if(lMaxNode != null && lMaxNode.val >= root.val
                        || rMinNode != null && rMinNode.val <= root.val)
                    return new int[]{0,-1};
                //否则，更新当前子树最大节点和最小节点
                minNode = lMinNode!=null?lMinNode:root;
                maxNode = rMaxNode!=null?rMaxNode:root;
                //当前是BST，更新累加和
                int sum = root.val + lRes[1] + rRes[1];
                ans = Math.max(sum,ans);
                return new int[]{1,sum};
            }
            //空节点返回1,0
            return new int[]{1,0};
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
    class Solution2 {
        public int maxSumBST(TreeNode root) {
            /**
             后序遍历，递归函数traverse()返回一个int[]，长度为4，每个元素分别代表：
             以root为根节点的二叉树是否为二叉搜索树（是为1，不是为0）
             以root为根节点的二叉树中的最小节点值
             以root为根节点的二叉树中的最大节点值
             以root为根节点的二叉树中的所有节点值之和
             ans为全局变量，维护全局最大值，也是最终返回的结果
             */
            //初始化为0
            ans = 0;
            helper(root);
            return ans;
        }
        private int ans;
        private int[] helper(TreeNode root){
            if(root != null){
                int[] lRes = helper(root.left);
                int[] rRes = helper(root.right);
                //如果左子树或右子树非BST,或者 不满足当前节点大于左子树最大节点/当前节点小于右子树最小节点
                if(lRes[0] == 0 || rRes[0] == 0 || root.val <= lRes[2] || root.val >= rRes[1])
                    return new int[]{0,Integer.MAX_VALUE,Integer.MIN_VALUE,0};
                //否则满足BST 更新当前子树的最大/最小值 及 累加和
                int minValue = Math.min(lRes[1],root.val);
                int maxValue = Math.max(rRes[2],root.val);
                int sum = root.val+lRes[3]+rRes[3];
                ans = Math.max(ans,sum);
                return new int[]{1,minValue,maxValue,sum};
            }
            //如果为空节点,则返回的是[1,Integer.MAX_VALUE,Integer.MIN_VALUE,0]
            return new int[]{1,Integer.MAX_VALUE,Integer.MIN_VALUE,0};
        }
    }
    public static void main(String[] args) {
        leetcode_1373.Solution solution = new leetcode_1373().new Solution();
        leetcode_1373.Solution2 solution2 = new leetcode_1373().new Solution2();
        leetcode_1373.TreeNode root = new leetcode_1373().new TreeNode(1);
        leetcode_1373.TreeNode left = new leetcode_1373().new TreeNode(4);
        leetcode_1373.TreeNode right = new leetcode_1373().new TreeNode(3);
        leetcode_1373.TreeNode ll = new leetcode_1373().new TreeNode(2);
        leetcode_1373.TreeNode lr = new leetcode_1373().new TreeNode(4);
        leetcode_1373.TreeNode rl = new leetcode_1373().new TreeNode(2);
        leetcode_1373.TreeNode rr = new leetcode_1373().new TreeNode(5);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new leetcode_1373().new TreeNode(0);
//        lr.left = new leetcode_1373().new TreeNode(3);
        rr.left = new leetcode_1373().new TreeNode(4);
        rr.right = new leetcode_1373().new TreeNode(6);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [1, 4, 3, 2, 4, 2, 5, null, null, null, null, null, null, 4, 6]
        int res1 = solution.maxSumBST(root);
        System.out.println(res1);
        //result
        //20
        int res2 = solution.maxSumBST(root);
        System.out.println(res2);
        //result
        //20
    }
}
