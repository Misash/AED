//
// Created by misash on 30/09/21.
//

#include <iostream>
#include <string>
#include <math.h>

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

    T tail_value(){
        return (tail)->value;
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
    {  return seq.tail_value();   }

    void print(){
        seq.print();
    }

    bool empty(){
        return (seq.size() == 0);
    }

private:
    S seq;
};




struct Program{

    string infix,postfix;

    Program(string infix){
        this->infix = infix;
        removeSpaces();
    }

    void removeSpaces()
    {
        string txt;
        for (char i:infix) if (i != ' ')txt+=i;
        infix = txt;
    }

    bool isOperator(char x){
        return x == '(' || x == ')' || x == '*' || x == '/' || x == '+' || x == '-' || x == '^';
    }

    int precedence(char x){
        if( x == '(' || x == ')') return 3;
        if( x == '^' ) return 2;
        if( x == '*' || x == '/') return 1;
        if( x == '+' || x == '-') return 0;
        return 0;
    }


    void Rules(CStack<char,CList<char>> &stack , char simbol){
        if( stack.empty()  || stack.top() == '(')
        {
            stack.push(simbol);
        }else
        {
            if(precedence(simbol) > precedence(stack.top()) ){
                stack.push(simbol);

            }else if(precedence(simbol) < precedence(stack.top())){
                postfix += stack.top() ;
                stack.pop();
                Rules(stack , simbol);
            }else{
                // Right ->Left
                if(simbol == '^' ){
                    stack.push(simbol);
                }else{ //left -> Right
                    postfix += stack.top() ;
                    stack.pop();
                    Rules(stack , simbol);
                }
            }
        }

    }

    void infix_to_posfix(){

        CStack<char,CList<char>> stack;

        for ( char simbol:infix) {

            if(isOperator(simbol))
            {
                if(simbol == ')'){
                    while(stack.top() != '('){
                        postfix += stack.top() ;
                        stack.pop();
                    }
                    stack.pop();
                }else{
                    Rules(stack , simbol);
                }
            }else{
                postfix +=  simbol;
            }

        }
        while( !stack.empty()){
            postfix +=stack.top();
            stack.pop();
        }

    }

    double operation(double *values, char op){
        switch (op) {
            case '+' : return *(values+1) + *(values) ;
            case '-' : return *(values+1) - *(values) ;
            case '*' : return *(values+1) * *(values) ;
            case '/' : return *(values+1) / *(values) ;
            case '^' : return  pow(*(values+1) , *(values)) ;
        }
        return 0;
    }

    double calculateOperations(){

        double result;

        CStack<double,CList<double>> stack;
        double values[2];

        for( char simbol:postfix){
            if(isOperator(simbol)){
                for (int i = 0; i < 2; ++i){
                    values[i] = stack.top();
                    stack.pop();
                }
                result = operation(values,simbol);
                stack.push(result);

            }else{
                string s(1,simbol);
                stack.push(stod(s));
            }
        }
        return result;
    }

};




int main(){


    /**
     * El Programa convierte notacion
     * infix -> postfix
     * para finalmente calcular sus operaciones binarias
     *
     */


    string expr = "(  4 ^ 2 ^ 1 / ( 2 * 2 + (1) ) ) + 4^(1/2) ";

    Program x(expr);

    cout<<"\nInfix: "<<x.infix;
    x.infix_to_posfix();
    cout<<"\nPostFix: "<<x.postfix;
    cout<<"\nResult: "<<x.calculateOperations();


}












