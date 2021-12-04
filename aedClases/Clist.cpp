#include <iostream>

using namespace std;

struct CNode
{
    CNode(int x)
    {
        value = x;
        next = prev = nullptr;
    }
    int value;
    CNode *next, *prev;
};


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
        
    void push_back(int x)
    {
        CNode* n = new CNode(x);
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
            CNode* aux = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }
    
    void push_front(int x)
    {
        CNode* n = new CNode(x);
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
            CNode* aux = head;
            head = head->next;
            head->prev = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }
    
    int& operator[](int i)
    {
        CNode* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }
    
    void print()
    {
        cout<<"\n";
        for (CNode* i = head; i ; i=i->next) {
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
    
private:
    CNode* head, *tail;
    int nelem;
};

void Pruebas(){

    CNode* n = new CNode(5);
    CNode* h = n;
    CNode* t = n;
    CNode* aux = t;

    cout<<"\nt: "<<t;
    cout<<"\nh: "<<h;
    cout<<"\naux: "<<aux;



    t=t->prev;
    delete aux;

    cout<<"\nt: "<<t;
    cout<<"\nh: "<<h;
    cout<<"\naux: "<<aux;



}


int main()
{
    CList l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.pop_front();


//    l.pop_back();
//    l.pop_back();
//    l.pop_back();




    l.print2();
    cout<<"\n-> "<<l.size();



    
//    std::cout<<"\nelem 4:"<<l[4]<<"\n";
}
