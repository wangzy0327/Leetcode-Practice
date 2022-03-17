import java.util.LinkedList;
import java.util.List;

public class leetcode_0082 {
    class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    class Solution {
        public ListNode deleteDuplicates(ListNode head) {
            ListNode dummyHead = new ListNode();
            dummyHead.next = head;
            ListNode cur = dummyHead;
            while(cur.next != null){
                ListNode next1 = cur.next;
                ListNode next2 = next1.next;
                if(next1 != null && next2 != null && next1.val != next2.val
                        || next1 != null && next2 == null){
                    cur = cur.next;
                }else{
                    while(next1 != null && next2 != null && next1.val == next2.val){
                        next1 = next1.next;
                        next2 = next2.next;
                    }
                    cur.next = next2;
                }
            }
            return dummyHead.next;
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

        public  <T> List<T> toList(ListNode head){
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
        Solution solution = new leetcode_0082().new Solution();
        ListNode head = new leetcode_0082().new ListNode(1,new leetcode_0082().new ListNode(2,new leetcode_0082().new ListNode(3,new leetcode_0082().new ListNode(3,new leetcode_0082().new ListNode(4,new leetcode_0082().new ListNode(4,new leetcode_0082().new ListNode(5)))))));
        solution.deleteDuplicates(head);
        List<Integer> list = solution.toList(head);
        solution.printList(list);
        //result
        //[1,2,5]
    }
}
