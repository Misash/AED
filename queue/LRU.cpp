//
// Created by misash on 18/10/21.
//

#include <iostream>

using namespace std;


template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = nullptr;
    }
    T value;
    CNode *next, *prev;
};

template<class T>
class CList
{
public:
    CList()
    {
        head = tail = nullptr;
        nelem = 0;
    }
    ~CList()
    {
        //...
    }

    void push_back(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        nelem++;
    }

    void pop_back()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode<T>* aux = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    void push_front(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem++;
    }

    void pop_front()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode<T>* aux = head;
            head = head->next;
            head->prev = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    int& operator[](int i)
    {
        CNode<T>* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }

    //////////////////////////////////////

    bool find(int x , CNode<T> **&p){

        for(p = &head ; *p ; p=&(*p)->next)
            if( (*p)->value.first == x)
                return 1;

        return 0;
    }

    void remove(CNode<T>**&p){
        if(!(*p)->next) pop_back();
        else{
            CNode<T> * temp = *p;
            *p = (*p)->next;
            (*p)->prev = temp->prev;
            delete temp;
            nelem -=(nelem)? 1:0;
        }
    }


    ////////////////////////////////////////

    void print()
    {
        cout<<"\n";
        for (CNode<T>* i = head; i ; i=i->next) {
            cout<< i->value<<" ";
        }
    }

    void print2()
    {
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    }

    void printPairs(){
        std::cout<<"\n";
        for(CNode<T>*i = head ; i ; i=i->next){
            cout<<i->value.first<<","<<i->value.second<<"  ";
        }
    }

    int size(){
        return nelem;
    }



private:
    CNode<T>* head, *tail;
    int nelem;
};


class LRUCache
{
public:
    int capacity;
    CList<pair<int,int>> *list;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        list = new CList<pair<int,int>>;
    }

    int get(int key)
    {
        CNode<pair<int,int>> **p;
        if(list->find(key,p)){
            pair<int,int> x = (*p)->value;
            list->remove(p);
            list->push_front(x);
            return x.second;
        }
        return -1;
    }

    void put(int key, int value)
    {
        CNode<pair<int,int>> **p;
        pair<int,int> x(key,value);

        if(list->find(key,p)){
            list->remove(p);
        }else if( list->size() == capacity){
                list->pop_back();
        }
        list->push_front(x);
    }

    void print(){
        list->printPairs();
    }
};



int main() {

    LRUCache x(3);

    x.put(1,1);
    x.put(2,2);
    x.put(3,3);
    x.put(4,5);

    cout<<"\nget: "<<x.get(3)<<endl;
    cout<<"\nget: "<<x.get(1)<<endl;
    cout<<"\nget: "<<x.get(2)<<endl;

    x.put(5,5);

    cout<<"\nget: "<<x.get(4)<<endl;

    cout<<"\nget: "<<x.get(3)<<endl;

    cout<<"\nsize: "<<x.list->size()<<endl;

    x.print();


}