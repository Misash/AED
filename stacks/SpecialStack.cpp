//
// Created by misash on 6/10/21.
//

#include <iostream>
#include <stack>

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



class SpecialStack {

    Node * head;
    int size;
    stack<int> min;
    /*----------------- Public Functions of SpecialStack -----------------*/
public:

    SpecialStack(){
        head = 0;
        size = 0;
    }

    void push(int data) {
        int m = (!head)? data:(data<min.top())? data:min.top();
        min.push(m);

        Node * t = new Node(data);
        t->next = head;
        head = t;
        size++;
    }

    int pop() {
        if(size){
            min.pop();
            Node *t = head;
            int val = t->data;
            t = head;
            head = head->next;
            delete t;
            size --;
            return  val;
        }
        return -1;
    }

    int top() {
        return (isEmpty())? -1:head->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getMin() {
        return (size)? min.top():-1;
    }

    void print(){
        cout<<endl;
        for (Node *i = head; i  ; i = i->next) {
            cout<<i->data<<" ";
        }
    }

};


int main(){

    SpecialStack s;

    s.push(5);
    s.push(4);
    s.push(10);
    s.push(10);
    s.push(-358);

    s.pop();
    s.pop();
    s.pop();
    s.pop();

    cout<<"\nempty: "<<s.isEmpty()<<" min: "<<s.getMin();

    s.print();



}

