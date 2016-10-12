// https://leetcode.com/problems/longest-palindromic-substring/

// http://articles.leetcode.com/longest-palindromic-substring-part-i/#comment-6650

#include <iostream>
#include <string>

using namespace std;
// 01 -- error. dp的遍历顺序有问题。
// 02 -- error. "bb" --> 字符串长度应该提前处理，+1
// 03 -- Memory Limit Exceeded. "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

// manacher`s algorithm 是解决回文字符串最高效的算法。// 其没有通用代表性，
// 没有理解这个算法的意思，以及证明这个算法的正确性。

// 使用DP解决该问题，时间复杂度On2，空间复杂度为On2。
class SolutionDP {
public:
    string longestPalindrome(string s) {
    	int size = s.length();

    	bool** dp = new bool*[size];
    	for (int i = 0; i < size; ++i)
    	{
    		dp[i] = new bool[size];
    		memset(dp[i], 0, size*sizeof(bool));
    	}


    	int bIndex = 0, subMax = 1;
    	for (int i = 0; i < size; ++i)
    	{
    		for (int j = 0; j < size-i; ++j)
    		{
    			int ej = j+i;
    			bool bRet = false;
    			if (i == 0)
    			{
    				bRet = true;
    			}
    			else if (i == 1)
    			{
					bRet = (s[j] == s[ej]);
    			}
    			else
    			{
					bRet = (dp[j+1][ej-1] && s[j] == s[ej]);
    			}

    			dp[j][ej] = bRet;
    			int len = i + 1;
    			if (bRet && len > subMax)
    			{
    				bIndex = j;
    				subMax = len;
    			}
    		}
    	}

    	for (int i = 0; i < size; ++i)
    	{
    		delete []dp[i];
    	}
    	delete []dp;

	    return s.substr(bIndex, subMax);
    }
};

// 正常解决问题方法，遍历各个回文串的中心，获取最大的palindromic
class SolutionN {
public:
	string centerAround(string s, int c1, int c2)
	{
		int len = s.length();
        // cout << "init: " << c1 << ", " << c2 << " [";
		while(c1 >= 0 && c2 <= len-1 && s[c1] == s[c2])
		{
			--c1;
			++c2;
		}
        // cout << c1 << "," << c2 << "--->" << c1+1 << "," << c2-1 << "]" << endl << endl;
        return s.substr(c1+1, c2-c1-1);
	}

	string longestPalindrome(string s) 
	{
		int len = s.length();

        string palindrome = "";
        for (int i = 0; i < len; ++i)
        {
            string res = centerAround(s, i, i);
            if (res.length() > palindrome.length())
            {
                palindrome = res;
            }

            if (i > 0)
            {
                res = centerAround(s, i-1, i);                
                if (res.length() > palindrome.length())
                {
                    palindrome = res;
                }
            }
        }

        return palindrome;
	}
};

// Manacher’s Algorithm
class Solution
{
public:
    string preProcess(string s) {
        int n = s.length();
        if (n == 0) 
            return "^$";
        string ret = "^";
        for (int i = 0; i < n; i++)
            ret += "#" + s.substr(i, 1);
 
        ret += "#$";
        return ret;
    }
 
    string longestPalindrome(string s) {
        string T = preProcess(s);
        int n = T.length();
        int *P = new int[n];
        int C = 0, R = 0;
        for (int i = 1; i < n-1; i++) {
            int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
            P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
            // Attempt to expand palindrome centered at i
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
 
                // If palindrome centered at i expand past R,
                // adjust center based on expanded palindrome.
                if (i + P[i] > R) {
                    C = i;
                    R = i + P[i];
                }
            }
 
        }  

        // Find the maximum element in P.
        int maxLen = 0;
        int centerIndex = 0;
        for (int i = 1; i < n-1; i++) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        delete[] P;

        return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
    }
};

int main()
{
    Solution s;

    string res = s.longestPalindrome("cabcbabcbabcba");
    cout << res << endl;
    return 0;
}