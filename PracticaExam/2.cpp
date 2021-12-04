//
// Created by misash on 22/10/21.
//

#include <iostream>
#include <vector>

using namespace std;

template<class T>
class BSTNode {
public:
    BSTNode() {
        left = right = 0;
    }
    BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) {
        el = e; left = l; right = r;
    }
    T el;
    BSTNode<T> *left, *right;
};


template<class T>
class BST {
public:
    BST() {
        root = 0;
    }
//    ~BST() {
//        clear();
//    }
    void clear() {
        clear(root); root = 0;
    }

    void clear(BSTNode<T> *p) {
        if(p)
        {
            clear(p->left);
            clear(p->right);
            delete p;
        }

    }


    bool isEmpty() const {
        return root == 0;
    }
    void preorder() {
        preorder(root);
    }
    void inorder() {
        inorder(root);
    }
    void postorder() {
        postorder(root);
    }

    void insert(const T&);

    void toLEC();
    void PrintLEC();

protected:
    BSTNode<T>* root;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void inorderTrack(BSTNode<T>* , vector< BSTNode<T>* > &);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* p) {
        cout << p->el << ' ';
    }

};

template<class T>
void BST<T>::inorder(BSTNode<T> *p) {
    if (p != 0) {
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}


template<class T>
void BST<T>::preorder(BSTNode<T> *p) {
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}
template<class T>
void BST<T>::postorder(BSTNode<T>* p) {
    if (p != 0) {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<class T>
void BST<T>::insert(const T& el) {
    BSTNode<T> *p = root, *prev = 0;
    while (p != 0) { // find a place for inserting new node;
        prev = p;
        if (el < p->el)
            p = p->left;
        else p = p->right;
    }
    if (root == 0) // tree is empty;
        root = new BSTNode<T>(el);
    else if (el < prev->el)
        prev->left = new BSTNode<T>(el);
    else prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::inorderTrack(BSTNode<T> *p, vector<BSTNode<T>*> &vec){
    if (!p)  return;
    inorderTrack(p->left,vec);
    vec.push_back(p);
    inorderTrack(p->right,vec);

}


template<class T>
void BST<T>::toLEC() {

    vector<BSTNode<T>*> vec;

    inorderTrack(root,vec);

    for (int i = 0; i < vec.size(); ++i) {
       if(i != (vec.size() -1))
           vec[i]->right = vec[i+1];
       if(i != 0)
           vec[i]->left = vec[i-1];
    }

    vec[0]->left = vec[vec.size()-1];
    vec[vec.size()-1]->right = vec[0];

}

template<class T>
void BST<T>::PrintLEC() {
    BSTNode<T> *p;
    if(root)
    {
        cout<<endl<< "Recorrido por left " <<endl;
        p = root;
        do
        {
            visit(p);
            p = p->left;
        }while(p!=root);

        cout<< endl<< "Recorrido por rigth " <<endl;
        p = root;
        do
        {
            visit(p);
            p = p->right;
        }while(p!=root);
    }
}



int main() {
    BST<int> Arbol;
    Arbol.insert(32);
    Arbol.insert(22);
    Arbol.insert(52);
    Arbol.insert(8);
    Arbol.insert(26);
    Arbol.insert(43);
    Arbol.insert(61);
//    cout << "Preorder" << endl;
//    Arbol.preorder();
//    cout << endl << "Inorder" << endl;
//    Arbol.inorder();
//    cout << endl << "Postorder" << endl;
//    Arbol.preorder();
//    cout << endl;
//    Arbol.toLEC();
//    Arbol.PrintLEC();
//    cout << endl;

//    Arbol.inorder();

//    Arbol.inorder();
    cout<<endl;
    Arbol.toLEC();
    Arbol.PrintLEC();

    return 0;
}