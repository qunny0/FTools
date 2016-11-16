using System;
using System.Collections.Generic;


/**
 * Error 
*/

namespace LeetCode
{
	public class leetcode030
	{
		public class Solution {
			public IList<int> FindSubstring(string s, string[] words) {
				IList<int> res = new List<int>();
				if (words.Length == 0) {
					return res;
				}

				IDictionary<string, int> dicWord = new Dictionary<string, int> ();
				foreach (string word in words) {
					dicWord.Add (word, 1);
				}

				int wordLen = words [0].Length;
				int wordSize = words.Length;
				int wordsLen = wordLen * wordSize;

				for (int i = 0; i < s.Length - wordsLen + 1; ++i) {
					foreach (KeyValuePair<string, int> it in dicWord) {
						it.Value = 1;
					}

					var substr = s.Substring (i, wordsLen);
					for(int j = 0; j < wordsLen; ++j){
						string subsubstr = substr.Substring (j * wordLen, wordLen);
						if (dicWord.ContainsKey (subsubstr)) {
							if (dicWord [subsubstr] == 1) {
								dicWord [subsubstr] = 0;
							} else {
								break;
							}
						}
					}

					bool match = true;
					foreach (var ele in dicWord.Values) {
						if (ele == 1) {
							match = false;
						}
					}
					if (match) {
						res.Add (i);
					}
				}

				return res;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				string s1 = "barfoothefoobarman";
				string [] s1_1 = {
					"foo",
					"bar"
				};

				IList<int> res1 = s.FindSubstring (s1, s1_1);
				foreach(var re in res1){
					Console.Write (re + ",");
				}
				Console.WriteLine ("");
			}
		}
	}
}

