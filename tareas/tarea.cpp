
#include <iostream>
#include <math.h>
#include <string>


using namespace  std;


template<class T>
struct CNode
{
    CNode(int x)
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

    CNode<T>* head, *tail;
    int nelem;

    CList()
    {
        head = tail = nullptr;
        nelem = 0;
    }
    ~CList()
    {}

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


};


template<class T, class S>
class CStack
{
public:
    void push(T x)
    {   seq.push_back(x);   }
    void pop()
    {   seq.pop_back();     }

    T top(){
        return (seq.tail)->value;
    }

    bool empty(){
        return (seq.nelem == 0);
    }

private:
    S seq;
};






void removeSpaces(string &str)
{
    string n_str;
    for (char i:str)
        if (i != ' ') n_str+=i;
    str = n_str;
}

bool isOperator(char x){
    return x == '(' || x == ')' || x == '*' || x == '/' || x == '+' || x == '-' || x == '^';
}


int precedence(char x) {
    if( x == '^' ) return 3;
    if( x == '*' || x == '/') return 2;
    if( x == '+' || x == '-') return 1;
    return -1;
}



string infixToPostfix(string s) {

    CStack<char, CList<char>> st; //For stack operations, we are using C++ built in stack
    string posfix;

    for(char i : s) {

        if(!isOperator(i))
            posfix += i;

        else if(i == '(')
            st.push('(');

        else if(i == ')') {
            while(st.top() != '(')
            {
                posfix += st.top();
                st.pop();
            }
            st.pop();
        }

        else {
            while(!st.empty() && precedence(i) <= precedence(st.top())) {
                posfix += st.top();
                st.pop();
            }
            st.push(i);
        }
    }

    while(!st.empty()) {
        posfix += st.top();
        st.pop();
    }

    return posfix;
}


int calcPosfix(string posfix){

    int result,a,b;
    CStack<int,CList<int>> s;

    for( char simbol:posfix){

        if(isOperator(simbol)){

            a = s.top(); s.pop();
            b = s.top(); s.pop();

            switch (simbol) {
                case '*' : result =  b * a; break;
                case '/' : result =  b / a; break;
                case '^' : result =  pow(b,a); break;
                case '+' : result =  b + a; break;
                case '-' : result =  b - a; break;
            }

            s.push(result);

        }else{
            s.push(simbol - '0');
        }

    }

    return result;
}




int main() {



    string str = "(5+3) * (7-4) + 4^2^1 + 4/2";
    removeSpaces(str);

    cout<<"\nInfix: "<<str;

    string posfix = infixToPostfix(str);

    cout<<"\nPostFix: "<<posfix;

    int rpta = calcPosfix(posfix);
    cout<<"\nResult: "<<rpta;


}





