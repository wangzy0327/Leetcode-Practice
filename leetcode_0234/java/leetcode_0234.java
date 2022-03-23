import java.util.LinkedList;
import java.util.List;

public class leetcode_0234 {
    public class ListNode<T>{
        T val;
        ListNode next;
        ListNode(){}
        ListNode(T val) {this.val = val;}
        ListNode(T val, ListNode next) {this.val = val;this.next = next;}
    }
    public class Solution {
        public boolean isPalindrome(ListNode head) {
            //这里采用快慢指针找到 第二段的起始位置节点
            // 1->2->3->2->1  找到 3
            // 1->2->2->1    找到2
            // 然后就地反转 找到的第二段位置
            // 1->2->2->null  1->2->null
            // 1->2->3->null  1->2->3->null
            //然后判断 是否为回文
            //最后将 第二段反转 保持原链表 顺序
            // 1->2->2->1
            // 1->2->3->2->1
            ListNode fast = head;
            ListNode slow = head;
            while(fast != null && fast.next != null){
                fast = fast.next.next;
                slow = slow.next;
            }
            ListNode ano = reverse(slow);
            fast = head;slow = ano;
            while(slow != null && fast != null){
                if(slow.val != fast.val)
                    break;
                slow = slow.next;
                fast = fast.next;
            }
            //再反转链表，保持原链表顺序
            reverse(ano);
            if(slow != null && fast != null)
                return false;
            else
                return true;

        }
        private ListNode reverse(ListNode node){
            ListNode pre = null;
            ListNode cur = node;
            while(cur != null){
                ListNode next = cur.next;
                cur.next = pre;
                pre = cur;
                cur = next;
            }
            return pre;
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
        Solution solution = new leetcode_0234().new Solution();
        ListNode head = new leetcode_0234().new ListNode(1);
        ListNode h1 = new leetcode_0234().new ListNode(2);
        ListNode h2 = new leetcode_0234().new ListNode(3);
        head.next = h1;h1.next = h2;
        List<Integer> l1 = solution.toList(head);
        solution.printVec(l1);
        System.out.println(solution.isPalindrome(head));
        List<Integer> l2 = solution.toList(head);
        solution.printVec(l2);
    }
}
