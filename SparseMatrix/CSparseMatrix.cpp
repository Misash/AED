//
// Created by misash on 8/12/21.
//

#include <iostream>
#include <vector>
#include <list>
using namespace std;


template<class T>
struct smxNode{
    typedef unsigned int uint;
    smxNode(uint x, uint y, T val) : x(x) , y(y) , value(val) {}
    uint x,y;
    T value;
};


template <class T, T NE>
class CSparseMatrix
{
    typedef unsigned int uint;
    typedef T value_type;
    typedef smxNode<T> Node;
    typedef typename list<Node*>::iterator listIter;
public:
    CSparseMatrix(uint xdim, uint ydim);
    void Set(uint x, uint y, T value);
    T    Get(uint x, uint y);
    void Print();

private:
    vector< list<Node*> > matrix;
    uint m_XDim, m_YDim;

    bool Find(unsigned int x, unsigned int y, listIter &it);
};

template <class T, T NE>
CSparseMatrix<T,NE>::CSparseMatrix(uint xdim, uint ydim)
{
    m_XDim = xdim; m_YDim = ydim;
    matrix.resize(m_XDim);
}


template <class T, T NE>
bool CSparseMatrix<T,NE>::Find(uint x , uint y ,listIter &it){

    for (; it != matrix[x].end() ; it++)
        if((*it)->y == y ) return 1;
    return 0;
}


template <class T, T NE>
void CSparseMatrix<T,NE>::Set(uint x, uint y, T value)
{

   listIter it = matrix[x].begin();
   if(Find(x,y,it)){
       if(value != NE){
           //update
           (*it)->value = value;
       }else{
           //rem valor 0
           matrix[x].erase(it);
       }
   }else{
       //insertar nulo
       if(value == NE) return;
       //ins de verdad
       Node *n = new Node(x,y,value);
       matrix[x].push_back(n);
   }

}


template <class T, T NE>
typename CSparseMatrix<T,NE>::value_type CSparseMatrix<T,NE>::Get(uint x, uint y)
{
    listIter it = matrix[x].begin();
    if(!Find(x,y,it)) return NE;
    return (*it)->value;
}

template <class T, T NE>
void CSparseMatrix<T,NE>::Print()
{
    int xi, yi;
    for (yi = 0; yi < m_YDim; yi++)
    {
        for (xi = 0; xi < m_XDim; xi++)
        {
            T value = Get(xi,yi);
            cout<< value<<"\t";
        }
        cout<<endl;
    }
    cout<<"---"<<endl;
}


int main(int argc, const char * argv[])
{
    CSparseMatrix<int,-1> m(5,5);

    m.Set(0,0,2);   m.Set(2,0,-1);   m.Set(3,1,5);
    m.Set(1,2,6);   m.Set(2,2,7);   m.Set(3,2,-1);
    m.Set(4,2,9);   m.Set(1,3,1);   m.Set(0,4,-1);
    m.Set(3,4,8);
    m.Print();
    m.Set(3,1,-1);   m.Set(1,2,-1);   m.Set(0,4,-1);
    m.Set(4,4,-1);
    m.Print();

//    m.Set(0,1,5);
//    m.Set(0,1,0);
//    m.Set(0,1,-1);
//    m.Print();


    return 0;
}