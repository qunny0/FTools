using System;
using System.Collections;

// https://leetcode.com/problems/regular-expression-matching/

// parse
// http://blog.csdn.net/fzzying3/article/details/42057935
// http://meetqun.com/thread-2688-1-1.html

namespace leetcode010 {
	public class Solution {
		public bool IsMatch(string s, string p) {
			int sLen = s.Length;
			int pLen = p.Length;

			if (pLen == 0) {
				if (sLen == 0) {
					return true;
				}
				return false;
			}

			char[] pArr = p.ToCharArray ();
			char[] sArr = s.ToCharArray ();

			int sIdx = 0;
			if (pLen > 1 && pArr [1] == '*') {
				while (sIdx < sLen && (sArr [sIdx] == pArr [0] || pArr [0] == '.')) {
					if (IsMatch(s.Substring(sIdx), p.Substring(2))) {
						return true;
					}
					++sIdx;
				}
				return IsMatch (s.Substring(sIdx), p.Substring (2));
			}

			if (sIdx >= sLen) {
				return false;
			}

			return (sArr [sIdx] == pArr [0] || pArr [0] == '.') && IsMatch (s.Substring (1), p.Substring (1));
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//			Console.WriteLine (s.IsMatch("aa", "a"));
//		}
//	}

}