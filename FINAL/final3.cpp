//
// Created by misash on 11/12/21.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>


using namespace std;
mutex mu;

void PrintMatrix(int (*pm)[7], int y, int x)
{
    for ( int j = 0; j < y; j++ )
    {
        for ( int i = 0; i < x; i++ )
            std::cout<<pm[j][i]<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void PrintVector(int *v, int s)
{
    for ( int i = 0; i < s; i ++ )
        std::cout<<v[i]<<" ";
    std::cout<<"\n\n";
}

int s[10] = {0};

void F1(int* ar, int n)
{
    mu.lock();
    for ( int i = 0; i < n; i++ )
    {

        if(ar[i] >= 0 &&  ar[i] <= 99) s[0] += ar[i];
        if(ar[i] >= 100 &&  ar[i] <= 199) s[1] += ar[i];
        if(ar[i] >= 200 &&  ar[i] <= 299) s[2] += ar[i];
        if(ar[i] >= 300 &&  ar[i] <= 399) s[3] += ar[i];
        if(ar[i] >= 400 &&  ar[i] <= 499) s[4] += ar[i];
        if(ar[i] >= 500 &&  ar[i] <= 599) s[5] += ar[i];
        if(ar[i] >= 600 &&  ar[i] <= 699) s[6] += ar[i];
        if(ar[i] >= 700 &&  ar[i] <= 799) s[7] += ar[i];
        if(ar[i] >= 800 &&  ar[i] <= 899) s[8] += ar[i];
        if(ar[i] >= 900 &&  ar[i] <= 999) s[9] += ar[i];

    }
    mu.unlock();
}


int main()
{
    int m[10][7]
            {
                    {142,950,227,771,907,827,159},
                    {932,51,99,117,306,909,885},
                    {471,208,985,202,42,85,364},
                    {248,860,82,154,236,429,756},
                    {120,989,344,638,77,522,911},
                    {985,842,170,491,904,736,854},
                    {114,431,657,864,604,580,766},
                    {120,352,321,668,917,88,898},
                    {768,190,955,757,422,915,658},
                    {5,622,355,675,150,557,126}
            };
    int sum[10] = {0};
    PrintMatrix(m, 10, 7);
//**************************************************


    int m_flatten[70];
    int count=0;
    for (int i = 0; i <10; ++i) {
        for (int j = 0; j <7 ; ++j) {
            m_flatten[count++] = m[i][j];
        }
    }

//    int nt = thread::hardware_concurrency();
    int nt = 4;
    int size_arr = sizeof(m_flatten)/sizeof(m_flatten[0]);

    // adecuacion
    if( size_arr < nt )
        nt = size_arr;

    int chunk = size_arr / nt , chunk_b = size_arr % nt;
    vector<thread> ths(nt);

    //paralelismo
    for (int i = 0, j = 0; i < nt; i++, j += (chunk + (chunk_b-- > 0)))
        ths[i] = thread(F1, &m_flatten[j], (chunk + (chunk_b > 0)));

    //wait threads
    for ( int i = 0; i < nt; i++ )
        ths[i].join();


    for (int i = 0; i < 10; ++i) {
        sum[i] =s[i];
    }

    int ss=0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 7 ; ++j) {
            if(m[i][j] >=500 && m[i][j] <=599 ) ss+=m[i][j];

        }
    }
    cout<<"\nsum: "<<ss;
    cout<<endl;


//**************************************************
    PrintVector(sum, 10);
}
