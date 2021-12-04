//
// Created by misash on 19/10/21.
//

#include <iostream>
#include <queue>

using namespace std;



void reverse(queue<int>&q){
    if(q.empty()) return;

    int data = q.front();
    q.pop();

    reverse(q);

    q.push(data);
}

queue<int> reverseQueue(queue<int> q)
{
    reverse(q);
    return q;
}



int main(){
    queue<int> x;
    queue<int> y;

    x.push(1);
    x.push(2);
    x.push(3);
    x.push(4);

    y = reverseQueue(x);

    while(!y.empty()){
        cout<<y.front()<<" ";
        y.pop();
    }

}