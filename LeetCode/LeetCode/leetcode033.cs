using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 TLE [1, 3] 0
 * # 2 {3, 1} 1
*/

namespace LeetCode
{
	public class leetcode033
	{
		public class Solution {
			public int Search(int[] nums, int target) {
				int pivot = findPivot(nums, 0, nums.Length);

				int l = 0;
				int r = nums.Length-1;
				while (true) {
					if (l > r) {
						return -1;
					}

					int tmpl = l + pivot;
					int tmpr = r + pivot;
					int tmpm = (tmpl + tmpr) / 2;
					tmpl = tmpl >= nums.Length ? tmpl -= nums.Length : tmpl;
					tmpr = tmpr >= nums.Length ? tmpr -= nums.Length : tmpr;
					tmpm = tmpm >= nums.Length ? tmpm -= nums.Length : tmpm;

//					if (tmpl > tmpr) {
//						return -1;
//					}

					int vm = nums [tmpm];

					if (vm == target) {
						return tmpm;
					}

					if (tmpl == tmpr) {
						return -1;
					}

					if (target > vm) {
						l = (l+r)/2 + 1;
						continue;
					} else {
						r = (l+r)/2 - 1;
						continue;
					}
				}
			}

			// [l, r)
			public int findPivot(int[] nums, int l, int r) {
				int lv = nums [l];
				int rv = nums [r-1];
				if (lv < rv) {
					return l;
				}

				int m = (l + r) / 2;
				int mv = nums [m];

				if (m == nums.Length - 1) {
					return m;
				}
				if (mv <= nums [m - 1] && mv <= nums [m + 1]) {
					return m;
				}

				if (mv >= rv) {
					return findPivot (nums, m + 1, r);
				}

				if (mv >= lv) {
					return findPivot (nums, m + 1, r);
				}

				return findPivot (nums, l, m);
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				int [] test = {3, 1};
//				int tt = 3;
//
////				int ttr = s.findPivot (test, 0, test.Length);
//
//				int res = s.Search (test, tt);
//				Console.WriteLine ("" + res);
//			}
//		}
	}
}

