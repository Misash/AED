//
// Created by misash on 24/09/21.
//

#include<bits/stdc++.h>
//#include <stack>

using namespace std;

int main(){

    ios::sync_with_stdio(0);cin.tie(0);

    int n,x;
    stack<int> A;
    stack<int> B;

    cin>>n;
    int arr[n];

    for (int i=0 ; i<n ; ++i) cin>>arr[i];
    for (int i : arr) B.push(i);
    for (int i=n-1 ; i >=0 ; --i) A.push(arr[i]);

    while(!A.empty() && !B.empty()){

        if(A.top() > B.top()){
            cout<<1<<" ";
            B.pop();
        }
        else if(A.top() < B.top()){
            cout<<2<<" ";
            A.pop();
        }else{
            cout<<0<<" ";
            A.pop(); B.pop();
        }

    }

}