//
// Created by misash on 19/10/21.
//

#include <bits/stdc++.h>

using namespace std;


void real_sort(stack<int> &s,int current){

    if(s.empty() || current > s.top()){
        s.push(current);
        return;
    }

    int top = s.top();
    s.pop();

    real_sort(s,current);

    s.push(top);
}


void sortStack(stack<int> &s){

    if(s.empty()) return;

    int data = s.top();
    s.pop();

    sortStack(s);

    real_sort(s,data);

}



void printStack(stack<int> s){
    cout<<"\n";
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
}



int main(){

    stack<int> stack;

    stack.push(-3);
    stack.push(14);
    stack.push(-5);
    stack.push(30);

    printStack(stack);

    sortStack(stack);

    printStack(stack);


}