using System;
using System.Collections.Generic;

namespace LeetCode
{
	public class leetcode025
	{
//		Definition for singly-linked list.
		public class ListNode {
 			public int val;
 			public ListNode next;
 			public ListNode(int x) { val = x; }

			public void print() {
				ListNode p = this;
				while (p != null) {
					Console.Write (p.val + ", ");
					p = p.next;
				}
				Console.WriteLine ("");
			}
 		}

 		public class Solution {
			public ListNode ReverseKGroup(ListNode head, int k) {
				if (head == null) {
					return head;
				}

				if (k == 1) {
					return head;
				}

				ListNode root = null;
				ListNode pNode = head;
				ListNode[] pTmps = new ListNode[k];

				int i = 0;
				for (i = 0; i < k; ++i) {
					if (pNode == null) {
						return head;
					}
					pTmps [i] = pNode;
					pNode = pNode.next;
				}

				ListNode aft = pTmps [i - 1].next;
				ListNode pre = null;

				while (true) {
					if (root == null) {
						root = pTmps [k - 1];
					} else {
						pre.next = pTmps [k - 1];
					}

					for (i = k-1; i > 0; --i) {
						pTmps [i].next = pTmps [i - 1];
					}
					pTmps [0].next = aft;
					pre = pTmps [0];

					bool jumpout = false;
					for (i = 0; i < k; ++i) {
						if (pNode == null) {
							jumpout = true;
							break;
						}
						pTmps [i] = pNode;
						pNode = pNode.next;
					}
					if (jumpout) {
						break;
					}
					aft = pTmps [i - 1].next;
				}

				return root;
			}
		}

		class MainClass
		{
			public static ListNode createListByArray(int [] nums) {
				ListNode root = null;
				ListNode pTmp = null;
		
				for (int i = 0; i < nums.Length; ++i) {
					ListNode p = new ListNode (nums [i]);

					if (pTmp == null) {
						pTmp = p;
					} else {
						pTmp.next = p;
						pTmp = p;
					}

					if (root == null) {
						root = p;
					}
				}

				return root;
			}

//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
//				ListNode[] test1 = new ListNode[2];
//				int[] test1_0 = { 1, 2, 3, 4 };
//				int[] test1_1 = {  };
//				test1 [0] = createListByArray (test1_0);
//				test1 [1] = createListByArray (test1_1);
//
//				ListNode proot = s.ReverseKGroup (test1[1], 3);
//				if (proot != null) {
//					proot.print ();
//				}
//			}
		}
	}
}

