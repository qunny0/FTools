using System;
using System.Collections.Generic;

namespace LeetCode
{
	public class leetcode028
	{
		public class Solution {
			public int StrStr(string haystack, string needle) {
				int nHayLen = haystack.Length;
				int mNeedleLen = needle.Length;

//				if (nHayLen == 0 || mNeedleLen == 0) {
//					return -1;
//				}

				var hayArray = haystack.ToCharArray ();
				var needleArray = needle.ToCharArray ();

				for (int i = 0; i < nHayLen - mNeedleLen + 1; ++i) {
					bool match = true;
					for (int j = 0; j < mNeedleLen; ++j) {
						if (hayArray [i + j] != needleArray [j]) {
							match = false;
							break;
						}
					}
					if (match) {
						return i;
					}
				}

				return -1;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
//				int idx = s.StrStr ("1223", "");
//				Console.WriteLine ("" + idx);
//			}
//		}
	}
}

