using System;
using System.Collections;

// https://leetcode.com/problems/valid-parentheses/

// 01 Runtime Error  	"]"
// 02 Wrong Answer		"([]"
// 03 AC

namespace leetcode020 {

	public class Solution {
		public bool IsValid(string s) {
			Stack stack = new Stack();

			char[] sArray = s.ToCharArray ();
			int len = s.Length;
			for (int i = 0; i < len; ++i) {
				char c = sArray [i];
				Console.WriteLine ("16 - " + c);
				if (c == '(' || c == '[' || c == '{') {
					stack.Push (c);
				} else {
					if (stack.Count > 0) {
						char peekC = (char)stack.Pop ();
						if (!isMatch (peekC, c)) {
							return false;
						}
					} else {
						return false;
					}
				}
			}

			return stack.Count == 0;
		}

		private bool isMatch(char lc, char rc)
		{
			if (rc == ')' && lc == '(' ||
			    rc == ']' && lc == '[' ||
			    rc == '}' && lc == '{') {
				return true;
			}
			return false;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution();
//			bool ret = s.IsValid ("([]");
//			Console.WriteLine (ret);
//		}
//	}

}