import java.util.LinkedList;
import java.util.List;

public class leetcode_0025 {
    static class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
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

    static class Solution {
        public static ListNode reverseKGroup(ListNode head, int k) {
            ListNode dummyHead = new ListNode();
            dummyHead.next = head;
            ListNode preL = dummyHead;
            ListNode cur = dummyHead;
            ListNode l,rSucc;
            while(cur != null){
                l = cur.next;
                for(int i = 1;i <= k && cur!=null;i++)
                    cur = cur.next;
                if(cur == null)
                    break;
                rSucc = cur.next;
                //截断要反转的链表
                cur.next = null;
                ListNode reverseHead = reverse(l);
                //拼接反转链表
                preL.next = reverseHead;
                l.next = rSucc;
                preL = l;
                cur = preL;
            }
            return dummyHead.next;
        }
        public static ListNode reverse(ListNode head){
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
    }

    public static void main(String[] args) {
        ListNode<Integer> head = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4,new ListNode(5)))));
        List<Integer> l = toList(head);
        printVec(l);
        int k = 2;
        ListNode anoHead = Solution.reverseKGroup(head,k);
        List<Integer> reverseL = toList(anoHead);
        printVec(reverseL);
        //result
//        [1,2,3,4,5]
//        [2,1,4,3,5]
    }
}
