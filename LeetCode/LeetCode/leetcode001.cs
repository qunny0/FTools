using System;
using System.Collections;

namespace leetcode001 {
	public class Solution {
//		Hash Table
		public int[] TwoSum(int[] nums, int target) {
			Hashtable ht = new Hashtable();

			for (int i = 0; i < nums.Length; ++i) {
				if (!ht.ContainsKey (nums[i])) {
					ht.Add (nums[i], i);
				}
			}
			int[] retArray = new int[2];
			for (int i = 0; i < nums.Length; ++i) {
				int tgt = target - nums [i];
				if (ht.ContainsKey (tgt) && i != (int)ht[tgt]) {
					retArray [0] = i;
					retArray [1] = (int)ht[tgt];
					break;
				}
			}

			Console.WriteLine (" -- " + retArray [0] + ", " + retArray [1]);

			return retArray;
		}
	}

	//class MainClass
	//{
	//	public static void Main (string[] args)
	//	{
	//		int[] nums = {0,4,3,0};
	//		int target = 0;
	//
	//		Solution s = new Solution ();
	//		s.TwoSum(nums, target);
	//	}
	//}

}