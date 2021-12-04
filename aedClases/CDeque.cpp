

#include <iostream>
using namespace std;



template<class T>
struct chunk
{
    T *head,*tail,*init;
    int capacity,start,size=0;

    chunk(int capacity , int start){
        this->capacity = capacity;
        this->start = start;

        head = new T[capacity];
        tail = head + capacity - 1;
        init = head + start;
    }

    void push_back(T x){
        *(init + size++) = x;
    }
    void pop_back(){
        size--;
    }
    void push_front(T x){
        init -= (size++ > 0);
        *init = x;
    }
    void pop_front(){
        init += (size-- > 1);
    }
    void print(){
        for (int *i = init; i < init + size; ++i) {
            cout<<*i<<" ";
        }
    }
};


template<class O>
class CDeque{

public:
    chunk<chunk<O>*> *map;

    int capacity;
    int size_chunk=5;


    CDeque(int capacity){
        this->capacity = capacity;
        //crea el mapa
        map = new chunk<chunk<O>*>(capacity,capacity/2);
        createChunk( *(map->init), size_chunk/2);
    }

    void createChunk(chunk<O>* &block,int pos){
        block = new chunk<O>(size_chunk,pos);
        map->size ++;
    }

    void collapse(){
        if( map->size < capacity/2){
            capacity /= 2;
            chunk<chunk<O>*> *temp =  new chunk<chunk<O>*>(capacity,capacity/2);
            for (chunk<O> **i = map->init , **j = temp->init ;  i < map->init + size() ; ++i , ++j){
                *j = *i;
                temp->size ++;
            }
            delete [] map;
            map = temp;
        }
    }

    void expand(){
        capacity *= 2;
        chunk<chunk<O>*> *temp =  new chunk<chunk<int>*>(capacity,capacity/2);

        for (chunk<O> **i = map->init , **j = temp->init ;  i < map->init + size() ; ++i , ++j){
            *j = *i; temp->size ++;
        }
        delete [] map;
        map = temp;
    }

    void push_back(O x)
    {
        //accedemos al last del map

        chunk<O> * last_chunk = *(map->init + map->size - 1);
//            chunk<int> * last_chunk = *(map->init);

        //verificar que se puede push en el chunk
       if( (last_chunk ->init + last_chunk->size ) <= last_chunk->tail){

           last_chunk->push_back(x);

       } else if ( (map->init + map->size - 1 ) == map->tail){
           // verificar si esta en el  ultimo map y el ultimo chunk

           expand();
           this->push_back(x);

       }else{
           // si no esta en el ultimo  pero se necesita otro chunk
           createChunk(*(map->init + map->size),0);
           last_chunk = *(map->init + map->size -1);
           last_chunk->push_back(x);
       }

    }

    void push_front(O x){

        chunk<O> * firts_chunk = *(map->init);

        //verificar que se puede push en el chunk
        if(firts_chunk->init > firts_chunk->head){

            firts_chunk->push_front(x);

        } else if ( map->init == map->head){
            // verificar si esta en el  ultimo map y el ultimo chunk

            expand();
            // un push back
            this->push_front(x);

        }else{
            // si no esta en el ultimo  pero se necesita otro chunk
            map->init --;
            createChunk(*(map->init ),size_chunk-1);
            firts_chunk = *(map->init);
            firts_chunk->push_front(x);
        }

    }

    void pop_back(){

        collapse();

        chunk<O> * last_chunk = *(map->init + map->size - 1);

        if(last_chunk->size){

            if(last_chunk->size == 1){
                last_chunk->pop_back();
                map->size -= (size()>1);
            }else{
                last_chunk->pop_back();
            }
        }
    }

    void pop_front(){

        collapse();

        chunk<O> * first_chunk = *(map->init);

        if(first_chunk->size ){
            if (first_chunk->size == 1){
                //eliminar chunk si es el ultimo
                first_chunk->pop_front();
                map->init += (size()>1);
                map->size -= (size()>1);
            }else{
                first_chunk->pop_front();
            }
        }

    }

    int operator[](int i){

        chunk<O> * current_chunk = *(map->init);
        int recorrido_i = i + size_chunk - current_chunk->size;
        int chunk = ( recorrido_i )/size_chunk;
        current_chunk = *(map->init + chunk);
        int * p = current_chunk->head + (recorrido_i % size_chunk);
        return *p;

    }

    void print(){
        cout<<endl;
        for (chunk<O> **i = map->init; i< map->init + map->size; ++i) {
            (*i)->print();cout<<" ";
        }
    }

    void print2(){
        for (chunk<O> **i = map->head;  i <= map->tail ; ++i) {
            cout<<*i<<" ";
        }
    }

    int size(){
        return map->size;
    }

};


int main() {


    CDeque<int> d(5);


    d.push_back(1);
    d.push_back(2);
    d.push_back(3);

    d.push_back(4);
    d.push_back(5);
    d.push_back(6);
    d.push_back(7);
    d.push_back(8);
    d.push_back(9);
    d.push_back(10);
    d.push_back(11);


    cout << "\nsize: " << d.map->size << " capacity: " << d.map->capacity << endl;

    d.print();

    cout<<"\n"<<d[1];



}

