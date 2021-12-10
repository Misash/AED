#include <iostream>
#include <thread>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CAVLNode
{
    CAVLNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0;  }
    int value;
    CAVLNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CAVLTree
{
public:
    CAVLTree();
    ~CAVLTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    int MaxNodeHeight(CAVLNode* n);
    int MaxHeight();
    void MaxNodeHeightThread(CAVLNode *n, int &height);
    void PrintNiveles();

private:
    bool Find(int x, CAVLNode**& p);
    CAVLNode** Rep(CAVLNode** p);
    void InOrder(CAVLNode* n);
    CAVLNode* m_root;
    int size;
    void InOrderTrack(CAVLNode *data, vector<vector<string>> &v, int i, int &j);

};

CAVLTree::CAVLTree()
{   m_root = 0; size= 0;}

CAVLTree::~CAVLTree()
{}

bool CAVLTree::Find(int x, CAVLNode**& p)
{
    for ( p = &m_root ; *p && (*p)->value != x ; p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CAVLTree::Insert(int x)
{
    CAVLNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CAVLNode(x);
    size++;
    return 0;
}
bool CAVLTree::Remove(int x)
{
    CAVLNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CAVLNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CAVLNode* t = *p;
    *p = (*p)->nodes[ !(*p)->nodes[0] ];
    delete t;
    size--;
    return 1;
}

CAVLNode** CAVLTree::Rep(CAVLNode** p)
{
    bool b = rand()%2;
    for( p = &( (*p)->nodes[b] ); (*p)->nodes[!b]; p = &( (*p)->nodes[!b] ) );
    return p;
}

void CAVLTree::InOrder(CAVLNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CAVLTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

//======================================================
void CAVLTree::MaxNodeHeightThread(CAVLNode* n, int& height)
{
    height = MaxNodeHeight(n);
}
//======================================================




int CAVLTree::MaxNodeHeight(CAVLNode* n)
{
    if ( !n ) return 0;
    return std::max(MaxNodeHeight(n->nodes[0]), MaxNodeHeight(n->nodes[1])) + 1;
}

int CAVLTree::MaxHeight()
{
    CAVLNode * A = m_root;
    CAVLNode * B = m_root->nodes[0];
    CAVLNode * C = m_root->nodes[1];

    //threads
    int nt = 4;
    vector<thread> ths(nt);
    int hb[2],hc[2];


    //hallar alturas de hijos de B
    for (int i = 0; i < 2; ++i) {
        ths[i] = thread(&CAVLTree::MaxNodeHeightThread,this,(B->nodes[i]),ref(hb[i]));
    }

    //hallar alturas de hijos de C
    for (int i = 0; i < 2; ++i) {
        ths[i+2] = thread(&CAVLTree::MaxNodeHeightThread,this,(C->nodes[i]),ref(hc[i]));
    }

    //wait threads
    for ( int i = 0; i < nt; i++ )
        ths[i].join();

    //parte secuencial
    int hB = max(hb[0],hb[1]) + 1;
    int hC = max(hc[0],hc[1]) + 1;
    int hA = max(hB , hC) + 1;
    return hA;
}

/*  ---------- PRINT LEVELS  -------*/


void CAVLTree::InOrderTrack(CAVLNode* data , vector<vector<string>> &v ,  int i, int &j)
{
    if ( !data ) return;
    InOrderTrack(data->nodes[0],v,i+1,j);
    v[i][j++] = std::to_string(data->value);
    InOrderTrack(data->nodes[1],v,i+1,j);
}


void CAVLTree::PrintNiveles() {

    int height = MaxNodeHeight(m_root)  , j = 0;
    vector<vector<string>> vec(height, vector<string> (size, "  "));

    InOrderTrack(m_root,vec,0,j);

    cout<<"\n\n";
    for (int i = 0; i < height; ++i) {
        for (j = 0; j < size; ++j)
            cout<<vec[i][j]<<"  ";
        cout<<"\n";
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int v[150] = {239, 389, 128, 46, 235, 65, 423, 417, 121, 451, 396, 331, 158, 100, 95, 353, 470, 207, 453, 156, 98, 160, 373, 44, 313, 284, 152, 131, 236, 340, 369, 408, 411, 174, 141, 69, 96, 451, 259, 28, 234, 158, 168, 100, 379, 1, 487, 307, 182, 486, 385, 221, 30, 305, 41, 115, 415, 227, 166, 85, 220, 446, 127, 66, 316, 298, 144, 446, 65, 425, 241, 160, 215, 346, 212, 341, 44, 452, 226, 168, 132, 230, 448, 173, 174, 483, 59, 237, 436, 28, 472, 2, 142, 194, 203, 355, 410, 78, 418, 489, 220, 258, 19, 411, 373, 216, 311, 31, 411, 357, 334, 205, 118, 471, 252, 291, 389, 40, 389, 437, 36, 134, 475, 401, 448, 133, 30, 251, 456, 220, 417, 302, 256, 34, 120, 115, 318, 459, 110, 251, 392, 360, 261, 389, 450, 122, 308, 188, 212, 37};
    
    CAVLTree t;
    for ( int i = 0; i < 150; i++ )
        t.Insert(v[i]);
    t.PrintNiveles();

    cout<<"\nMax Height is: "<<t.MaxHeight()<<endl;

    
}


