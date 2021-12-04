//
// Created by misash on 28/09/21.
//


#include <iostream>

using namespace std;

template <class T>
struct CForwardNode{

    T value;
    CForwardNode<T>* next;
    CForwardNode(T x)
    { value = x; next = nullptr; }
};

template <class T>
class CForwardList{
public:
    CForwardList();
    ~CForwardList();
    bool Find(T x,CForwardNode<T>** &p);
    bool Ins(T x);
    bool Rem(T x);
    void Print();

private:
    CForwardNode<T> *head;

};

template <class T>
CForwardList<T>::CForwardList(){
    head = nullptr;
}

template <class T>
CForwardList<T>::~CForwardList(){
    CForwardNode<T>* t = head;
    while(t){
        auto p = t;
        t=t->next;
        delete p;
    }
}

template <class T>
bool CForwardList<T>::Find(T x, CForwardNode<T> **&p){

//    for ( p = &head;   (*p)->value < x && *p   ; p = &(*p)->next );
    for ( p = &head;   *p &&  (*p)->value < x   ; p = &(*p)->next );
    return *p  && (*p)->value == x;
}

template <class T>
bool CForwardList<T>::Ins(T x) {

    CForwardNode<T>** p;
    if ( Find(x,p) ) return 0;
    CForwardNode<T>* t = new CForwardNode<T>(x);
    t->next = *p;
    *p = t;
    return 1;
}

template <class T>
bool CForwardList<T>::Rem(T x) {
    CForwardNode<T>** p;
    if ( !Find(x,p) ) return 0;
    CForwardNode<T>* t = *p;
    *p = t->next;
    delete t;
    return 1;
}


template <class T>
void CForwardList<T>::Print(){
    cout<<endl;
    for(CForwardNode<T> *t = head; t; t = t->next)
        cout<<" -> "<<t->value;
}



int main(){

    CForwardList<int> l;

    l.Ins(15);
    l.Ins(9);

    l.Print();


}









