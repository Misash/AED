//
// Created by eileen
//
#include <iostream>
#include<deque>
#include <thread>
#include<list>
#include <vector>

using namespace std;

/////////////////////////////// GRAFO MULTIPROPOSITO /////////////////////////////

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
    bool dir;
};

/////////////// NODO ESPECIAL  ///////////////////////////
template<class G>
struct SpecialNode{
    typedef typename G::N       N;
    typedef typename G::Node   Node;
    typedef typename G::E       E;
    list<Node*> path;
    E peso = -1 ;
};
///////////////////////////////////////////////////////////
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

    bool InsEdgeHelper(Node* a, Node* b, E e, bool dir=1){
        if(!a || !b) return 0;
        Edge* edge_ptr = new Edge(a,b,e,dir);
        a->edges.push_back(edge_ptr);
        b->edges.push_back(edge_ptr);
        return 1;
    }

    bool InsEdge(N a,N b,E e ,bool dir=1){
        dIter it[2];
        if(!FindNode(a,it[0]) || !FindNode(b,it[1])) return 0;
        InsEdgeHelper(*it[0],*it[1],e,dir);
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


    int getIndex(Node *n){
        for (dIter it = nodes.begin(); it != nodes.end() ; ++it)
            if((*it) == n) return it-nodes.begin();
    }
    int index_of(N x){
        for (dIter it = nodes.begin(); it != nodes.end() ; ++it)
            if((*it)->value == x) return it-nodes.begin();
    }

    void init_matrix(){
        deque2D.resize(nodes.size(),deque<SpecialNode<G>>(nodes.size()));
    }

    //////////////////// DIJKSTRA ///////////////////////////////////////////
    void dijkstra(Node *n){
        if(!nodes.size()) return;
        vector<Node*> no_visitados;

        for (auto it = nodes.begin(); it != nodes.end() ; ++it)
            no_visitados.push_back(*it);
        int fila = getIndex(n),minPeso;
        deque2D[fila][fila].peso = minPeso = 0;
        do{
            for (auto ptr = n->edges.begin() ; ptr != n->edges.end() ; ptr ++) {
                if( (*ptr)->dir && (*ptr)->nodes[0] == n ){
                    int j = getIndex((*ptr)->nodes[1]);
                    if( deque2D[fila][j].peso == -1 || deque2D[fila][getIndex((*ptr)->nodes[0])].peso + (*ptr)->value < deque2D[fila][j].peso){
                        deque2D[fila][j].peso = deque2D[fila][getIndex((*ptr)->nodes[0])].peso + (*ptr)->value;
                        deque2D[fila][j].path = deque2D[fila][getIndex((*ptr)->nodes[0])].path;
                        deque2D[fila][j].path.push_back(nodes[j]);
                    }
                }
            }
            for (  typename vector<Node*>::iterator  it = no_visitados.begin(); it != no_visitados.end() ; ++it)
                if((*it) == n) {no_visitados.erase(it);break;}
            minPeso = -1;
            typename vector<Node*>::iterator it;
            for (it = no_visitados.begin() ; it != no_visitados.end() ; it ++){
                if (deque2D[fila][getIndex(*it)].peso != -1 ){
                    minPeso = deque2D[fila][getIndex(*it)].peso; break;
                }
            }
            for (it = no_visitados.begin() ; it != no_visitados.end() ; it ++){
                int peso = deque2D[fila][getIndex(*it)].peso;
                if( ( peso != -1 ) && ( peso <= minPeso )){
                    minPeso = peso;
                    n = *it;
                }
            }
        }while(minPeso != -1 );
    }

    void helper(dIter it ){
        for (auto iter = it ; iter != it+1 ; ++iter)
            dijkstra(*iter);
    }

    void Secuencial(){
        for (int i = 0; i < deque2D.size(); ++i){
            for (int j = 0; j < deque2D.size(); ++j){
                if(deque2D[i][j].path.size()){
                    deque2D[i][j].path.push_front(nodes[i]);
                }
            }
        }
    }

    void pre_process(){

        /////////////  THREADS  /////////////////////

        init_matrix();
        int numths = 5; // 5 threads
        vector<thread> ths(numths);
        for (int i = 0 ; i < numths; i++){
            ths[i] = thread(&CGraph::helper,this,nodes.begin()+i);
        }
        for (int i = 0; i < numths; i++ ){
            ths[i].join();
        }
        Secuencial();
    }

    SpecialNode<CGraph<N,E>> getSNode(int a, int b){
        return deque2D[index_of(a)][index_of(b)];
    }

    void printRecorrido( SpecialNode<CGraph<N,E>> data){
        for (auto it = data.path.begin() ; it != data.path.end() ; it++)
            cout<<" -> "<<(*it)->value;
    }

    std::deque<Node*> nodes;
    deque<deque<SpecialNode<G>>> deque2D; //Data structure
};




int main()
{

    CGraph<int,int> graph;

    //insert nodes
    graph.InsNode(5);graph.InsNode(4);
    graph.InsNode(1);graph.InsNode(2);
    graph.InsNode(3);

    //insert edges
    graph.InsEdge(1, 5, 10);graph.InsEdge(1, 2, 2);
    graph.InsEdge(2, 3, 3);graph.InsEdge(2, 5, 7);
    graph.InsEdge(3, 1, 4);graph.InsEdge(3, 4, 4);
    graph.InsEdge(4, 5, 5);graph.InsEdge(5, 3, 3);

    graph.pre_process();
    SpecialNode<CGraph<int,int>> snode;

    /**
     *
     * El programa esta diseñado con un deque 2D para almacenar
     * nodos , los cuales tienen peso y una lista de punteros a nodos
     * ademas , utiliza 5 threads en total uno para cada nodo
     * usando el algoritmo de dijkstra
     *
     * para utlizar el programa solo ingrese
     * el nodo origen y final , se
     * calculara:
     *  - distancia mas corta
     *  - impresion de recorrido
     *
     */

    while(1){

        int op,u,v;

        do{
            cout<<"\n\n ---------------------------------------------------";
            cout<<"\n\n PRECALCULO GRAFO ";
            cout<<"\n\n1| Calcular camino mas corto entre dos nodos";
            cout<<"\n2| Salir";
            cout<<"\n\neliga una opcion : ";
            cin>>op;
        }while(op < 1 || op > 2);

        cin.ignore();

        if(op == 1){
            cout<<"\nIngrese el nodo de partida: "; cin >> u;
            cout<<"\nIngrese el nodo de llegada: "; cin >> v;
            snode = graph.getSNode(u, v);
            cout << "\nDistancia entre " << u << " y  " << v << " es " << snode.peso;
            cout<<"\nEl recorrido es : ";
            graph.printRecorrido(snode);
        }
        if(op == 2){
            break;
        }
    }

}
