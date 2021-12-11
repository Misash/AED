//
// Created by misash on 9/12/21.
//

#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;


void merges( int* arr , int * lb, int  *mid, int * ub)
{
    int n = ub - lb + 1;
    int *temp_arr = new int[n];
    int* i = lb;
    int* j = mid + 1;
    int* k = temp_arr;

    while( i <= mid && j <= ub ){
        if( *i <= *j){
            *k = *i;
            i++;
        }else{
            *k = *j;
            j++;
        }
        k++;
    }

    if( i > mid){
        while( j <= ub){
            *k = *j;
            k++; j++;
        }
    }else if( j > ub){
        while( i <= mid){
            *k = *i;
            k++; i++;
        }
    }

    for (int l = lb-arr; l < n; ++l)arr[l] = temp_arr[l];
}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int* arr, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void print(int *arr , int n){
    cout<<endl;
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
}

int main(){

    int arr[] = { 1,8,3,100,5,0,88,89,15,63,58,2,69,41,25,100};
    auto arr_size = sizeof(arr) / sizeof(arr[0]);

    int nt = 4;
    int chunk = arr_size / 4;
    vector<thread> ths(nt);

    cout<<"\nantes de ordenar:";
    print(arr,arr_size);

    //paralelismo
    for ( int i = 0, j = 0; i < nt; i++ , j+= chunk){
//        cout<<"\n"<<i<<" "<<j<<" "<<chunk;
        ths[i] = thread(bubbleSort, &arr[j], chunk);
    }

    //wait threads
    for ( int i = 0; i < nt; i++ )
        ths[i].join();

    cout<<"\n1er sort paralelo :";
    print(arr,arr_size);

    //merge parallel
    vector<thread> th(2);
    for ( int i = 0; i < 2;i++)
        th[i] = thread(merges, arr,&arr[i*8],&arr[i*8+3],&arr[i*8+7]);

    //wait threads merge
    for ( int i = 0; i < 2; i++ )
        th[i].join();

    cout<<"\nmerge parallel :";
    print(arr,arr_size);

    //secuencial
    merges(arr,&arr[0],&arr[7],&arr[15]);

    cout<<"\nfinal secuencial merge:";
    print(arr,arr_size);


}