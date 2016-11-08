using System;
using System.Collections;
using System.Collections.Generic;


// 1 Wrong Answer Input: "" ; Output: [""] ; Expected: []


namespace leetcode017 {
	public class Solution {
		public Solution() {
			_resList = new List<string> ();
			_resList.Clear ();
		}

		public IList<string> LetterCombinations(string digits) {
			dfs (digits, "");

			return _resList;
		}

		protected void dfs(string digits, string pre) {
			if (digits.Length == 0) {
				if (pre.Length > 0) {
					Console.WriteLine (pre);
					_resList.Add (pre);
				}
				return;
			}

			var digitStr = num2str [digits [0] - '0'].ToCharArray();
			for (int i = 0; i < digitStr.Length; ++i) {
				dfs (digits.Substring(1), pre + digitStr [i]);
			}
		}

		private IList<string> _resList;
		static private string[] num2str = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//			s.LetterCombinations ("");
//		}
//	}

}	