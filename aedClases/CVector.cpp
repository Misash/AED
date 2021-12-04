#include <iostream>

using namespace std;

template <typename T>
class Cvector{
public:

    Cvector(T size){
        m_size = size;
        m_v=new T[m_size];
        m_nelem=0;//size
    }

    ~Cvector(){
        delete[] m_v;
    }

    int size(){
        return m_nelem;
    }

    void expand(){
        T* p=new T[2*m_size];
        for( int i = 0; i < m_size ; i ++){
            p[i]=m_v[i];
        }
        delete[] m_v;
        m_v=p;
        m_size= 2*m_size;
    }

    void collapse(){
        m_size/=2;
        T* p = new T[m_size];
        for(int i = 0; i < m_size ; i++)
            p[i]=m_v[i];
        delete[] m_v;
        m_v = p;
    }

    void push_back(int x){
        if(m_nelem == m_size)
            expand();
        m_v[m_nelem]=x;
        m_nelem++;
    }

    void pop_back(){
        if(m_nelem < m_size/2)
            collapse();
        m_nelem--;
    }

    void push_front(int x){
        if(m_nelem == m_size)
            expand();
        for(int i = m_nelem-1; i>=0; i--){
            m_v[i+1]=m_v[i];
        }
        m_v[0] = x;
        m_nelem++;
    }

    void print(){
        cout<<"\n";
        for (int i = 0; i <m_nelem; ++i)
            cout<<m_v[i]<<" ";
    }

    void pop_front(){
        if(m_nelem < m_size/2)
            collapse();
        for (int i = 0; i <m_nelem-1 ; ++i)
            m_v[i]=m_v[i+1];
        m_nelem--;
    }

    int&  operator[](int i){
        return m_v[i];
    }

private:
    T* m_v;
    int m_size;
    int m_nelem;

};



int main() {


    Cvector<int> v(3);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_front(0);
    v.push_front(1);
    v.push_front(2);
    v.pop_front();


    v.print();
    cout<<"\n-> "<<v.size();

    return 0;
}



