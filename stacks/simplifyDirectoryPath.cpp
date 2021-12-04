//
// Created by misash on 8/10/21.
//

#include <iostream>
#include <stack>

// split:
#include <string>
#include <vector>
#include <sstream>

using namespace  std;


template<class T>
struct CNode
{
    CNode(T x)
    {
        value = x;
        next = prev = nullptr;
    }
    T value;
    CNode<T> *next, *prev;
};

template<class T>
class CList
{
public:
    CList()
    {
        head = tail = nullptr;
        nelem = 0;
    }


    void push_back(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        nelem++;
    }

    void pop_back()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode<T>* aux = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    void push_front(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if(!nelem){
            head = tail = n;
        }else{
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem++;
    }

    void pop_front()
    {
        if(head == tail){
            head =  tail = nullptr;
        }else{
            CNode<T>* aux = head;
            head = head->next;
            head->prev = nullptr;
            delete aux;
        }
        nelem -=(nelem)? 1:0;
    }

    int& operator[](int i)
    {
        CNode<T>* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }

    void print()
    {
        cout<<"\n";
        for (CNode<T>* i = head; i ; i=i->next) {
            cout<<i->value<<" ";
        }
    }

    void print2()
    {
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    }

    int size(){
        return nelem;
    }

    T get_tail(){
        return (tail)->value;
    }

    T get_head(){
        return (head)->value;
    }




private:
    CNode<T>* head, *tail;
    int nelem;
};


template<class T, class S>
class CStack
{
public:
    void push(T x)
    {   seq.push_back(x);   }
    void pop()
    {   seq.pop_back();     }

    T top()
    {  return seq.get_tail();   }

    void print(){
        seq.print();
    }

    bool empty(){
        return (seq.size() == 0);
    }

    int size(){
        seq.size();
    }

private:
    S seq;
};


string simplifyPath(string A) {

    string res;
    CStack<char,CList<char>> s;

    s.push('/');

    for ( char c:A) {

        if( c != '/' && c !='.'){
            s.push(c);
        }
        else if( c == '/' && c != s.top()){
            s.push(c);
        }
        else if(c == '.' ){
            if( s.top() == '/'){
                s.pop();
            }else{
                while( s.size() >1 && s.top() !='/') s.pop();
            }
        }
        if( s.empty()) s.push('/');
    }

    if(s.top() == '/' && s.size() > 1) s.pop();


    while (!s.empty()){
        res = s.top() + res;
        s.pop();
    }

    return res;

}


/////////////////////////////////////////////////////////////

void split_str( string const &str, const char delim, vector <string> &out )
{
    //string/vector/sstream
    std::stringstream s(str);
    std::string s2;
    while (std:: getline (s, s2, delim) )
    {
        if(s2 != "") out.push_back(s2); // store the string in s2
    }
}



string simplifyDirectory(string str) {

    vector<string> tokens;
    split_str(str,'/',tokens);

    CStack<string,CList<string>> s;

    for (auto & token : tokens) {
        if(token == ".."){
            if(!s.empty()) s.pop();
        }else {
            if(token != ".") s.push(token);
        }
    }

    if(s.empty()) return "/";

    string path;
    while (!s.empty()){
        path = "/" + s.top() + path;
        s.pop();
    }

    return path;

}




int main(){

    string s = "/a//b////c/d//..//..";
    cout<<simplifyDirectory(s);

}


