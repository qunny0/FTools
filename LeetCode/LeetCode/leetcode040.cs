using System;
using System.Collections;
using System.Collections.Generic;

/*
 * 5 - 111221 
 * 6 - 312211
*/

namespace LeetCode
{
	public class leetcode040
	{
		public class Solution {
			public IList<IList<int>> CombinationSum(int[] candidates, int target) {
				_res = new List<IList<int>> ();

				IList<int> tmpRes = new List<int> ();
				Array.Sort (candidates);

				helper (candidates, 0, target, tmpRes, 0);

				foreach (IList<int> l in _res) {
					foreach (int n in l) {
						Console.Write ("" + n + ", ");
					}
					Console.WriteLine ("");
				}

				return _res;
			}


			protected void helper(int[] nset, int sIdx, int target, IList<int> tmpRes, int level){
				if (sIdx >= nset.Length) {
					return;
				}

				for (int i = sIdx; i < nset.Length; ++i) {
					if (i > sIdx && nset [i] == nset [i - 1]) {
						continue;
					}
					int remain = target - nset [i];
					if (remain == 0) {
						tmpRes.Add (nset [i]);
						_res.Add (new List<int> (tmpRes));
						tmpRes.RemoveAt (tmpRes.Count - 1);
					} else if (remain > 0) {
						tmpRes.Add (nset[i]);
						helper (nset, i + 1, remain, tmpRes, level+1);
						tmpRes.RemoveAt (tmpRes.Count - 1);
					} else {
						break;
					}
				}
			}

			private IList<IList<int>> _res;
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				int[] t1 = {1, 1, 2, 5, 6, 7, 10};
//				int t1t = 8;
//
//				s.CombinationSum (t1, t1t);
//			}
//		}
	}
}

