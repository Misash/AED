//
// Created by misash on 27/11/21.
//


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

void F1(int* ar, int n, int* s)
{
    for ( int i = 0; i < n; i++ )
    {
        *s += ar[i];
    }
}



int main(){

    int arr[10][10];
    int k=1;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j <10 ; ++j) {
            arr[i][j] = k++;
        }
    }








}






