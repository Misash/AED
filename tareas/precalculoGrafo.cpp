//
// Created by misash on 2/12/21.
//

#include <iostream>
#include<deque>
#include <vector>
#include<list>
#include <thread>

using namespace std;

/*----------- GENERAL GRAPH  ------------*/
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


    std::deque<Node*> nodes;
};

/*----------- END GENERAL GRAPH CLASS ------------*/


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


/*----------- PARTICULAR GRAPH CLASS ------------*/


class myGrafo : public CGraph<int,int>
{

public:

    void initializeValues(){
        init_matrix();
    }

    bool insArista(N a,N b,E e ,bool dir=1){
        dIter it[2];
        if(!FindNode(a,it[0]) || !FindNode(b,it[1])) return 0;
        InsEdge(*it[0],*it[1],e,dir);
        return 1;
    }

    bool insNodo(N x){
        return InsNode(x);
    }

    void print(){
        cout<<"\nprint:";
        for (dIter n = nodes.begin() ; n != nodes.end() ; ++n) {
            for (lIter e = (*n)->edges.begin() ; e != (*n)->edges.end() ; e++) {
                Node * b = (*e)->nodes[1];
                if( (*e)->dir  && (*e)->nodes[0] == *n )
                    cout<<"\n|"<<(*n)->value<<"| - "<<(*e)->value<<" -> |"<<b->value<<"|";
            }
        }
    }
    /*-----------------  DIJKSTRA ------------------------*/

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
            if( (*edge_ptr)->dir && (*edge_ptr)->nodes[0] == n ){
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
        vector<Node*>::iterator  it;
        for ( it = unvisited.begin(); it != unvisited.end() ; ++it){
            if((*it) == n){
                unvisited.erase(it); return;
            }
        }
    }

    void find_Min_Unvisited(int row ,Node *&n,int &min,vector<Node*> &unvisited){
        vector<Node*>::iterator it;
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

    void F1(dIter it , int n){
        for (auto i = it ; i != it+n ; ++i)
            Dijkstra(*i);
    }

    void printMatrixDistancias(){
        cout<<endl;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                cout<<matrix[i][j].distance<<"\t";
            }
            cout<<endl;
        }
    }

    void printDistanciasCaminos(){
        cout<<"\nNodos  -  Distancia  - Caminos";
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                cout<<"\n"<<nodes[i]->value<<" - "<<nodes[j]->value<<" |\t\t "<<matrix[i][j].distance<<" :\t";
                for (auto it = matrix[i][j].path.begin() ; it != matrix[i][j].path.end() ; it++) {
                    cout<<" -> "<<(*it)->value;
                }
            }
            cout<<endl;
        }
    }


    void precalculo(){

        initializeValues();
        /* ------------------- T H R E A D S ----------------------*/
        //numero de threads a utilizar
        int nt = thread::hardware_concurrency();
        if( matrix.size() < nt ) nt = matrix.size();

        //asignacion de numero de nodos por thread
        int chunk = matrix.size() / nt ;
        int chunk_b = matrix.size() % nt;

        vector<thread> ths(nt);
        //paralelismo
        for ( int i = 0, j = 0; i < nt; i++ , j+= (chunk + (chunk_b-- > 0)))
            ths[i] = thread(&myGrafo::F1,this,nodes.begin()+j,chunk + (chunk_b > 0));

        //wait threads
        for ( int i = 0; i < nt; i++ ) ths[i].join();

        //parte secuencial
        completePath();

        /* ------------------- T H R E A D S--------------------*/
    }

    vector<vector<Dictionary<G>>> matrix;
};

/*----------- END PARTICULAR GRAPH CLASS ------------*/



int main()
{

    /**
     *      PREPROCESADO DE GRAFO
     *
     * EL programa hace un precalculo de la distancia
     * y camino mas corto del grafo, para esto se  utiliza el algoritmo
     * de Dijkstra , ademas se usa threads para que este programa sea
     * escalable  , el programa utiliza todos threads del computador y
     *  dividiendolos de la manera mas pareja posible asignando una cantidad
     *  de nodos a cada thread
     *
     *  FEATURES:
     *   - calcular la distancia y camino mas corto entre dos nodos
     *   - imprimir la matriz de distanias
     *   - imprimir la distancia y camino de todo el grafo
     *
     */

   myGrafo g;

  g.insNodo(5);
  g.insNodo(4);
  g.insNodo(2);
  g.insNodo(3);
  g.insNodo(1);

  g.insArista(1,5,10);
  g.insArista(1,2,2);
  g.insArista(2,3,3);
  g.insArista(2,5,7);
  g.insArista(3,1,4);
  g.insArista(3,4,4);
  g.insArista(4,5,5);
  g.insArista(5,3,3);


  g.precalculo();

    bool play = 1;
    while(play){

        int op;

        do{
            cout<<"\n\n\t** PREPROCESADO DE GRAFO **";
            cout<<"\n\n1.Calcular camino mas corto entre dos nodos";
            cout<<"\n2.Imprimir matriz de distancias";
            cout<<"\n3.Imprimir distancias y caminos mas cortos del grafo";
            cout<<"\n4.Salir";
            cout<<"\n\nseleciona una opcion > "; cin>>op;
        }while(op < 1 || op > 4);

        cin.ignore();
        Dictionary<CGraph<int,int>> data;
        switch (op) {
            case 1:
                int a,b;
                cout<<"\nIngrese el nodo de partida y llegada: "; cin>>a>>b;
                 data = g.matrix[g.index_of(a)][g.index_of(b)];
                cout<<"\nDistancia : "<<data.distance;
                if(data.distance == -1) break;
                cout<<"\nPath : ";
                for (auto it = data.path.begin() ; it != data.path.end() ; it++)
                    cout<<" -> "<<(*it)->value;
                break;
            case 2:
                cout<<"\n-- MATRIZ DE DISTANCIAS --\n";
                g.printMatrixDistancias();
                break;
            case 3:
                cout<<"\n--DISTANCIAS Y  CAMINOS MAS CORTOS --\n";
                g.printDistanciasCaminos();
                break;

            default: play = 0; break;
        }
    }





}
