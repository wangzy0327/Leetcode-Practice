import java.util.LinkedList;
import java.util.List;

public class leetcode_0083 {
    class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    class Solution {
        public ListNode deleteDuplicates(ListNode head) {
            ListNode cur = head;
            if(cur == null)
                return null;
            while(cur.next != null){
                ListNode next = cur.next;
                if(cur.val == next.val){
                    cur.next = next.next;
                    next = null;
                }else{
                    cur = next;
                }
            }
            return head;
        }
        public  <T> void printVec(List<T> list){
            String res = "[";
            for(T ele : list){
                res += ele+",";
            }
            res = res.substring(0,res.length() - 1);
            res += "]";
            System.out.println(res);
        }

        public  <T> void printList(List<T> list){
            String res = "[";
            for(T ele : list){
                res += ele+",";
            }
            res = res.substring(0,res.length() - 1);
            res += "]";
            System.out.println(res);
        }

        public  <T> List<T> toList(leetcode_0083.ListNode head){
            List<T> list = new LinkedList<T>();
            leetcode_0083.ListNode cur = head;
            while(cur != null){
                list.add((T) cur.val);
                cur = cur.next;
            }
            return list;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0083().new Solution();
        ListNode head = new leetcode_0083().new ListNode(1,new leetcode_0083().new ListNode(1,new leetcode_0083().new ListNode(2,new leetcode_0083().new ListNode(3,new leetcode_0083().new ListNode(3)))));
        solution.deleteDuplicates(head);
        List<Integer> list = solution.toList(head);
        solution.printList(list);
        //result
        //[1,2,3]
    }
}
