//
// Created by misash on 5/10/21.
//


//Following is the class structure of the Node class:

#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};



class Stack
{
    Node * head;
    int size;
public:
    Stack()
    {
        head = 0;
        size = 0;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void push(int data)
    {
        Node * t = new Node(data);
        t->next = head;
        head = t;
        size++;
    }

    void pop()
    {
        if(size){
            Node *t = head;
            t = head;
            head = head->next;
            delete t;
            size --;
        }
    }

    int getTop()
    {
        return (isEmpty())? -1:head->data;
    }

    void print(){
        cout<<endl;
        for (Node *i = head; i  ; i = i->next) {
            cout<<i->data<<" ";
        }
    }

};

int main(){

    Stack s;

    s.push(55);
    s.push(22);
    s.push(33);

    s.pop();

    cout<<"\nsize: "<<s.getSize()<<" top: "<<s.getTop();

    s.print();


}