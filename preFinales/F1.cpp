#include <iostream>
#include <vector>
using namespace std;

// Estructura de datos para almacenar nodos de lista de adyacencia
struct Node
{
	int val;
	Node* next;
};

// Estructura de datos para almacenar una arista de grafo
struct Edge {
	int src, dest;
};

class Graph
{

public:
	// Función para asignar un nuevo nodo para la lista de adyacencia
	Node* getAdjListNode(int dest, Node* head)
	{
		Node* newNode = new Node;
		newNode->val = dest;

		// apunta nuevo nodo a la cabeza actual
		newNode->next = head;

		return newNode;
	}

	int N;	// número total de nodos en el grafo



	// Una array de punteros al nodo para representar la
	// lista de adyacencia
	Node** head;

	// Constructor
	Graph(Edge edges[], int n, int N)
	{
		// asignar memoria
		head = new Node * [N]();
		this->N = N;

		// inicializar el puntero de cabeza para todos los vértices
		for (int i = 0; i < N; i++) {
			head[i] = nullptr;
		}

		// agregar aristas al grafo dirigido
		// se insertan aristas de ida y vuelta
		for (unsigned i = 0; i < n; i++)
		{
			int src = edges[i].src;
			int dest = edges[i].dest;

			// insertar al principio
			Node* newNode = getAdjListNode(dest, head[src]);

			// apuntar el puntero de la cabeza al nuevo nodo
			head[src] = newNode;

			
			newNode = getAdjListNode(src, head[dest]);

			// cambia el puntero de la cabeza para que apunte al nuevo nodo
			head[dest] = newNode;
			
		}
	}

	// Destructor
	~Graph() {
		for (int i = 0; i < N; i++) {
			delete[] head[i];
		}

		delete[] head;
	}

    int NumeroEdges(Node** n){
        int count=0;
        for (Node * i = *n; i ; i = i->next) {
            count++;
        }
        return count;
    }

    bool isvalidEdge(Node **v,Node *av){
        //av is unique adjacent vertex
        if(NumeroEdges(v) == 1) return 1;
        if(NumeroEdges(v) > 1 && NumeroEdges(&head[av->val]) != 1){
            //multiple vertex and not bridge ( mean has just one edge )
            return 1;
        }
        return 0;
    }

    void removeEdge(Node **v ,Node* av){
        if(!*v || !av) return;
        int i_init = v - &head[0];
        int i_final = av->val;

        //borrar del initializeValues
        for (Node **i = &head[i_init]; *i ; i = &(*i)->next) {
            if((*i)->val == av->val){
                Node *t = *i;
                *i = (*i)->next;
                t = 0;
                break;
            }
        }
        //borrar del final
        for (Node **i = &head[i_final]; *i ; i = &(*i)->next) {
            if((*i)->val == i_init){
                Node *t = *i;
                *i= (*i)->next;
                t = 0;
                break;
            }
        }
    }

    void printEulerPath(Node **v){

        for (Node *av = *v; av ; av = av->next) {
            if( isvalidEdge(v,av)){
//                cout<<"\n N: "<<av->val<<" \n";
                cout<<" ("<<v - &head[0]<<" - "<<av->val<<") ";
                int index = av->val;
                removeEdge(v,av);
//                for (int i = 0; i < N; i++){
//                    cout << i << " --";
//                    printList(head[i]);
//                }
//                cout<<endl;

                printEulerPath(&head[index]);
            }
        }
    }


    void printTravelEdge(int index)
    {

        printEulerPath(&head[index]);

    }

    void printList(Node* ptr)
    {
        while (ptr != nullptr)
        {
            cout << " -> " << ptr->val << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }

    void init(Edge edges[], int n, int N){
        Graph(edges,n,N);
    }

};

// Función para imprimir todos los vértices vecinos de un vértice dado


// Halla todos los recorridos desde el nodo ptr que recorra
// todas las aristas del grafo, sin repetir una arista
// se puede pasar por un nodo mas de una vez










// Implementación de grafos
int main()
{
	// un array de aristas del grafo según el diagrama
	Edge edges[] =
	{
		// par `(x, y)` representa una arista de `x` a` y`
		{ 0, 1 }, { 0, 2 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 4 }, { 3, 4 }
	};

	// número total de nodos en el grafo
	int N = 5;

	// calcula el número total de aristas
	int n = sizeof(edges) / sizeof(edges[0]);

	// construir grafo
	Graph graph(edges, n, N);


    // imprimir la representación de la lista de adyacencia de un grafo
    for (int i = 0; i < N; i++)
    {
        // imprimir el vértice dado
        cout << i << " --";

        // imprime todos sus vértices vecinos
        graph.printList(graph.head[i]);

    }


//    graph.removeEdge(&graph.head[0],graph.head[0]);



	//prueba de recorridos de aristas
	for (int i = 0; i < N; i++)
	{
		// imprimir el vértice de inicio
		cout << "\nPartiendo del nodo " << i << endl;

		// imprime el recorrido de todas las aristas sin repetir
        graph.printTravelEdge(i);
        graph.init(edges, n, N);
	}


	return 0;
}