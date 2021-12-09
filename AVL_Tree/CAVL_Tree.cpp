//
// Created by misash on 7/12/21.
//

#include <iostream>
#include <queue>
#include <stack>
#include <vector>


//#define abs(x)  (x>0)? x:-1*x

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
    typedef CBinTreeNode<T> Node;
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p,stack<CBinTreeNode<T>**> &s);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p,stack<Node **> &path);
    void InOrder(CBinTreeNode<T>* n);
    void PreOrder(CBinTreeNode<T>* n);
    void PosOrder(CBinTreeNode<T>* n);
    void ReverseOrder(CBinTreeNode<T>* n);
    void LevelOrder(CBinTreeNode<T>* n);
    int MaxDepth(CBinTreeNode<T>* n);
    void Print();
    //AVL
    int getFactor(Node *);
    void Balance( stack<Node **> &s);
    void RightRight(CBinTreeNode<T> **&);
    void LeftLeft(Node **&p);
    void LeftRight(Node **&p);
    void RightLeft(Node **&p);
    //PRINT
    void InOrderTrack(CBinTreeNode<T> *data, vector<vector<string>> &v, int i, int &j);
    void PrintNiveles();
    int Size();

private:
    CBinTreeNode<T>* root;
    bool brep;
    int size ;
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
    //...
}

template <class T>
int CBinTree<T>::Size() {
    return size;
}

template <class T>
CBinTreeNode<T>* CBinTree<T>::Root()
{
    return root;
}

//---------- R O T A T E S ---------------//


template <class T>
void CBinTree<T>::RightRight(Node** &p)
{
    Node *temp = (*p)->nodes[1]->nodes[0];
    (*p)->nodes[1]->nodes[0] = *p;
    *p = (*p)->nodes[1];
    (*p)->nodes[0]->nodes[1] = temp;
}

template <class T>
void CBinTree<T>::LeftLeft(Node** &p)
{
    Node *temp = (*p)->nodes[0]->nodes[1];
    (*p)->nodes[0]->nodes[1] = *p;
    *p = (*p)->nodes[0];
    (*p)->nodes[1]->nodes[0] = temp;
}

template <class T>
void CBinTree<T>::LeftRight(Node** &p)
{
    Node *temp_left = (*p)->nodes[0]->nodes[1]->nodes[0];
    Node *temp_right = (*p)->nodes[0]->nodes[1]->nodes[1];
    (*p)->nodes[0]->nodes[1]->nodes[0] = (*p)->nodes[0];
    (*p)->nodes[0]->nodes[1]->nodes[1] = *p;
    *p = (*p)->nodes[0]->nodes[1];
    (*p)->nodes[0]->nodes[1] = temp_left;
    (*p)->nodes[1]->nodes[0] = temp_right;
}

template <class T>
void CBinTree<T>::RightLeft(Node** &p)
{
    Node *temp_left = (*p)->nodes[1]->nodes[0]->nodes[0];
    Node *temp_right = (*p)->nodes[1]->nodes[0]->nodes[1];
    (*p)->nodes[1]->nodes[0]->nodes[1] = (*p)->nodes[1];
    (*p)->nodes[1]->nodes[0]->nodes[0] = *p;
    *p = (*p)->nodes[1]->nodes[0];
    (*p)->nodes[1]->nodes[0] = temp_right;
    (*p)->nodes[0]->nodes[1] = temp_left;
}

//---------- E N D  R O T A T E S ---------------//

//----------- B A L A N C E ----------------------//

template <class T>
int CBinTree<T>::getFactor(Node *n){
    if(!n) return -1;
    return MaxDepth(n->nodes[0]) - MaxDepth(n->nodes[1]);
}

template <class T>
void CBinTree<T>::Balance(stack<Node**> &path){

    // traverse until an unbalanced subtree is found
    for ( ; !path.empty() && abs(getFactor(*path.top())) != 2  ; path.pop());
    if(path.empty()) return;

    Node** root = path.top();
    int factorBalance = getFactor(*root);;

    //rotate
    if( factorBalance == -2 && getFactor((*root)->nodes[1]) < 0)
        RightRight(root);
    else if( factorBalance == -2 && getFactor((*root)->nodes[1]) > 0)
        RightLeft(root);
    else if( factorBalance == 2 && getFactor((*root)->nodes[0]) > 0)
        LeftLeft(root);
    else if( factorBalance == 2 && getFactor((*root)->nodes[0]) < 0)
        LeftRight(root);
}

//template <class T>
//void CBinTree<T>::Balance(Node **n,stack<Node**> &path){
//
//    // traverse until an unbalanced subtree is found
//    for ( ; !path.empty() && abs(getFactor(*path.top())) != 2  ; path.pop());
//    if(path.empty()) return;
//
//    Node** root = path.top();
//    int factorBalance = getFactor(*root);;
//
//    //rotate
//    if( factorBalance == -2 && (*n)->value > (*root)->nodes[1]->value) RightRight(root);
//    else if( factorBalance == -2 && (*n)->value < (*root)->nodes[1]->value) RightLeft(root);
//    else if( factorBalance == 2 && (*n)->value < (*root)->nodes[0]->value) LeftLeft(root);
//    else if( factorBalance == 2 && (*n)->value > (*root)->nodes[0]->value) LeftRight(root);
//}


//----------- E N D  B A L A N C E ----------------------//

template <class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p, stack<CBinTreeNode<T>**> &s)
{
    for ( p = &root; *p && (*p)->value != x ; p = &((*p)->nodes[ (*p)->value < x ]))
        s.push(p);

    return *p != 0;
}

template <class T>
bool CBinTree<T>::Ins(T x)
{
    CBinTreeNode<T>** p;
    stack<CBinTreeNode<T>**> path;
    if ( Find(x,p,path) ) return 0;
    *p = new CBinTreeNode<T>(x);
    size++;
    Balance(path);
    return 1;
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    CBinTreeNode<T>** p;
    stack<CBinTreeNode<T>**> path;
    if ( !Find(x,p,path) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinTreeNode<T>** q = Rep(p,path);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    size--;
    Balance(path);
    return 1;
}

template <class T>
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p,stack<Node **> &path)
{
    CBinTreeNode<T>** q;
    for ( q = &(*p)->nodes[!brep];(*q)->nodes[brep];q = &(*q)->nodes[brep] ){
       path.push(q);
    }
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

/* -------  P R I N T  L E V E L S-------------*/


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
    vector<vector<string>> vec(height, vector<string> (size, "  "));

    InOrderTrack(root,vec,0,j);

    cout<<"\n\n";
    for (int i = 0; i < height; ++i) {
        for (j = 0; j < size; ++j)
            cout<<vec[i][j]<<"  ";
        cout<<"\n";
    }
}

/* ------- E N D   P R I N T  L E V E L S-------------*/

int main()
{
    CBinTree<int> t;
    std::cout<<"ins \n";

    vector<int> vec = {14,17,11,7,53,4,13,12,8,60,19,16,20};
    for (int i = 0; i <vec.size() ; ++i) t.Ins(vec[i]);

//    t.Rem(8);
//    t.Rem(7);


    t.PrintNiveles();

    t.Rem(8);
    t.Rem(7);
    t.Rem(11);
    t.Rem(14);
    t.Rem(17);
    t.PrintNiveles();
    t.Rem(4);
    t.Rem(19);
    t.Rem(16);
    t.Rem(12);
    t.Rem(13);

    t.PrintNiveles();

}

