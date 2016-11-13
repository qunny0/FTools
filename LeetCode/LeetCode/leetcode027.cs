using System;
using System.Collections.Generic;


// # 1. [1, 1, 2] [1, 2] ; [1, 1]
// 返回无重复的数组元素长度n，修改nums，前n个数组为不重复的元素

namespace LeetCode
{
	public class leetcode027
	{
		public class Solution {
			public int RemoveElement(int[] nums, int val) {
				if (nums == null || nums.Length == 0) {
					return 0;
				}

				int res = 0;
				int tIdx = 0;
				for (int i = 0; i < nums.Length; ++i) {
					if (val == nums [i]) {
						continue;
					} else {
						++res;
						nums [tIdx] = nums[i];
						++tIdx;
					}
				}

				return res;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
//				int[] test1_0 = { 1, 1, 2 };
//				int[] test1_1 = {  };
//
//				int res = s.RemoveElement (test1_0, 1);
//				Console.WriteLine ("" + res);
//			}
//		}
	}
}

