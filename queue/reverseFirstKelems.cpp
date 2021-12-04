//
// Created by misash on 19/10/21.
//

#include <bits/stdc++.h>

using namespace std;



queue<int> reverseElements(queue<int> q, int k)
{
    stack<int> s;
    while (k--){
        s.push(q.front());
        q.pop();
    }

    queue<int> x;

    while(!s.empty()){
        x.push(s.top());
        s.pop();
    }

    while(!q.empty()){
        x.push(q.front());
        q.pop();
    }

    return x;
}


void print(queue<int> x){
    cout<<endl;
    while(!x.empty()){
        cout<<x.front()<<" ";
        x.pop();
    }
}



int main(){

    queue<int> q ,x;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    x = reverseElements(q,2);

    print(x);

}