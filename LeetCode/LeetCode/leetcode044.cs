using System;
using System.Collections;
using System.Collections.Generic;

// #1 WA : "", "*"
// #2 WA : "ho", "ho**"
// #3 WA : "aa", "a"
// #4 TLE: "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba" "a*******b"
// #5 TLE: "babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb" "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a"

namespace LeetCode
{
	public class leetcode044
	{
		public class Solution {
    		public bool IsMatch(string s, string p) {
				int sl = s.Length;
				int pl = p.Length;

				

				return false;
    		}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				var res = s.IsMatch ("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b");
				Console.WriteLine (res);
			}
		}
	}
}
