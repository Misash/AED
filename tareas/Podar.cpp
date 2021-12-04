//
// Created by misash on 29/10/21.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;


template <class T>
struct CBinTreeNode
{
    CBinTreeNode(T v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    T value;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};


template <class T>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p);
    void InOrder(CBinTreeNode<T>* n);
    void PreOrder(CBinTreeNode<T>* n);
    void PosOrder(CBinTreeNode<T>* n);
    void ReverseOrder(CBinTreeNode<T>* n);
    void LevelOrder(CBinTreeNode<T>* n);
    int MaxDepth(CBinTreeNode<T>* n);
    void Print();
    int Size();
    void deleteTree(CBinTreeNode<T> **);


    void InOrderTrack(CBinTreeNode<T>*  , vector<vector<string>> & , int , int &);
    void PrintNiveles();
    void Podarlevel(CBinTreeNode<T> **n, int , int );
    int PodarTree(CBinTreeNode<T> *);
    void Podar();


private:
    CBinTreeNode<T>* root;
    bool brep;
    int size;
};

template <class T>
CBinTree<T>::CBinTree()
{
    root = 0;
    brep = 0;
    size = 0;
}

template <class T>
CBinTree<T>::~CBinTree()
{
    deleteTree(&root);
}

template <class T>
void CBinTree<T>::deleteTree(CBinTreeNode<T> ** p)
{

    if( !(*p)  ) return ;
    int val = (*p)->value;

    deleteTree(&(*p)->nodes[0]);
    deleteTree(&(*p)->nodes[1]);
    CBinTreeNode<T> *temp = *p;
    *p = nullptr;
    delete temp;

}


template <class T>
CBinTreeNode<T>* CBinTree<T>::Root()
{
    return root;
}

template <class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p)
{
    for (   p = &root;
            *p && (*p)->value != x;
            p = &((*p)->nodes[ (*p)->value < x ])
            );
    return *p != 0;
}

template <class T>
bool CBinTree<T>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinTreeNode<T>(x);
    size++;
    return 1;
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    CBinTreeNode<T>** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinTreeNode<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    size--;
    return 1;
}

template <class T>
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
{
    CBinTreeNode<T>** q;
    for ( q = &(*p)->nodes[!brep];
          (*q)->nodes[brep];
          q = &(*q)->nodes[brep] );
    brep = !brep;
    return q;
}
//////////////////////
template <class T>
int CBinTree<T>::Size() {
    return size;
}

template <class T>
void CBinTree<T>::InOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    std::cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

template <class T>
void CBinTree<T>::PreOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    std::cout<<n->value<<" ";
    PreOrder(n->nodes[0]);
    PreOrder(n->nodes[1]);
}

template <class T>
void CBinTree<T>::PosOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    PosOrder(n->nodes[0]);
    PosOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
}

template <class T>
void CBinTree<T>::ReverseOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    ReverseOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
    ReverseOrder(n->nodes[0]);
}

template <class T>
void CBinTree<T>::LevelOrder(CBinTreeNode<T>* n)
{
    if ( !root ) return;
    std::queue< CBinTreeNode<T>* > q;
    for ( q.push(root); !q.empty(); q.pop() )
    {
        std::cout<<q.front()->value<<" ";
        if ( q.front()->nodes[0] ) q.push( q.front()->nodes[0] );
        if ( q.front()->nodes[1] ) q.push( q.front()->nodes[1] );
    }
}

template <class T>
int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n)
{
    if ( !n ) return -1;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print()
{
    std::cout<<"\n";
    InOrder(root);
}




/* ---  IMPLEMENTACIONES  ---*/


template <class T>
void CBinTree<T>::InOrderTrack(CBinTreeNode<T>* data , vector<vector<string>> &v ,  int i, int &j)
{
    if ( !data ) return;
    InOrderTrack(data->nodes[0],v,i+1,j);
    v[i][j++] = std::to_string(data->value);
    InOrderTrack(data->nodes[1],v,i+1,j);
}

template <class T>
void CBinTree<T>::PrintNiveles() {

    int height = MaxDepth(root) + 1 , j = 0;
    vector<vector<string>> vec(height, vector<string> (size, " "));

    InOrderTrack(root,vec,0,j);

    cout<<"\n\n";
    for (int i = 0; i < height; ++i) {
        for (j = 0; j < size; ++j)
            cout<<vec[i][j]<<" ";
        cout<<"\n";
    }
}



template <class T>
void CBinTree<T>::Podarlevel(CBinTreeNode<T> **n, int depth , int level) {

    if( !(*n) || level > depth){
        deleteTree(n); return;
    }
    Podarlevel(&(*n)->nodes[0],depth,level+1);
    Podarlevel(&(*n)->nodes[1],depth,level+1);

}


template <class T>
int CBinTree<T>::PodarTree(CBinTreeNode<T> *n){
    if(!n) return -1;

    int heightRight = PodarTree(n->nodes[1]);
    int heightLeft = PodarTree(n->nodes[0]);

    if(heightLeft != heightRight){
        CBinTreeNode<T> **greater =  &n->nodes[heightRight > heightLeft];
        Podarlevel(greater,min(heightRight,heightLeft),0);
    }
    return PodarTree(n->nodes[0]) + 1;

}


template <class T>
void CBinTree<T>::Podar()
{
    PodarTree(root);
}



int main()
{
    CBinTree<int> t;

    //PRUEBA
//    vector<int> v = {8,3,10,1,0,2,6,9,14,4,7,13,20,18};
    vector<int> v = {50,40,80,30,43,60,95,20,35,73,90,99,10,28};

    for (int i : v) {
        t.Ins(i);
    }


    cout<<"\nAntes de Podar : ";
    t.PrintNiveles();

    t.Podar();

    cout<<"\nDespues de Podar : ";
    t.PrintNiveles();

}


