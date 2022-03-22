import java.util.LinkedList;
import java.util.List;

public class offer_0022 {
    public class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    class Solution {
        public ListNode getKthFromEnd(ListNode head, int k) {
            //快慢指针
            ListNode fast = head;
            ListNode slow = head;
            int i = 0;
            while(i < k && fast != null){
                fast = fast.next;
                i++;
            }
            while(fast != null){
                fast = fast.next;
                slow = slow.next;
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
        Solution solution = new offer_0022().new Solution();
        ListNode head = new offer_0022().new ListNode(1);
        ListNode h1 = new offer_0022().new ListNode(2);
        ListNode h2 = new offer_0022().new ListNode(3);
        ListNode h3 = new offer_0022().new ListNode(4);
        ListNode h4 = new offer_0022().new ListNode(5);
        head.next = h1;h1.next = h2;h2.next = h3;h3.next = h4;
        int k = 2;
        ListNode res = solution.getKthFromEnd(head,k);
        List<Integer> li = solution.toList(head);
        solution.printVec(li);
        List<Integer> resList = solution.toList(res);
        solution.printVec(resList);
        //[1,2,3,4,5]
        //[4,5]

        /**
         * 给定一个链表: 1->2->3->4->5, 和 k = 2.
         *
         * 返回链表 4->5.
         *
         */
    }
}
