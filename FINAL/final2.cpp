//
// Created by misash on 11/12/21.
//

#include <iostream>
#include <vector>

using namespace  std;

template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = 0;
    }
    T value;
    CNode<T> *next, *prev;
};

template<class T>
class CList
{
public:
    CList();
    void push_back(T x);
    CNode<T>* Find_O_N(T x);
    CNode<T>* Find_O_1(T x);

private:
    CNode<T>* head, *tail;
    int nelem;
    vector<CNode<T>*> nodes;
};


template<class T>
CList<T>::CList()
{
    head = tail = 0;
    nelem = 0;
    nodes.resize(26);
}

template<class T>
void CList<T>::push_back(T x)
{
    CNode<T>* n = new CNode<T>(x);
    if (!nelem)
        head = tail = n;
    else
    {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    nodes[abs(97 -x)] = n; //ingreso
    nelem ++;
}

template<class T>
CNode<T>* CList<T>::Find_O_N(T x)
{
    for (CNode<T>* n = head; n != 0; n = n->next )
        if ( n->value == x )
            return n;
    return 0;
}


template<class T>
CNode<T>* CList<T>::Find_O_1(T x)
{
    if(nodes[abs(97 -x)]->value == x)
        return nodes[abs(97 - x)];
    return 0;
}

void Test_Find_O_N(CList<char>& l)
{
    std::cout<<"\n";
    for ( int i = 0; i < 26; i++ )
    {
        if ( l.Find_O_N((char)(i+97)) )
            std::cout<<(char)(i+97)<<" ";
        else
            std::cout<<"- ";
    }
    std::cout<<"\n";
}

void Test_Find_O_1(CList<char>& l)
{
    std::cout<<"\n";
    for ( int i = 0; i < 26; i++ )
    {
        if ( l.Find_O_1((char)(i+97)) )
            std::cout<<(char)(i+97)<<" ";
        else
            std::cout<<"- ";
    }
    std::cout<<"\n\n";
}

int main()
{
    CList<char> l;

    l.push_back('g');   l.push_back('w');   l.push_back('b');   l.push_back('k');
    l.push_back('n');   l.push_back('p');   l.push_back('a');   l.push_back('r');
    l.push_back('e');   l.push_back('s');   l.push_back('d');   l.push_back('f');
    l.push_back('y');   l.push_back('v');   l.push_back('u');   l.push_back('o');
    l.push_back('q');   l.push_back('h');   l.push_back('i');   l.push_back('c');
    l.push_back('m');   l.push_back('t');   l.push_back('z');   l.push_back('j');
    l.push_back('x');   l.push_back('l');

    Test_Find_O_N(l);
    Test_Find_O_1(l);

}