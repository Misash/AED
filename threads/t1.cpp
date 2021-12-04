//
// Created by misash on 25/11/21.
//

#include <thread>
#include <iostream>

using namespace std;

void f1(char c,int n){
    for (int i = 0; i < n; ++i) {
        cout<<c;
    }
}

int main(){

    thread t(f1,'c',5);

    t.join(); //wait thread

}