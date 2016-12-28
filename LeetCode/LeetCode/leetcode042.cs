using System;
using System.Collections;
using System.Collections.Generic;

// #1 [5,4,1,2]

namespace LeetCode
{
	public class leetcode042
	{
		public class Solution {
			public int Trap(int[] height) {
				int res = 0;
				if (height.Length <= 2) {
					return res;
				}

				int [] leftMax = new int[height.Length];
				int tmpMax = 0;
				for (int i = 0; i < height.Length; ++i) {
					leftMax [i] = tmpMax;
					tmpMax = Math.Max (tmpMax, height [i]);
				}

				tmpMax = height [height.Length - 1];
				for (int j = height.Length - 2; j >= 1; --j) {
					int tmpMin = Math.Min (tmpMax, leftMax [j]);
					if (tmpMin > height [j]) {
						res = tmpMin - height [j];
					}
					tmpMax = Math.Max (tmpMax, height [j]);
				}

				return res;
			}

			protected int calTrap(int[] height, int s, int e) {
				int min = Math.Min (height [s], height [e]);
				int res = 0;

				for (int i = s + 1; i < e; ++i) {
					if (min > height [i]) {
						res += (min - height [i]);
					}
				}

				Console.WriteLine ("" + s + ", " + e + ", " + res);
				return res;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
////				int[] t1 = {5,2,1,4,1,2};
//				int[] t2 = {0,1,0,2,1,0,1,3,2,1,2,1};
//
//				int res = s.Trap (t2);
//				Console.WriteLine (res);
//			}
//		}
	}
}

