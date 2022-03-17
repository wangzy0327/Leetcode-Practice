import java.util.LinkedList;
import java.util.List;

public class offer_0024 {
    static class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val,ListNode next) {this.val = val;this.next = next;}
    }
    static class Solution{
        public static ListNode reverseList(ListNode head){
            ListNode pre = null;
            ListNode cur = head;
            while(cur != null){
                ListNode next = cur.next;
                cur.next = pre;
                pre = cur;
                cur = next;
            }
            return pre;
        }
        public static ListNode reverseList2(ListNode head){
            if(head == null || head.next == null)
                return head;
            ListNode ret = reverseList2(head.next);
            head.next.next = head;
            head.next = null;
            return ret;
        }
    };
    public static <T> void printVec(List<T> list){
        String res = "[";
        for(T ele : list){
            res += ele+",";
        }
        res = res.substring(0,res.length() - 1);
        res += "]";
        System.out.println(res);
    }

    public static <T> List<T> toList(ListNode head){
        List<T> list = new LinkedList<T>();
        ListNode cur = head;
        while(cur != null){
            list.add((T) cur.val);
            cur = cur.next;
        }
        return list;
    }

    public static void main(String[] args) {
        ListNode<Integer> head = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4,new ListNode(5)))));
        List<Integer> l = toList(head);
        printVec(l);
        ListNode anoHead = Solution.reverseList(head);
        List<Integer> reverseL = toList(anoHead);
        printVec(reverseL);
    }
}


