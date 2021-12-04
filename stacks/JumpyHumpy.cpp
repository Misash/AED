//
// Created by misash on 24/09/21.
//

#include <bits/stdc++.h>

using namespace std;


int main(){

    ios::sync_with_stdio(0);cin.tie(0);

    int n,prev,x,mx,stam;
    stack<int> s;
    cin>>n;

    for (int i = 0; i < n; ++i) {
        cin>>x;
        s.push(x);
    }

    prev = s.top()-1;
    mx = 0;

    while(!s.empty()){

        if(s.top() > prev){
           stam = s.top();
        } else{
            stam ^= s.top();
        }

        mx = (stam > mx)? stam:mx;


        prev = s.top();
        s.pop();

    }

    cout<<mx;

}