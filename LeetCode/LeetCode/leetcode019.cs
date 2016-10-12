using System;

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 * 
 * Given linked list: 1->2->3->4->5, and n = 2.
   After removing the second node from the end, the linked list becomes 1->2->3->5.
 */

/*
ListNode的定义，在提交的时候不需要提交。
*/

namespace leetcode019 {

	public class ListNode {
		public int val;
		public ListNode next;
		public ListNode(int x) {
			val = x;
			next = null;
		}
	}

	public class Solution {
		public ListNode RemoveNthFromEnd(ListNode head, int n) {
			if (head == null || n < 0 ) {
				return head;
			}

			ListNode pre = head, aft = null;
			for (int i = 0; i < n; ++i) {
				pre = pre.next;
			}

			while (pre != null) {
				pre = pre.next;

				if (aft == null) {
					aft = head;
				} else {
					aft = aft.next;
				}
			}

			if (aft == null) {
				head = head.next;
			} else {
				aft.next = aft.next.next;
			}

			return head;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			ListNode head = null;
//			ListNode pre = null;
//
//			int[] p = { 1 };
//			int index = 1;
//			for (int i = 0; i < p.Length; ++i) {			
//				ListNode newNode = new ListNode (p[i]);
//				if (pre != null) {
//					pre.next = newNode;
//				}
//				if (head == null) {
//					head = newNode;
//				}
//				pre = newNode;
//			}
//
//			pre = head;
//			while (pre != null) {
//				Console.WriteLine (pre.val);
//				pre = pre.next;
//			}
//
//			Console.WriteLine ("~~~~~~~~~~~");
//			
//			Solution s = new Solution ();
//			head = s.RemoveNthFromEnd(head, index);
//
//			pre = head;
//			while (pre != null) {
//				Console.WriteLine (pre.val);
//				pre = pre.next;
//			}
//		}
//	}

}