// https://leetcode.com/problems/two-sum/

// 分别使用循环 时间复杂度O(N2)，空间复杂度为O(1)
// 使用map或是hash，时间复杂度为O(N)，空间复杂度为O(N)

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Solutions {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> vRes;
        for (int i = 0; i < nums.size()-1; ++i)
        {
            for(int j = i + 1; j < nums.size(); ++j)
            {
                if(nums[i]+nums[j] == target)
                {
                    vRes.push_back(i);
                    vRes.push_back(j);
                    return vRes;
                }
            }
        }

        return vRes;
    }
};



// hash
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> vRes;
        // map<int, int> numHash;
        unordered_map<int, int> numHash;
        for (int i = 0; i < nums.size(); ++i)
        {
            numHash[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (numHash.find(target-nums[i]) != numHash.end() && numHash[target-nums[i]] != i)
            {
                cout << i << ", " << numHash[target-nums[i]] << endl;
                vRes.push_back(i);
                vRes.push_back(numHash[target-nums[i]]);
                break;
            }
        }
        return vRes;
    }
};


int main()
{
    Solution s;
    int test[] = {3, 2, 4};
    vector<int> vNum(test, test+3);
    vector<int> vRes = s.twoSum(vNum, 6);

    if (vRes.size() > 0)
    {
        cout << "[" << vRes[0] << ", " << vRes[1] << "]." << endl;
    }

    return 0;
}