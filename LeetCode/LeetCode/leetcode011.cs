using System;
using System.Collections;

//https://leetcode.com/problems/container-with-most-water/

//01, 02, 03 	Wrong Answer	提议没有分析清除
//04 [1-15000]	Time Limit Exceeded

namespace leetcode011 {
	public class Solution {

//		Time Limit Exceeded
//		public int MaxArea(int[] height) {
//			int area = 0, tmpArea = 0;
//			for (int i = 0; i < height.Length; ++i) {
//				for (int j = 0; j < height.Length; ++j) {
//					tmpArea = (j - i) * Math.Min (height [i], height [j]);
//					area = tmpArea > area ? tmpArea : area;
//				}
//			}
//
//			return area;
//		}

//		Accepted 
//		public int MaxArea(int[] height) {
//			int area = 0, tmpArea = 0;
//			for (int i = 0; i < height.Length; ++i) {
//				if (height [i] == 0) {
//					continue;
//				}
//				for (int j = Math.Max(i+1, area/height[i]+i); j < height.Length; ++j) {
//					tmpArea = (j - i) * Math.Min (height [i], height [j]);
//					area = tmpArea > area ? tmpArea : area;
//				}
//			}
//
//			return area;
//		}

	
//		Accepted 
		public int MaxArea(int[] height) {
			int maxArea = 0, area = 0;
			int i = 0, j = height.Length - 1;
			if (j <= i) {
				return 0;
			}

			while (i < j) {
				area = (j - i) * (Math.Min (height [i], height [j]));
				if (height [i] < height [j]) {
					i++;
				} else {
					j--;
				}
				maxArea = area > maxArea ? area : maxArea;
			}

			return maxArea;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//
//			int[] hArr = new int[15000];
//			for (int i = 0; i < 15000; ++i) {
//				hArr [i] = i + 1;
//			}
//
//			Console.WriteLine (s.MaxArea(hArr));
//		}
//	}

}