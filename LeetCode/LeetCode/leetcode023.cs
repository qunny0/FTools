using System;
using System.Collections.Generic;



// # 1. [[]]

namespace LeetCode
{
	public class leetcode023
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
			public ListNode MergeKLists(ListNode[] lists) {
				ListNode root = null;

				if (lists == null) {
					return root;
				}

				int nlists = lists.Length;
				if (nlists == 0) {
					return root;					
				}

				ListNode pTmp = null;
				ListNode[] rootlists = new ListNode[nlists];
				for (int i = 0; i < nlists; ++i) {
					rootlists [i] = lists [i];
				}

				bool allempty = false;

				do {

					allempty = true;
					for (int i = 0; i < nlists; ++i) {
						if (rootlists [i] != null) {
							allempty = false;
							break;
						}
					}

					if(!allempty){
						
						int minNumIndex = 0;
						int minNum = 0;
						int idx = 0;
						bool init = false;
						do {
							if(!allempty){

							}

							if(rootlists[idx] == null){
								++idx;
								continue;
							}

							if(!init){
								init = true;
								minNumIndex = idx;
								minNum = rootlists[idx].val;
							}
							else {
								int tmpNum = rootlists[idx].val;
								if(tmpNum < minNum){
									minNum = tmpNum;
									minNumIndex = idx;
								}
							}

							++idx;
						} while(idx < nlists);

						ListNode pNewNode = new ListNode(minNum);
						if(pTmp == null){
							pTmp = pNewNode;
						}
						else{
							pTmp.next = pNewNode;
							pTmp = pNewNode;
						}

						if (root == null){
							root = pTmp;
						}

						rootlists[minNumIndex] = rootlists[minNumIndex].next;					
					}

				} while(!allempty);

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

			public static void Main (string[] args)
			{
				Solution s = new Solution();

				ListNode[] test1 = new ListNode[2];
				int[] test1_0 = { 1, 3, 5, 7 };
				int[] test1_1 = { 2, 3, 6, 8 };
				test1 [0] = createListByArray (test1_0);
				test1 [1] = createListByArray (test1_1);

//				test1 [0].print ();
//				test1 [1].print ();

				ListNode[] test2 = new ListNode[1];

				test2 [0] = null;

				ListNode proot = s.MergeKLists (test2);
				if (proot != null) {
					proot.print ();
				}
			}
		}
	}
}

