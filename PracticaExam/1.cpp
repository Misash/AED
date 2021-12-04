//
// Created by misash on 22/10/21.
//

#include <iostream>
using namespace std;




template<class T>
struct CLess
{   inline bool operator()(T a, T b)
    { return a < b; }
};


template<class T>
struct CGreater
{   inline bool operator()(T a, T b)
    { return a > b; }
};




template<class T>
struct CNode
{
    CNode(T _v) { v = _v; next = 0; }
    T v;
    CNode<T>* next;
};


template<class T, class C>
class CList
{
public:
    CList();
    ~CList();
    bool Find(T x, CNode<T>**& p);
    bool Insert(T x);
    bool Remove(T x);
    void Print();
private:
    CNode<T>* m_head;
    C m_cmp;
    CNode<T>** end;
};


template<class T, class C>
CList<T,C>::CList(){
    m_head = 0;
    end = &m_head;
}

template<class T, class C>
CList<T,C>::~CList()
{
    CNode<T> *a = m_head ,*b;
    while(a)
    {
        b = a->next;
        delete a;
        a = b;
    }
}

template<class T, class C>
bool CList<T,C>::Find(T x, CNode<T>**& p)
{
//    for ( p = &m_head;
//          *p && m_cmp( (*p)->v, x );
//          p = &((*p)->next) );
//    return *p && (*p)->v == x;

    for (p =&m_head; *p ; p = &((*p)->next) ){
        if((*p)->v == x) return 1;
    }
    return 0;
}

template<class T, class C>
bool CList<T,C>::Insert(T x)
{
//    CNode<T>** p;
//    if ( Find(x,p) ) return 0;
//    CNode<T>* n = new CNode<T>(x);
//    n->next = *p;
//    *p = n;
//    return 1;

    *end = new CNode<T>(x);
    end = &(*end)->next;

}

template<class T, class C>
bool CList<T,C>::Remove(T x)
{
    CNode<T>** p;
    if ( ! Find(x,p) ) return 0;
    CNode<T>* t = *p;
    *p = (*p)->next;
    delete t;
    return 1;
}

template<class T, class C>
void CList<T,C>::Print()
{
    cout<<endl;
    for ( CNode<T> *a = m_head; a; a = a->next )
        cout<<a->v<<" ";
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    CList<int, CLess<int> > l;
    l.Insert(3);
    l.Insert(1);
    l.Insert(0);
    l.Insert(0);
    l.Insert(0);
    l.Insert(0);



    l.Print();

    l.Remove(0);
    l.Remove(0);
    l.Remove(0);


    l.Print();



}







