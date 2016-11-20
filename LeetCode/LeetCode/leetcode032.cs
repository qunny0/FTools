using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 : 【1， 3， 2】
 * # 1 : 【1， 3， 2】
 * # 3 : 【2， 3， 1】
 * # 4 : [5,4,7,5,3,2]
 * 
 * 
*/

namespace LeetCode
{
	public class leetcode031
	{
		public class Solution {
			public int LongestValidParentheses(string s) {

			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

//				int[] t1 = { 1, 2, 1 };
				int[] t1 = { 5, 4, 7, 5, 3, 2 };
//				int[] t1 = { 3, 2, 1 };

				s.NextPermutation (t1);

				Array.ForEach<int> (t1, (k) => Console.Write (k + ","));
				Console.WriteLine ();
			}
		}
	}
}

