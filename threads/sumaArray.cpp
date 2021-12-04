//
// Created by misash on 26/11/21.
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

    int nt = thread::hardware_concurrency();

    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                 26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
                 48,49};

    int size_arr = sizeof(arr)/sizeof(arr[0]);

    // adecuacion
    if( size_arr < nt )
        nt = size_arr;

    vector<int> xsum(nt,0);
    int sum = 0;
    int chunk = size_arr / nt , chunk_b = size_arr % nt;
    vector<thread> ths(nt);

    //INFO
    cout<<"\nsize arr: "<<size_arr;
    cout<<"\nthreads: "<<nt;
    cout<<"\nsize chunk: "<<chunk;
    cout<<"\nsize add chunk: "<<chunk_b;


    //paralelismo
    for ( int i = 0, j = 0; i < nt; i++ , j+= (chunk + (chunk_b-- > 0)))
        ths[i] = thread(F1, &arr[j], (chunk + (chunk_b > 0)), &xsum[i]);

    //wait threads
    for ( int i = 0; i < nt; i++ )
        ths[i].join();

    //parte seccuencial
    for ( int i = 0; i < nt; i++ )
        sum += xsum[i];


    cout<<"\n\nSum: "<<sum;


}
