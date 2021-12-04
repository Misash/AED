//
// Created by misash on 19/10/21.
//


#include <bits/stdc++.h>

using namespace  std;


void deleteMiddle(stack<int>&inputStack, int N){

    int M = N/2 - !(N%2);


    stack<int> temp;

//    for (int i = 0; i <= M; ++i) {
//        if(i != M) temp.push(inputStack.top());
//        inputStack.pop();
//    }


    for (int i = N-1 ; i >= M; --i) {
        if(i != M) temp.push(inputStack.top());
        inputStack.pop();
    }


    while(!temp.empty()){
        inputStack.push(temp.top());
        temp.pop();
    }

}


void printStack(stack<int> s){
    cout<<"\n";
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
}


int main(){

    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    printStack(s);

    deleteMiddle(s,5);

    printStack(s);


}