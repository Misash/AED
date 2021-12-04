//
// Created by misash on 18/10/21.
//

#include <stdio.h>
#include <iostream>

int main(void) {


    int n , i=0 , mul =0;
    bool continuar= true;

    cin>>n;

    while(continuar || i == 9 || mul < n){
        mul = n * i++;
        cout<<"\n "<<n<<" * "<<i<<" = "<<mul;
        if(m == 10){
            cout<<"\nquieres continuar? ";
            cin>>continuar;
        }
    }


    return 0;




}