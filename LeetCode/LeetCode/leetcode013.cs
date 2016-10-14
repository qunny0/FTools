using System;
using System.Collections.Generic;

// https://leetcode.com/problems/roman-to-integer/

// I（1）、V（5）、X（10）、L（50）、C（100）、D（500）、M（1000）

namespace LeetCode013
{
	public class Solution {
		public int RomanToInt(string s) {
			char[] romans = {'I',  'V', 'X', 'L', 'C', 'D', 'M'};
			int[] nums = { 1, 5, 10, 50, 100, 500, 1000 };

			Dictionary<char, int> roman2num = new Dictionary<char, int> ();
			for (int i = 0; i < romans.Length; ++i) {
				roman2num.Add (romans [i], nums [i]);
			}

			int res = 0;
			for (int i = 0; i < s.Length-1; ++i) {
				int cur = roman2num[s [i]];
				int next = roman2num[s[i+1]];

				if (next > cur) {
					res -= cur;					
				} else {
					res += cur;
				}
			}

			res += roman2num[s[s.Length-1]];
			return res;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Dictionary<int, string> dictTests = new Dictionary<int, string>();
//			dictTests.Add (14, "XIV");
//			dictTests.Add (1, "I");
//			dictTests.Add (4, "IV");
//			dictTests.Add (8, "VIII");
//			dictTests.Add (16, "XVI");
//			dictTests.Add (45, "XLV");
//			dictTests.Add (99, "XCIX");
//			dictTests.Add (1666, "MDCLXVI");
//			dictTests.Add (3999, "MMMCMXCIX");
//
//			Solution s = new Solution ();
//
//			foreach (KeyValuePair<int, string> kvp in dictTests) {
//				int res = s.RomanToInt (kvp.Value);
//				if (res != kvp.Key) {
//					throw new Exception ("error " + kvp + " --> " + res);
//				}
//			}
//
//			Console.WriteLine (s.RomanToInt("MMMCMXCIX"));
//		}
//	}
}

