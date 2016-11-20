using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 : 【1， 3， 2】
 * # 1 : 【1， 3， 2】
 * # 3 : 【2， 3， 1】
 * # 4 : [5,4,7,5,3,2]
 * 
 * 
*/

namespace LeetCode
{
	public class leetcode031
	{
		public class Solution {
			public void NextPermutation(int[] nums) {
				if (nums.Length == 0) {
					return;
				}

				int idx = 0;
				for (idx = nums.Length -1; idx > 0; --idx) {
					if (nums [idx] > nums [idx - 1]) {
						break;
					}
				}

				if (idx == 0) {
					// fan zhuang
					for (int i = 0; i < nums.Length / 2; ++i) {
						int k = nums.Length - i - 1;
						int tmp = nums [i];
						nums [i] = nums [k];
						nums [k] = tmp;
					}

				} else {
					int minIdx = idx - 1;
					int minTmpIdx = idx;
					int minTmp = nums [minTmpIdx];
					for (int i = idx + 1; i < nums.Length; ++i) {
						if (nums [i] > nums[minIdx] && nums [i] < minTmp) {
							minTmpIdx = i;
							minTmp = nums [minTmpIdx];
						}
					}

					int tmp = nums[minIdx];
					nums [minIdx] = nums [minTmpIdx];
					nums [minTmpIdx] = tmp;

					// sort (minIdx, nums.len)
					int b = minIdx + 1;
					int e = nums.Length;
					for (int i = b; i < nums.Length; ++i) {
						bool change = false;
						for (int j = b; j < nums.Length - 1; ++j) {
							if (nums [j] > nums [j + 1]) {
								int t = nums [j];
								nums [j] = nums [j + 1];
								nums [j + 1] = t;
								change = true;
							}
						}
						if (!change) {
							break;
						}
					}
				}
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
////				int[] t1 = { 1, 2, 1 };
//				int[] t1 = { 5, 4, 7, 5, 3, 2 };
////				int[] t1 = { 3, 2, 1 };
//
//				s.NextPermutation (t1);
//
//				Array.ForEach<int> (t1, (k) => Console.Write (k + ","));
//				Console.WriteLine ();
//			}
//		}
	}
}

