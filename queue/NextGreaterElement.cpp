//
// Created by misash on 19/10/21.
//

#include <bits/stdc++.h>

using namespace std;


vector<int> nextGreaterElement(vector<int>& arr, int n){

    vector<int> v;
    for (int i = 0; i < n; ++i) {
        int max = -1;
        for (int j = i+1; j < n ; ++j) {
            if( arr[j] > arr[i] ){
                max = arr[j];
                break;
            }
        }
        v.push_back(max);
    }

    return v;
}


int main(){

    vector<int> x;

    vector<int> z = { 6,4,7,1,7,1,3,9,8};
    int n = z.size();
    x = nextGreaterElement(z,n);

    for (int i = 0; i < n;  ++i) {
        cout<<x[i]<<" ";
    }


}