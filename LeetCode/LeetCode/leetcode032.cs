using System;
using System.Collections.Generic;


/**
 * Error 
 * 
*/

namespace LeetCode
{
	public class leetcode032
	{
		public class Solution {
			public int LongestValidParentheses(string s) {
				if (s.Length == 0) {
					return 0;
				}

				int max = 0;
				char[] sarr = s.ToCharArray ();
				for (int i = 0; i < sarr.Length; ++i) {
					int tmax = longestValidForm (s, i);
					max = tmax > max ? tmax : max;
				}

				return max;
			}

			protected int longestValidForm(string s, int beg) {
				char[] sarr = s.ToCharArray();
				int left = 0;
				int max = 0;
				for (int i = beg; i < sarr.Length; ++i) {
					if (sarr [i] == '(') {
						++left;
					} else {
						--left;
					}

					if (left < 0) {
						break;
					} else if (left == 0) {
						int tm = i - beg + 1;
						max = tm > max ? tm : max;
					} 
				}

				return max;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();
//				string test = ")()())";
				string test = ")(((())))(";

				int res = s.LongestValidParentheses (test);
				Console.WriteLine ("" + res);
			}
		}
	}
}

