using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 : "wordgoodgoodgoodbestword" ["word","good","best","good"]
 * # 2 : "barfoofoobarthefoobarman" ["bar","foo","the"] Output: [6] Expected: [6,9,12]
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

				IDictionary<string, short> dicWord = new Dictionary<string, short> ();

				int wordLen = words [0].Length;
				int wordSize = words.Length;
				int wordsLen = wordLen * wordSize;

				for (int i = 0; i < s.Length - wordsLen + 1; ++i) {
					dicWord.Clear ();
					foreach (string word in words) {
						if (dicWord.ContainsKey (word)) {
							dicWord [word] += 1;
						} else {
							dicWord.Add (word, 1);
						}
					}

					var substr = s.Substring (i, wordsLen);
					for(int j = 0; j < wordSize; ++j){
						string subsubstr = substr.Substring (j * wordLen, wordLen);
						if (dicWord.ContainsKey (subsubstr)) {
							if (dicWord [subsubstr] > 0) {
								dicWord [subsubstr] -= 1;
							} else {
								break;
							}
						} else {
							break;
						}
					}

					bool match = true;
					foreach (var ele in dicWord.Values) {
						if (ele > 0) {
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

				string s1 = "barfoofoobarthefoobarman";
				string [] s1_1 = {
					"bar","foo","the"
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

