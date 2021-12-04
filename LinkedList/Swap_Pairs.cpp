//
// Created by misash on 3/10/21.
//


/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,

Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

 */



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
ListNode* Solution::swapPairs(ListNode* A) {


    for(ListNode **p=&A  ; *p && (*p)->next ; p=&(*p)->next->next ){
        ListNode **q = &(*p)->next;
        ListNode * t = *p;
        *p = *q;
        *q = (*q)->next;
        (*p)->next = t;
    }

    return A;

}
