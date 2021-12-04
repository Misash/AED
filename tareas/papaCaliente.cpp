//
// Created by misash on 7/10/21.
//


#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace  std;


template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = nullptr;
    }
    T value;
    CNode<T> *next, *prev;
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

    void print()
    {
        cout<<"\n";
        for (CNode<T>* i = head; i ; i=i->next) {
            cout<<i->value<<" ";
        }
    }

    void print2()
    {
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    }

    int size(){
        return nelem;
    }

    T get_tail(){
        return (tail)->value;
    }

    T get_head(){
        return (head)->value;
    }




private:
    CNode<T>* head, *tail;
    int nelem;
};


template<class T, class S>
class CQueue
{
public:
    void push(T x){
        seq.push_back(x);
    }
    T pop(){
        T f = front();
        seq.pop_front();
        return f;
    }

    T front(){
        return seq.get_head();
    }
    bool empty(){
        return (seq.size() == 0);
    }
    void print(){
        if (empty())  cout<<"\nNull"; seq.print();
    }

private:
    S seq;
};


void Simulate_Lista_Circular( CQueue<char,CList<char>> &queue){
    queue.print();
    srand (time(NULL));

    while(!queue.empty()){
        int n = rand() % 20 + 1;
        cout<<"\nn : "<<n;
        for (int i = 0; i < n; ++i) {
            int front = queue.pop();
            queue.push(front);
        }
        cout<<"\tsale : "<<queue.pop()<<"\n";

        queue.print();
    }
}


int main(){

    CQueue<char,CList<char>> queue;

    //PLAYERS
    queue.push('A');
    queue.push('B');
    queue.push('C');
    queue.push('D');
    queue.push('E');
    queue.push('F');
    queue.push('G');
    queue.push('H');
    queue.push('I');
    queue.push('J');

    Simulate_Lista_Circular(queue);

}
