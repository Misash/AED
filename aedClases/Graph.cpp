#include <iostream>
#include<deque>
#include<list>

using namespace std;


template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;
    CNode(N val){value = val;}
    N value;
    std::list<Edge*> edges;
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;
    CEdge(Node * a ,Node* b,E val,bool d){
        value = val;  dir = d;
        nodes[0] = a; nodes[1] = b;
    }
    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
};

template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N,_E>   G;
    typedef CNode<G>        Node;
    typedef CEdge<G>        Edge;
    typedef   _N            N;
    typedef   _E            E;
    typedef typename std::deque<Node*>::iterator dIter;
    typedef typename std::list<Edge*>::iterator lIter;

    bool FindNode(N x , dIter &it){
        for (it = nodes.begin();it != nodes.end() ; it++)
            if ((*it)->value == x) return 1;
        return 0;
    }

    bool FindEdge(Node* a, Node* b, E e , lIter &it , bool d=1  ){
        if(!a || !b) return 0;
        for (it = a->edges.begin() ; it != a->edges.end() ; it++) {
            bool verify = ((*it)->nodes[0] == a && (*it)->nodes[1] == b); // ->
            if(!d) verify = verify || ((*it)->nodes[0] == b && (*it)->nodes[1] == a); // <-->
            if((*it)->value == e && verify && (*it)->dir == d ) return 1;
        }
        return 0;
    }

    bool InsNode(N data){
        dIter it;
        if(FindNode(data,it)) return 0;
        Node* n = new Node(data);
        nodes.push_back(n);
        return 1;
    }

    bool InsEdge(Node* a, Node* b, E e, bool dir=1){
        if(!a || !b) return 0;
        Edge* edge_ptr = new Edge(a,b,e,dir);
        a->edges.push_back(edge_ptr);
        b->edges.push_back(edge_ptr);
        return 1;
    }

    bool RemEdge(Node* a, Node* b, E e, bool dir=1){
        lIter it[2];
        if(!FindEdge(a,b,e,it[0],dir) || !FindEdge(b,a,e,it[1],dir)) return 0;
        a->edges.erase(it[0]);
        b->edges.erase(it[1]);
        delete  *it[0];
        return 1;
    }

    bool RemNode(N n){
        dIter node;
        if(!FindNode(n,node)) return 0;
        for (lIter it=(*node)->edges.begin(); it != (*node)->edges.end(); ++it)
            RemEdge((*it)->nodes[0],(*it)->nodes[1],(*it)->value,(*it)->dir);
        nodes.erase(node);
        return 1;
    }

    void Print(){
        cout<<"\nprint:";
        for (dIter n = nodes.begin() ; n != nodes.end() ; ++n) {
            for (lIter e = (*n)->edges.begin() ; e != (*n)->edges.end() ; e++) {
                Node * b = (*e)->nodes[1];
                if( (*e)->dir  && (*e)->nodes[0] == *n ){
                    cout<<"\n"<<(*n)->value<<" -> "<<(*e)->value<<" "<<b->value;
                }else{
                    cout<<"\n"<<(*n)->value<<" <-> "<<(*e)->value<<" "<<b->value;
                }

            }
            cout<<"\n";
        }
    }

    std::deque<Node*> nodes;
};

struct Coord
{
    float x,y;
};


class CGraphCity : public CGraph<Coord,int>
{
    // algoritmos optimizados con coordenas
    /*
     busquedas direccionada
     precalculo
     etc
     */
};

class CGraphChar : public CGraph<char,int>
{
    // algoritmos no optimizados
    void Print();
    /*
     implementar dikjstra, etc
     */
};

int main()
{
    CGraphChar g1;
    CGraphCity g2;

    CGraph<char,int> g;

   CNode<CGraph<char,int>> a('a');
   CNode<CGraph<char,int>> b('b');
    CNode<CGraph<char,int>> c('c');

   g.nodes.push_back(&a);
   g.nodes.push_back(&c);
   g.nodes.push_back(&b);


    g.InsEdge(&a,&c,5);

    g.RemEdge(&c,&b,2,0);

    g.Print();



}
