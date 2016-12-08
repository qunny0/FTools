using System;
using System.Collections;
using System.Collections.Generic;

/*
 * 5 - 111221 
 * 6 - 312211
*/

namespace LeetCode
{
	public class leetcode039
	{
		public class Solution {
			public IList<IList<int>> CombinationSum(int[] candidates, int target) {
				_res = new List<IList<int>> ();

				IList<int> tmpRes = new List<int> ();
				Array.Sort (candidates);

				combinationOne (candidates, 0, target, tmpRes);

				return _res;
			}

			protected void combinationOne(int[] numset, int sIdx, int target, IList<int> tmpRes) {
				if (target == 0) {
					_res.Add (tmpRes);
				}

				if (sIdx >= numset.Length || numset[sIdx] > target) {
					return;
				}

				tmpRes.Add (numset [sIdx]);
				combinationOne (numset, sIdx + 1, target - numset [sIdx], tmpRes);
			}

			private IList<IList<int>> _res;
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();
				int[] t1 = { 2, 3, 6, 7 };
				int t1t = 7;

				s.CombinationSum (t1, t1t);
			}
		}
	}
}

