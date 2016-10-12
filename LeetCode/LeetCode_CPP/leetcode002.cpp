// https://leetcode.com/problems/add-two-numbers/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// submit failed 01
// [5]
// [5]

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* pRes = NULL;

        ListNode* p = pRes;
        ListNode* p1 = l1;
        ListNode* p2 = l2;

        int carry = 0;
        int sum = 0;
        while(p1 or p2)
        {   
            sum = 0;

            sum += carry;
            carry = 0;

            if (p1)
            {
                sum += p1->val;
                p1 = p1->next;
            }
            if (p2)
            {
                sum += p2->val;
                p2 = p2->next;
            }

            carry = sum / 10;
            sum = sum % 10;

            ListNode* pNew = new ListNode(sum);
            if (!pRes)
            {
                pRes = pNew;
            }
            else
            {
                p->next = pNew;
            }
            p = pNew;
        }

        if (carry != 0)
        {
            ListNode* pNew = new ListNode(carry);
            if (!pRes)
            {
                pRes = pNew;
            }
            else
            {
                p->next = pNew;
            }
        }

        return pRes;
    }
};

ListNode* createList(int a[], int num)
{
    ListNode* root = NULL;
    ListNode* p = NULL;
    for (int i = 0; i < num; ++i)
    {
        ListNode* pNew = new ListNode(a[i]);
        if (!root)
        {
            root = pNew;
        }
        else
        {
            p->next = pNew;
        }
        p = pNew;
    }

    return root;
}

void printList(ListNode* root)
{
    if (!root)
        return ;

    ListNode* p = root;
    while(p)
    {
        cout << p->val << ", ";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    int l1[] = {5, 4, 3};
    int l2[] = {5, 6, 4};

    ListNode* p1 = createList(l1, 1);
    ListNode* p2 = createList(l2, 1);

    printList(p1);
    printList(p2);

    Solution s;
    ListNode* pSum = s.addTwoNumbers(p1, p2);
    printList(pSum);

    return 0;
}
