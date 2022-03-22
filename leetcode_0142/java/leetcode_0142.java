import java.util.LinkedList;
import java.util.List;

public class leetcode_0142 {
    public class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    public class Solution {
        public ListNode detectCycle(ListNode head) {
            //快慢指针
            //如果有环，快慢指针相遇后，分别从头节点跟相遇节点向前，直到相遇即为环的索引节点
            //可证明
            // --------
            //    |----|
            //设 a为环前一段，b为从环起点到相遇节点，c为从相遇节点到环起点
            //  2(a+b) = a+b+c+b -> a = c
            //如果无环，快指针则遇到nullptr返回
            if(head == null)
                return null;
            ListNode fast = head;
            ListNode slow = head;
            while(fast != null && fast.next != null){
                fast = fast.next.next;
                slow = slow.next;
                if(fast == slow)
                    break;
            }
            if(fast == null || fast.next == null)
                return null;
            //慢指针从头开始，快指针从相遇节点开始 用到证明 a = c
            slow = head;
            while(slow != fast){
                slow = slow.next;
                fast = fast.next;
            }
            return fast;

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
        Solution solution = new leetcode_0142().new Solution();
        ListNode head = new leetcode_0142().new ListNode(3);
        ListNode h1 = new leetcode_0142().new ListNode(2);
        ListNode h2 = new leetcode_0142().new ListNode(0);
        ListNode h3 = new leetcode_0142().new ListNode(-4);
        head.next = h1;h1.next = h2;h2.next = h3;h3.next = h1;
//        ListNode head = new leetcode_0142().new ListNode(1);
//        System.out.println(solution.detectCycle(head) == null);
        //result
        //true  无环 返回 null
        System.out.println(solution.detectCycle(head) == h1);
        //result
        //true  返回入环第一个节点
    }
}
