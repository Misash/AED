//#include <iostream>
//#include <vector>
//#include <string>
#include <bits/stdc++.h>

using namespace std;

template<class T>
struct CFx1
{
    unsigned long operator()(T x)
    {
        return (unsigned long)(x[0] + x[x.size()-1]);
    }
};


template<class T, class Fx, class Ds, unsigned long Sz>
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    bool Find(T x);
    void Insert(T x);
    void Remove(T x);
    void Print();
    
private:
    Ds* m_ht;
    Fx m_fx;
};

template<class T, class Fx, class Ds, unsigned long Sz>
CHashTable<T,Fx,Ds,Sz>::CHashTable()
{
    m_ht = new Ds[Sz];
}

template<class T, class Fx, class Ds, unsigned long Sz>
CHashTable<T,Fx,Ds,Sz>::~CHashTable()
{
    delete[] m_ht;
}

template<class T, class Fx, class Ds, unsigned long Sz>
bool CHashTable<T,Fx,Ds,Sz>::Find(T x)
{
    Ds v = m_ht[ m_fx(x)%Sz ];
    for(auto k = v.begin() ; k != v.end(); k++)
        if( *k == 40) return 1;

    return 0;
}

template<class T, class Fx, class Ds, unsigned long Sz>
void CHashTable<T,Fx,Ds,Sz>::Insert(T x)
{
    m_ht[ m_fx(x)%Sz ].push_back(x);
}

template<class T, class Fx, class Ds, unsigned long Sz>
void CHashTable<T,Fx,Ds,Sz>::Remove(T x)
{
    Ds v = m_ht[ m_fx(x) % Sz ];
    vector<int>::iterator k;
    for(k = v.begin() ; k != v.end(); k++)
        if( *k == x) break;

    v.erase(k);
}

template<class T, class Fx, class Ds, unsigned long Sz>
void CHashTable<T,Fx,Ds,Sz>::Print()
{
    for ( int i = 0; i < Sz; i++ )
        cout<<"["<<i<<"] "<<m_ht[i].size()<<"\n";

}

int main()
{
    CHashTable<string, CFx1<string>, vector<string>, 19> ht;
    string strs[172] = {"abide", "arise", "awake", "be", "bear", "beat", "become", "beget", "begin", "bend", "bet", "bid", "bite", "bleed", "blow", "break", "bring", "broadcast", "build", "burn", "burst", "buy", "can", "cast", "catch", "chide", "choose", "cling", "clothe", "come", "cost", "creep", "cut", "deal", "dig", "dive", "do", "draw", "dream", "drink", "drive", "dwell", "eat", "fall", "feed", "feel", "fight", "find", "flee", "fling", "fly", "forbid", "forecast", "foresee", "forget", "forgive", "forsake", "freeze", "get", "give", "go", "grind", "grow", "hang", "have", "hear", "hide", "hit", "hold", "hurt", "keep", "kneel", "know", "lay", "lead", "lean", "leap", "learn", "leave", "lend", "let", "lie", "light", "lose", "make", "mean", "meet", "mow", "offset", "overcome", "partake", "pay", "plead", "preset", "prove", "put", "quit", "read", "relay", "rend", "rid", "ring", "rise", "run", "saw", "say", "see", "seek", "sell", "send", "set", "shake", "shed", "shine", "shoe", "shoot", "show", "shut", "sing", "sink", "sit", "slay", "sleep", "slide", "slit", "smell", "sow", "speak", "speed", "spell", "spend", "spill", "spin", "spit", "split", "spoil", "spread", "spring", "stand", "steal", "stick", "sting", "stink", "strew", "strike", "strive", "swear", "sweat", "sweep", "swell", "swim", "swing", "take", "teach", "tear", "tell", "think", "thrive", "throw", "thrust", "typeset", "undergo", "understand", "wake", "wear", "weep", "wet", "win", "wind", "withdraw", "wring", "write"};

    for (int i = 0; i < 172; i++)
        ht.Insert(strs[i]);


    ht.Print();

}





