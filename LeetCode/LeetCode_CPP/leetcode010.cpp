// https://leetcode.com/problems/regular-expression-matching/

// http://www.cnblogs.com/grandyang/p/4461713.html

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Solution {
public:
    /*
        (1)p[j+1]不是'*'。情况比较简单，只要判断当前s的i和p的j上的字符是否一样（如果有p在j上的字符是'.',也是相同），如果不同，返回false，否则，递归下一层i+1，j+1; 
        (2)p[j+1]是'*'。那么此时看从s[i]开始的子串，假设s[i],s[i+1],...s[i+k]都等于p[j]那么意味着这些都有可能是合适的匹配，那么递归对于剩下的(i,j+2),(i+1,j+2),...,(i+k,j+2)都要尝试（j+2是因为跳过当前和下一个'*'字符）。 
    */
    bool isMatch(string s, string p) {
        int slen = s.length(), plen = p.length();
        if (plen == 0 && slen == 0)
        {
            return true;
        }
        
        if (plen == 1)
        {
            if (slen == 1 && (s[0] == p[0] || p[0] == '.'))
            {
                return true;
            }
            return false;
        }

        if (p[1] != '*')
        {
            if (slen == 0)
            {
                return false;
            }
            return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }

        while(slen > 0 && (s[0] == p[0] || p[0] == '.'))
        {
            if (isMatch(s, p.substr(2)))
            {
                return true;
            }
            s = s.substr(1);
        }

        return isMatch(s, p.substr(2));
    }
};

int main()
{
    Solution s;

    cout << s.isMatch("ab", ".*c") << endl;

    return 0;
}
