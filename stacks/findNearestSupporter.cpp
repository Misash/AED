//
// Created by misash on 20/10/21.
//

#include <bits/stdc++.h>

using namespace  std;



void findSupport(stack<int> &s,int x, int &v){
    if(s.empty()){
        v=-1; return;
    }
    if(s.top() < x ){
        v = s.top();return;
    }

    int data = s.top();
    s.pop();
    findSupport(s,x,v);
    s.push(data);

}


vector<int> prevSmall(vector<int> arr, int n) {

    stack<int> s;
    vector<int> ans;
    int val;

    for (int i = 0; i < n; ++i) {
        findSupport(s,arr[i],val);
        s.push(arr[i]);
        ans.push_back(val);
    }
    return ans;
}


void printVector(vector<int> vec){
    for( auto & i: vec){
        cout<<i<<" ";
    }
}



int main(){

    vector<int> v = {9 ,8, 1, 2 ,5 ,5};



    printVector(prevSmall(v,v.size()));



}