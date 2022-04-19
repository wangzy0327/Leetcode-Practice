import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class leetcode_0222 {
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
        public int countNodes(TreeNode root) {
            //思路：由于是完全二叉树，所以最左边节点一定是最底层的
            // 最底层包含的节点数最少为 1，最多为 2^h
            //重点是 如何找到完全二叉树最后一层节点对应是哪一个，这里采用二分搜索来找到对应的元素
            /**
             如何判断第 k 个节点是否存在呢？如果第 k 个节点位于第 h 层，则 k 的二进制表示包含 h+1 位，其中最高位是 1，其余各位从高到低表示从根节点到第 k 个节点的路径，0 表示移动到左子节点，1 表示移动到右子节点。通过位运算得到第 k 个节点对应的路径，判断该路径对应的节点是否存在，即可判断第 k 个节点是否存在
             ep:12 = 1100  (根节点为1，向右为1，向左为0)
             1
             2        3
             4    5     6    7
             8  9 10 11 12 13 14 15
             */
            if(root == null)
                return 0;
            int h = 0;
            TreeNode cur = root;
            while(cur.left != null){
                cur = cur.left;
                h++;
            }
            //左侧边界(包含)，右侧边界(不包含)
            int left = 1<<h;int right = 1<<(h+1);
            //[left,right) 终止条件 left == right
            //找出最底层 最右端的元素位置
            //向右偏移
            while(left < right){
                int mid = left + (right - left)/2;
                if(exist(root,h,mid)){
                    left = mid + 1;
                }else{
                    right = mid;
                }
            }
            return left - 1;
        }
        //判断对应元素是否存在
        private boolean exist(TreeNode root,int h,int num){
            //刨除首位0/1
            //防止树只有一层 h 为0，h-1小于0
            int bits = (h-1 < 0)?0:(1<<(h-1));
            TreeNode cur = root;
            while(cur != null && bits != 0){
                if((bits & num) == 0){
                    cur = cur.left;
                }else{
                    cur = cur.right;
                }
                bits >>= 1;
            }
            return cur != null;
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
        leetcode_0222.Solution solution = new leetcode_0222().new Solution();
        leetcode_0222.TreeNode root = new leetcode_0222().new TreeNode(1);
        leetcode_0222.TreeNode left = new leetcode_0222().new TreeNode(2);
        leetcode_0222.TreeNode right = new leetcode_0222().new TreeNode(3);
        leetcode_0222.TreeNode ll = new leetcode_0222().new TreeNode(4);
        leetcode_0222.TreeNode lr = new leetcode_0222().new TreeNode(5);
        leetcode_0222.TreeNode rl = new leetcode_0222().new TreeNode(6);
        leetcode_0222.TreeNode rr = null;
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new leetcode_0222().new TreeNode(0);
//        lr.left = new leetcode_0222().new TreeNode(3);
//        lr.left = new leetcode_0222().new TreeNode(7);
//        lr.right = new leetcode_0222().new TreeNode(4);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        // root = [1, 2, 3, 4, 5, 6, null]
        int res = solution.countNodes(root);
        System.out.println(res);
        //result
        //6
    }
}
