//
// Created by misash on 7/10/21.
//

#include <bits/stdc++.h>
using namespace std;


class TwoStack {

public:

    // Initialize TwoStack.
    int size,s1,s2;
    int *arr;


    TwoStack(int s) {
        arr = new int[s];
        size = s;
        s1 = s2 = 0;
    }

    // Push in stack 1.
    void push1(int num) {
       if(s1+s2 < size) arr[s1++] = num;
    }

    // Push in stack 2.
    void push2(int num) {
        if(s1+s2 < size) arr[size - 1 -s2++] = num;
    }

    // Pop from stack 1 and return popped element.
    int pop1() {
        return (!s1)? -1: arr[--s1];
    }

    // Pop from stack 2 and return popped element.
    int pop2() {
        return (!s2)? -1: arr[size - 1 - (--s2)];
    }

    void print(){
        cout<<endl;
        for (int i = 0; i <size ; ++i) {
            cout<<arr[i]<<" ";
        }
    }

};


int main(){

    TwoStack s(3);


    s.push1(3);
    s.push2(4);
    s.push1(5);


    cout<<"\npop: "<<s.pop1();
    cout<<"\npop: "<<s.pop2();


    cout<<"\ns1: "<<s.s1<<" s2: "<<s.s2;

    s.print();



}