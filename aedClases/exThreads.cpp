//
// Created by misash on 8/11/21.
//

#include<iostream>
#include <thread>



using namespace  std;

void F1(char c, int n){
    for (int i = 0; i < n; ++i) {
        cout<<c;
    }
}


int main(){
    thread t(F1,'c',5);

    t.join();


}