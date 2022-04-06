import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class offer_1_0036 {
    class Node {
        public int val;
        public Node left;
        public Node right;

        public Node() {}

        public Node(int _val) {
            val = _val;
        }

        public Node(int _val,Node _left,Node _right) {
            val = _val;
            left = _left;
            right = _right;
        }
    };
    class Solution {
        public Node treeToDoublyList(Node root) {
            head = null;
            pre = null;
            if(root == null)
                return null;
            //中序遍历，保留前一个节点，修改当前节点的左子树指向(左子树已经遍历完可修改)和前一个节点的右子树指向
            inOrderHelper(root);
            //最后将首尾节点衔接在一起
            head.left = pre;
            pre.right = head;
            return head;
        }
        private Node head;
        private Node pre;
        private void inOrderHelper(Node root){
            if(root != null){
                inOrderHelper(root.left);
                if(pre == null){
                    pre = root;
                    head = root;
                }else{
                    pre.right = root;
                    root.left = pre;
                    pre = root;
                }
                inOrderHelper(root.right);
            }
        }
        public void printDoublyList(Node head){
            Node cur = head;
            if(cur == null){
                System.out.println("[]");
                return ;
            }
            System.out.printf("[");
            while(cur.right != head){
                System.out.printf("%d->",cur.val);
                cur = cur.right;
            }
            System.out.println(cur.val+"]");
        }
        public List<List<Integer>> levelOrder(Node root) {
            List<Node> cur = new ArrayList();
            List<Node> next = new ArrayList();
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

        public List<String> levelOrderStr(Node root) {
            List<Node> cur = new ArrayList();
            List<Node> next = new ArrayList();
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
                    Node left = cur.get(i).left;
                    Node right = cur.get(i).right;
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
        offer_1_0036.Solution solution = new offer_1_0036().new Solution();
        offer_1_0036.Node root = new offer_1_0036().new Node(4);
        offer_1_0036.Node left = new offer_1_0036().new Node(2);
        offer_1_0036.Node right = new offer_1_0036().new Node(5);
        offer_1_0036.Node ll = new offer_1_0036().new Node(1);
        offer_1_0036.Node lr = new offer_1_0036().new Node(3);
//        offer_1_0036.Node rl = new offer_1_0036().new Node(7);
//        offer_1_0036.Node rr = new offer_1_0036().new Node(9);
        left.left = ll;
        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        lr.left = new offer_1_0036().new Node(3);
//        lr.left = new offer_1_0036().new Node(5);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[4, 2, 5, 1, 3, null, null]
        Node head = solution.treeToDoublyList(root);
        solution.printDoublyList(head);
        //result
        //[1->2->3->4->5]
    }
}
