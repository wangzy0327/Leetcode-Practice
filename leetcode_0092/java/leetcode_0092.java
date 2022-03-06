import java.util.LinkedList;
import java.util.List;

public class leetcode_0092 {
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
        public static ListNode reverseBetween(ListNode head, int left, int right) {
            //1.找到反转左侧、右侧位置节点截取
            //2.反转链表段，然后接上
            ListNode dummyHead = new ListNode();
            dummyHead.next = head;
            ListNode l = null;
            //考虑到要保存左节点的前一个节点，所以这里创建一个虚拟头结点
            ListNode cur = dummyHead;
            //移动到left的前一个位置,从1移动到left位置需要left - 1 步
            for(int i = 1;i < left;i++)
                cur = cur.next;
            ListNode lPre = cur;
            cur = cur.next;
            l = cur;
            for(int i = left;i < right;i++)
                cur = cur.next;
            ListNode rSucc = cur.next;
            ListNode r = cur;
            r.next = null;
            ListNode reverseHead = reverse(l);
            l.next = rSucc;
            lPre.next = reverseHead;
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
        int left = 2;
        int right = 4;
        ListNode anoHead = Solution.reverseBetween(head,left,right);
        List<Integer> reverseL = toList(anoHead);
        printVec(reverseL);
    }
}
