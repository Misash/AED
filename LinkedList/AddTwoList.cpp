//
// Created by misash on 4/10/21.
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



CNode* addTwoNumbers(CNode* A, CNode* B) {

    long long  a=0,b=0,i=0;
    for(CNode *p = A ; p ; p=p->next){
        a += (p->val * pow(10,i++));
    }

    i = 0;
    for(CNode *p = B ; p ; p=p->next){
        b += (p->val * pow(10,i++));
    }

    auto c = std::to_string(a+b);
    long long  k = c.size();

    CNode *C = new CNode(0);
    CNode *p = C;

    while(k--){

        p->next = new CNode(c[k] - '0');
        p = p->next;
    }

    return C->next;
}







int main()
{
    CList A,B,C;
//    l.push_back(1);
    A.push_back(9);
    A.push_back(9);
    A.push_back(1);

    B.push_back(1);
//    B.push_back(6);
//    B.push_back(4);


    C.head = addTwoNumbers(A.head,B.head);


    A.print();
    B.print();
    C.print();


}



