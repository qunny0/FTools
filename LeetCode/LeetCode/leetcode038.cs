using System;
using System.Collections;
using System.Collections.Generic;

/*
 * 5 - 111221 
 * 6 - 312211
 * 未理解题意
*/

namespace LeetCode
{
	public class leetcode038
	{
		public class Solution {
			public string CountAndSay(int n) {
				string str = "1";

				for (int i = 2; i <= n; ++i) {
					str = getNext (str);
				}

				return str;
			}

			protected string getNext(string str) {
				string res = "";

				int index = 0;
				char curChar = str [index];
				int count = 1;
				do {
					++index;
					if (index >= str.Length) {
						res += count;
						res += curChar;
						break;
					}

					if (str [index] == str [index - 1]) {
						++count;
					} else {
						res += count;
						res += curChar;
						count = 1;
						curChar = str[index];
					}
				} while(true);

				return res;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				string res = s.CountAndSay (6);
//
//				Console.WriteLine (res);
//			}
//		}
	}
}

