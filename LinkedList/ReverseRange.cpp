//
// Created by misash on 5/10/21.
//

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct CNode
{
    CNode(int x)
    {
        val = x;
        next = prev = nullptr;
    }
    int val;
    CNode *next, *prev;
};


class CList
{
public:
    CList()
    {
        head = tail = nullptr;
        nelem = 0;
    }
    ~CList()
    {
        //...
    }

    void push_back(int x)
    {
        CNode* n = new CNode(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        nelem++;
    }

    void pop_back()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode* aux = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    void push_front(int x)
    {
        CNode* n = new CNode(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem++;
    }

    void pop_front()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode* aux = head;
            head = head->next;
            head->prev = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    int& operator[](int i)
    {
        CNode* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->val;
    }

    void print()
    {
        cout<<"\n";
        for (CNode* i = head; i ; i=i->next) {
            cout<<i->val<<" ";
        }
    }

    void print2()
    {
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    }

    int size(){
        return nelem;
    }

    CNode* head, *tail;
    int nelem;
};



CNode* reverseBetween(CNode* head, int m, int n) {

    if(!head) return 0;

    int k = n-m+1;

    CNode *fakeHead = new CNode(0);
    fakeHead->next = head;
    CNode *q = fakeHead;
    CNode *p = q->next;


    while(--m) q=q->next;
    while(n--) p=p->next;

    CNode *prev = p;
    CNode *r = q->next;

    while(k--){
        CNode *t = r->next;
        r->next = prev;
        prev = r;
        r = t;
    }

    q->next = prev;

    return fakeHead->next;
}


int main()
{
    CList A,B,C;

    A.push_back(1);
    A.push_back(2);
//    A.push_back(3);
//    A.push_back(4);
//    A.push_back(5);

    A.print();

    B.head = reverseBetween(A.head,1,2);


    B.print();

}



