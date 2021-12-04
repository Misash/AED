//
// Created by misash on 5/10/21.
//



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


ListNode* Solution::detectCycle(ListNode* head) {


    ListNode * p = head;
    ListNode *q = head;
    bool isCycle = 0;

    while(p && q && q->next){
        p = p->next;
        q = q->next->next;

        if(p == q){
            isCycle = 1;
            break;
        }
    }

    if(isCycle){
        //position of cycle

        q = head;

        while(p != q){
            p=p->next;
            q=q->next;
        }
        return p;
    }

    return NULL;
}


