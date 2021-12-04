//
// Created by misash on 25/11/21.
//

#include <iostream>
#include <list>

using namespace std;

/* FORWARD LIST */

template <class T>
struct CForwardNode{

    T value;
    CForwardNode<T>* next;
    CForwardNode(T x)
    { value = x; next = nullptr; }
};

template <class T>
class CForwardList{
public:
    CForwardList();
    ~CForwardList();
    bool Find(T x,CForwardNode<T>** &p);
    bool Ins(T x);
    bool Rem(T x);
    void Print();

private:
    CForwardNode<T> *head;

};

template <class T>
CForwardList<T>::CForwardList(){
    head = nullptr;
}

template <class T>
CForwardList<T>::~CForwardList(){
    CForwardNode<T>* t = head;
    while(t){
        auto p = t;
        t=t->next;
        delete p;
    }
}

template <class T>
bool CForwardList<T>::Find(T x, CForwardNode<T> **&p){

    for ( p = &head;   *p &&  (*p)->value < x   ; p = &(*p)->next );
    return *p  && (*p)->value == x;
}

template <class T>
bool CForwardList<T>::Ins(T x) {

    CForwardNode<T>** p;
    if ( Find(x,p) ) return 0;
    CForwardNode<T>* t = new CForwardNode<T>(x);
    t->next = *p;
    *p = t;
    return 1;
}

template <class T>
bool CForwardList<T>::Rem(T x) {
    CForwardNode<T>** p;
    if ( !Find(x,p) ) return 0;
    CForwardNode<T>* t = *p;
    *p = t->next;
    delete t;
    return 1;
}


template <class T>
void CForwardList<T>::Print(){
    for(CForwardNode<T> *t = head; t; t = t->next)
        cout<<" -> "<<t->value;
}


/* END FORWARD LIST*/




/* HASH TABLE */



struct CodigoVerificador
{
    inline unsigned int operator()(string dni) {
        int sum = 0;
        int serie[] = {3, 2, 7, 6, 5, 4, 3, 2};
        int codigo[] = {6, 7, 8, 9, 0, 1, 1, 2, 7, 4, 5};

        for (int i = 0; i < dni.size(); ++i)
            sum += (dni[i] - '0') * serie[i];

        return codigo[(11 - (sum % 11)) % 11];
    }
};


template<class T>
struct CListAdaptor{

    CForwardList<T> l;

    void Insert(T v){
        l.Ins(v);
    }
    void Remove(T v){
        l.Rem(v);
    }
    void Print(){
        l.Print();
    }
};



template<class T, class S, class Fd, unsigned long Sz>
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    bool ins(T v);
    bool rem(T v);
    void print();

    S* table;
    Fd fd;

};

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::CHashTable()
{
    table = new S[Sz];
}

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::~CHashTable()
{
    delete[] table;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::ins(T v)
{
    table[ fd(v) % Sz ].Insert(v);
    return 1;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::rem(T v)
{
    table[ fd(v)%Sz ].Remove(v);
    return 1;
}

template<class T, class S, class Fd, unsigned long Sz>
void CHashTable<T,S,Fd,Sz>::print()
{
    cout<<'\n';
    for (int i = 0; i < Sz; ++i) {
        cout<<"| "<<i<<" | ";table[i].Print();cout<<" \n";
    }
}


/* END HASH TABLE */





int main()
{

    /**
     * El siguiente programa almacena los DNI en orden y sin
     * repeticiones en una Tabla Hash , segun su codigo de verificacion
     *
     * Se ingresaron algunos DNI como ejemplo
     *
     */


    CHashTable<string, CListAdaptor<string>, CodigoVerificador , 10> reniec;

    //DNI EJEMPLO
    reniec.ins("17801146");
    reniec.ins("72039840");
    reniec.ins("30960533");
    reniec.ins("72414960");


    bool play = 1;
    while(play){

        int op;
        string dni;

        do{
            cout<<"\n\t** RENIEC **";
            cout<<"\n\n1.Agregar DNI";
            cout<<"\n2.Borrar DNI";
            cout<<"\n3.Imprimir Hash Table";
            cout<<"\n4.Salir";
            cout<<"\n\nseleciona una opcion > "; cin>>op;
        }while(op < 1 || op > 4);

        cin.ignore();

        switch (op) {
            case 1:
                cout<<"\nIngrese su DNI: ";
                getline(cin,dni);
                reniec.ins(dni);
                break;
            case 2:
                cout<<"\nIngrese su DNI a borrar: ";
                getline(cin,dni);
                reniec.rem(dni);
                break;
            case 3:
                cout<<"\nHash Table DNI\n";
                reniec.print();
                break;

            default: play = 0; break;
        }

    }

}
