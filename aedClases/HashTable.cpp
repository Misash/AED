#include <iostream>
#include <list>

using namespace std;

struct CFd1
{
    inline unsigned long operator()(int x)
    {
        return x+1;
    }
};


template<class T>
struct CListAdaptor{

    std::list<T> l;

    bool Find(T v){
        typename std::list<T>::iterator i;
        for ( i = l.begin() ; i != l.end() ; ++i)
            if( *i == v) return 1;
        return 0;
    }

    void Insert(T v){
        l.push_back(v);
    }

    void Remove(T v){
        l.remove(v);
    }
};



template<class T, class S, class Fd, unsigned long Sz>
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    bool find(T v);
    bool ins(T v);
    bool rem(T v);

    S* table;
    Fd fd;
};

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::CHashTable()
{
    table = new S[Sz];
}

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::~CHashTable()
{
    delete[] table;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::find(T v)
{
    S& l =  table[ fd(v) % Sz ];
    typename S::iterator i;

    for (i = l.begin(); i != l.end() ; ++i)
        if( *i == v) return 1;

    return 0;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::ins(T v)
{
    table[ fd(v)%Sz ].Insert(v);
    return 1;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::rem(T v)
{
    table[ fd(v)%Sz ].Remove(v);
    return 0;
}




int main()
{
    CHashTable<int, CListAdaptor<int>, CFd1, 7> ht;
    ht.ins(11);
    ht.ins(8);
    ht.ins(4);
    ht.ins(9);
    ht.rem(8);


}
