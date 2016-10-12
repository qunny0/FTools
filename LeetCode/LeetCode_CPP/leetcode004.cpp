// https://leetcode.com/problems/median-of-two-sorted-arrays/


// Runtime Error
// Last executed input:
// []
// [1]

// 其中一个数组为空的情况

// 这道题目要求的时间复杂度为O(log(m+n))

// 1. 第一次提交算法的复杂度为O((m+n)/2)

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    	int l1 = nums1.size(), l2 = nums2.size();
        int k = (l1+l2-1)/2;
    	bool isOdd = (((l1+l2) & 0x1) == 1);

        if (l1 == 0)
        {
            return isOdd ? nums2[k] : double(nums2[k]+nums2[k+1])/2;
        }
        if (l2 == 0)
        {
            return isOdd ? nums1[k] : double(nums1[k]+nums1[k+1])/2;
        }

        int bi = 0, bj = 0;
    	int jumpCount = (l1+l2-1)/2;
    	for (int i = 0; i < jumpCount; ++i)
    	{
            next(nums1, bi, nums2, bj);
    	}

		if (isOdd)
		{
			return next(nums1, bi, nums2, bj);
		}

		int tmpSum = next(nums1, bi, nums2, bj);
        tmpSum += next(nums1, bi, nums2, bj);

		return double(tmpSum/2.0f);
    }

    int next(vector<int>& nums1, int& i1, vector<int>& nums2, int& i2) {
        int l1 = nums1.size(), l2 = nums2.size();
        int num = 0;

        if (i1 >= l1)
        {
            num = nums2[i2]; 
            ++i2;
        }
        else if (i2 >= l2)
        {
            num = nums1[i1];
            ++i1;
        }
        else
        {
            num = nums1[i1] < nums2[i2] ? nums1[i1] : nums2[i2];
            if (nums1[i1] < nums2[i2])
            {
                ++i1;
            }
            else
            {
                ++i2;
            }
        }

        return num;
    }

    double findMedianSortedArraysV(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size(), l2 = nums2.size();
        int k = (l1+l2)/2;
        bool isOdd = (((l1+l2) & 0x1) == 1);

        // cout << isOdd << endl;

        if (isOdd)
        {
            return findKthV(nums1, 0, nums2, 0, k+1);
        }

        int tmpSum = findKthV(nums1, 0, nums2, 0, k);
        tmpSum += findKthV(nums1, 0, nums2, 0, k+1);

        cout << tmpSum << endl;
        return tmpSum/2.0;
    }

    // nums1.size() > nums2.size()
    double findKthV(vector<int>& nums1, const int b1, vector<int>& nums2, const int b2, int k)
    {
        int l1 = nums1.size(), l2 = nums2.size();
        int res = 0;
        cout << b1 << ", " << b2 << ", " << k << endl;
        if (l1 < l2)
        {
            res = findKthV(nums2, b2, nums1, b1, k);
        }
        else if (l2 == 0)
        {
            res = nums1[k-1];
        }
        else if (k == 1)
        {
            res = min(nums1[b1], nums2[b2]);
        }
        else 
        {
            int pa = min(k/2, l1-b1), pb = k-pa;
            if (nums1[pa-1] > nums2[pb-1])
            {
                res = findKthV(nums1, b1, nums2, b2+k-pa, k-pb);
            }
            else if (nums1[pa-1] < nums2[pb-1])
            {
                res = findKthV(nums1, b1+k-pb, nums2, b2, k-pa);
            }
            else
            {
                res = nums1[pa-1];
            }
        }
        cout << k << " " << res << endl;
        return res;
    }

    double findKth(int a[], int m, int b[], int n, int k)
    {
        //always assume that m is equal or smaller than n
        if (m > n)
            return findKth(b, n, a, m, k);
        if (m == 0)
            return b[k-1];
        if (k == 1)
            return min(a[0], b[0]);

        //divide k into two parts
        int pa = min(k/2, m), pb = k-pa;
        if (a[pa-1] < b[pb-1])
            return findKth(a+pa, m-pa, b, n, k-pa);
        else if (a[pa-1] > b[pb-1])
            return findKth(a, m, b+pb, n-pb, k-pb);
        else
            return a[pa-1];
    }
};

int main()
{
    Solution s;

    int va[] = {100001};
    vector<int> v1(va, va+1);
    int vb[] = {100000};
    vector<int> v2(vb, vb+1);

    double res = s.findMedianSortedArrays(v1, v2);
    cout << res << endl;
    return 0;
}
