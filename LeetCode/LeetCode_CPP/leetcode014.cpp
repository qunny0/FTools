// https://leetcode.com/problems/palindrome-number/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0)
        {
            return "";
        }

        string str = "";
        for (int i = 0; i < strs[0].length(); ++i)
        {
            for (int j = 1; j < strs.size(); ++j)
            {
                if (strs[0][i] != strs[j][i])
                {
                    return str;
                }
            }
            str += strs[0][i];
        }

        return str;
    }
};

int main()
{
    Solution s;

    cout << s.longestCommonPrefix("[]") << endl;
    return 0;
}

