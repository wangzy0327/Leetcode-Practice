import java.util.LinkedList;
import java.util.List;

public class leetcode_0141 {
    public class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    public class Solution {
        public boolean hasCycle(ListNode head) {
            if(head == null)
                return false;
            //快慢双指针 是否重合
            ListNode fast = head.next;
            ListNode slow = head;
            while(fast != null && fast.next != null){
                if(fast == slow)
                    return true;
                fast = fast.next.next;
                slow = slow.next;
            }
            return false;
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
        Solution solution = new leetcode_0141().new Solution();
//        ListNode head = new leetcode_0141().new ListNode(3);
//        ListNode h1 = new leetcode_0141().new ListNode(2);
//        ListNode h2 = new leetcode_0141().new ListNode(0);
//        ListNode h3 = new leetcode_0141().new ListNode(-4);
//        head.next = h1;h1.next = h2;h2.next = h3;h3.next = h1;
        ListNode head = new leetcode_0141().new ListNode(1);
        System.out.println(solution.hasCycle(head));
    }
}
