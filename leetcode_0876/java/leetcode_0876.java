import java.util.LinkedList;
import java.util.List;

public class leetcode_0876 {
    public class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    class Solution {
        public ListNode middleNode(ListNode head) {
            //快慢指针
            ListNode fast = head;
            ListNode slow = head;
            while(fast!=null && fast.next!=null){
                slow = slow.next;
                fast = fast.next.next;
            }
            return slow;
        }
        public <T> void printVec(List<T> list){
            String res = "[";
            for(T ele : list){
                res += ele+",";
            }
            res = res.substring(0,res.length() - 1);
            res += "]";
            System.out.println(res);
        }

        public <T> List<T> toList(ListNode head){
            List<T> list = new LinkedList<T>();
            ListNode cur = head;
            while(cur != null){
                list.add((T) cur.val);
                cur = cur.next;
            }
            return list;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0876().new Solution();
        ListNode head = new leetcode_0876().new ListNode(1);
        ListNode h1 = new leetcode_0876().new ListNode(2);
        ListNode h2 = new leetcode_0876().new ListNode(3);
        ListNode h3 = new leetcode_0876().new ListNode(4);
        ListNode h4 = new leetcode_0876().new ListNode(5);
        head.next = h1;h1.next = h2;h2.next = h3;h3.next = h4;
        ListNode res = solution.middleNode(head);
        System.out.println(res == h2);

        /**
         * 输入：[1,2,3,4,5]
         * 输出：此列表中的结点 3 (序列化形式：[3,4,5])
         * 返回的结点值为 3 。 (测评系统对该结点序列化表述是 [3,4,5])。
         * 注意，我们返回了一个 ListNode 类型的对象 ans，这样：
         * ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, 以及 ans.next.next.next = NULL.
         *
         */
    }
}
