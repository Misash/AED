//
// Created by misash on 3/10/21.
//


/*

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,

Given 1->4->3->2->5->2 and x = 3,

return 1->2->2->4->3->5.

 */


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* Solution::partition(ListNode* A, int x) {

    ListNode *B = 0;
    ListNode *p = 0;
    ListNode *C = 0;
    ListNode *r = 0;

    for(ListNode *q = A; q ; q=q->next){
        if(q->val < x){
            if(!B){
                B = q;
                p = q;
            }else{
                p->next = q;
                p = p->next;
            }
        }else{
            if(!C){
                C = q;
                r = q;
            }else{
                r->next = q;
                r = r->next;
            }
        }
    }

    if(B && C){
        p->next = C;
        r->next = 0;
        return B;
    }
    else if(C){
        r->next = 0;
        return C;
    }
    else if(B){
        return B;
    }

    return 0;

}
