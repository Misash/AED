//
// Created by misash on 4/10/21.
//

//Palindrome

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
int Solution::lPalin(ListNode* head) {

    ListNode * fast = head;
    ListNode * mid = head;

    //find middle
    while(fast && fast->next){
        fast = fast->next->next;
        mid = mid->next;
    }

    //reverse
    ListNode * prev = 0;

    while(mid){
        ListNode * t = mid->next;
        mid->next = prev;
        prev = mid;
        mid = t;
    }

    //check Palindrome
    ListNode * left = head;
    ListNode * right = prev;

    while(right){
        if(left->val != right->val){
            return 0;
        }
        left = left->next;
        right = right->next;
    }

    return 1;


}
