//
// Created by misash on 11/12/21.
//

#include<iostream>
#include<deque>
#include<list>
#include <vector>

using namespace  std;

template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;

    N value;
    std::list<Edge*> edges;
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
};

/*----------- STRUCT DICTIONARY ------------*/
template<class G>
struct Dictionary{
    typedef typename G::Node   Node;
    typedef typename G::E       E;
    typedef typename G::N       N;
    E distance = -1 ;
    list<Node*> path;
};

/*----------- END STRUCT DICTIONARY ------------*/


template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N,_E>   G;
    typedef CNode<G>        Node;
    typedef CEdge<G>        Edge;
    typedef _N              N;
    typedef _E              E;
    typedef typename std::deque<Node*>::iterator dIter;
    typedef typename std::list<Edge*>::iterator lIter;

    Node* InsNode(N n);
    void InsEdge(Node* a, Node* b, E e, bool d);
    void Path(Node *a, Node *b,std::list<N> &road);
    void PrintPath(std::list<N> &road);

    std::deque<Node*> nodes;


    ///////////////////////////// METODOS PROPIOS //////////////////////////////////


    void initializeValues(){
        init_matrix();
    }
    bool insNodo(N x){
        return InsNode(x);
    }

    int getIndex(Node *n){
        for (dIter it = nodes.begin(); it != nodes.end() ; ++it)
            if((*it) == n) return it-nodes.begin();
    }

    int index_of(N x){
        for (dIter it = nodes.begin(); it != nodes.end() ; ++it)
            if((*it)->value == x) return it-nodes.begin();
    }

    void init_Unvisited(vector<Node*> &unvisited){
        for (auto it = nodes.begin(); it != nodes.end() ; ++it)
            unvisited.push_back(*it);
    }

    void init_matrix(){
        matrix.resize(nodes.size(),vector<Dictionary<G>>(nodes.size()));
    }

    void updateDistances(Node *n,int i){
        for (lIter edge_ptr = n->edges.begin() ; edge_ptr != n->edges.end() ; edge_ptr ++) {
            if( (*edge_ptr)->dir == 0  && (*edge_ptr)->nodes[0] == n){
                int j = getIndex((*edge_ptr)->nodes[0]);
                int k = getIndex((*edge_ptr)->nodes[1]);
                int u = matrix[i][j].distance;
                int uv = (*edge_ptr)->value;
                int v = matrix[i][k].distance;

                if( v == -1 || u + uv < v){
                    matrix[i][k].distance = u + uv;
                    matrix[i][k].path = matrix[i][j].path;
                    matrix[i][k].path.push_back(nodes[k]);
                }
            }
        }
    }

    void remVisitedNode(Node *n,vector<Node*> &unvisited){
        if(!unvisited.size()) return;
        typename  vector<Node*>::iterator  it;
        for ( it = unvisited.begin(); it != unvisited.end() ; ++it){
            if((*it) == n){
                unvisited.erase(it); return;
            }
        }
    }

    void find_Min_Unvisited(int row ,Node *&n,int &min,vector<Node*> &unvisited){
        typename vector<Node*>::iterator it;
        for (it = unvisited.begin() ; it != unvisited.end() ; it ++){
            if (matrix[row][getIndex(*it)].distance != -1 ){
                min = matrix[row][getIndex(*it)].distance; break;
            }
        }
        if(min == -1) return;
        for (it = unvisited.begin() ; it != unvisited.end() ; it ++){
            int d = matrix[row][getIndex(*it)].distance;
            if( ( d != -1 ) && ( d <= min )){
                min = d;
                n = *it;
            }
        }
    }

    void completePath(){
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix.size(); ++j)
                if(matrix[i][j].path.size())
                    matrix[i][j].path.push_front(nodes[i]);
    }

    void Dijkstra(Node *n){
        if(!nodes.size()) return;

        vector<Node*> unvisited;
        init_Unvisited(unvisited);

        int row = getIndex(n);
        int min = 0;
        matrix[row][row].distance = 0;
        while( min != -1 && unvisited.size()){
            updateDistances(n,row);
            remVisitedNode(n,unvisited);
            min = -1;
            find_Min_Unvisited(row,n,min,unvisited);
        }
    }

    void precalulo(){
        initializeValues();

        for (auto it = nodes.begin() ; it != nodes.end() ; ++it){
            Dijkstra(*it);
        }
        completePath();
    }

    vector<vector<Dictionary<G>>> matrix;

};

template<class _N, class _E>
typename CGraph<_N,_E>::Node* CGraph<_N,_E>::InsNode(N n)
{
    Node* tmp = new Node;
    tmp->value = n;
    nodes.push_back(tmp);
    return tmp;

    return 0;
}

template<class _N, class _E>
void CGraph<_N,_E>::InsEdge(Node* a, Node* b, E e, bool d)
{
    Edge *tmp = new Edge;
    tmp->nodes[0]= a;
    tmp->nodes[1]= b;
    tmp->value = e;
    tmp->dir = d;

    a->edges.push_back(tmp);
    b->edges.push_back(tmp);
}

template<class _N, class _E>
void CGraph<_N,_E>::Path(Node *a, Node *b, std::list<N> &road)
{
    //Se realiza un precalculo con un vector 2D
    precalulo();
    Dictionary<CGraph<char,int>> data;
    data = matrix[getIndex(a)][getIndex(b)];
    for (auto it = data.path.begin() ; it != data.path.end() ; it++){
        road.push_back((*it)->value);
    }
}

template<class _N, class _E>
void CGraph<_N,_E>::PrintPath(std::list<N> &road)
{
    std::cout<<"El camino es : ";
    for(auto it = road.begin(); it!=road.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
}



int main()
{
    CGraph<char,int> g;
    CGraph<char,int>::Node* nodes[16];
    char data[16]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    std::list<char> PathGraph;


    for(int i=0; i<16; i++)
        nodes[i] = g.InsNode(data[i]);

    g.InsEdge(nodes[0], nodes[1], 1, 0);
    g.InsEdge(nodes[1], nodes[2], 1, 0);
    g.InsEdge(nodes[1], nodes[5], 1, 0);
    g.InsEdge(nodes[3], nodes[7], 1, 0);
    g.InsEdge(nodes[4], nodes[5], 1, 0);
    g.InsEdge(nodes[4], nodes[8], 1, 0);
    g.InsEdge(nodes[5], nodes[6], 1, 0);
    g.InsEdge(nodes[5], nodes[9], 1, 0);
    g.InsEdge(nodes[6], nodes[7], 1, 0);
    g.InsEdge(nodes[6], nodes[10], 1, 0);
    g.InsEdge(nodes[8], nodes[9], 1, 0);
    g.InsEdge(nodes[9], nodes[10], 1, 0);
    g.InsEdge(nodes[9], nodes[13], 1, 0);
    g.InsEdge(nodes[10], nodes[11], 1, 0);
    g.InsEdge(nodes[10], nodes[14], 1, 0);
    g.InsEdge(nodes[11], nodes[15], 1, 0);
    g.InsEdge(nodes[12], nodes[13], 1, 0);
    g.InsEdge(nodes[13], nodes[14], 1, 0);


    g.Path(nodes[0],nodes[15],PathGraph);
    g.PrintPath(PathGraph);
}
