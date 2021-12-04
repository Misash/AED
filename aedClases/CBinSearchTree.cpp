#include <iostream>
#include <queue>

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

private:
    CBinTreeNode<T>* root;
    bool brep;
};

template <class T>
CBinTree<T>::CBinTree()
{
    root = 0;
    brep = 0;
}

template <class T>
CBinTree<T>::~CBinTree()
{
    //...
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

int main()
{
    CBinTree<int> t;
    std::cout<<"ins \n";
    t.Ins(65);
    t.Ins(41);
    t.Ins(79);
    t.Ins(33);
    t.Ins(51);
    t.Ins(79);
    t.Ins(68);
    t.Ins(71);
    t.Ins(81);

   t.LevelOrder(t.Root());


}




/*
 template <class T>
 CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
 {
     int b = rand()%2;
     CBinTreeNode<T>** q = &(*p)->nodes[b];
     while ( (*q)->nodes[!b] )
         q = &(*q)->nodes[!b];
     return q;
 }

 template <class T>
 CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
 {
     CBinTreeNode<T>** q = &(*p)->nodes[!brep];
     while ( (*q)->nodes[brep] )
         q = &(*q)->nodes[brep];
     brep = !brep;
     return q;
 }

 template <class T>
 int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n)
 {
     if ( !n ) return 0;
     int l, r;
     l = MaxDepth(n->nodes[0]);
     r = MaxDepth(n->nodes[1]);
     return (l>r ? l : r) + 1;
 }

 */