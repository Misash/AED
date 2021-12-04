//
// Created by misash on 26/10/21.
//

#include <iostream>

using namespace  std;
#define op(a,b) a<b


template<class T>
struct Cless{
    inline bool operator()(T a ,T b){
        return a < b;
    }
};



template<class T>
struct Cgreater{
    inline bool operator()(T a ,T b){
        return a > b;
    }
};



//inline : sugerencia a tratar como macros
//define : macros , extension de codigo


int main(){

//    Cless<int> op;
    Cgreater<int> op;
    int a = 3, b = 5;

    if(op(a,b))
        cout<<a;
    else cout<<b;


}