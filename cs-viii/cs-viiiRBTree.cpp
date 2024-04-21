#include<iostream>
#define RED false
#define BLACK true
using namespace std;


//CONSTRUCCION DE NODO
struct Node{
    int value;
    bool color; // rojo = false  // negro = true
    Node* left;
    Node* right;
    Node* parent;    
};

//CREAR NODOS
Node* createNode(int v){
    Node* new_node = new Node();
    new_node->value = v;
    new_node->color = RED;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;
    return new_node;
}

struct Tree{
    Node* root = nullptr;
};

//COLORES
void changeColor(Node* node, bool c){
    node->color = c;
}

//ROTACIONES
void leftRotate(Tree* t, Node* n){
    Node* right_child = n->right;
    n->right = right_child->left;

    if(right_child->left != nullptr){
        right_child->left->parent = n;
    }
    right_child->parent = n->parent;

    if(n->parent == nullptr){
        t->root = right_child;
    }
    else if(n == n->parent->left){
        n->parent->left = right_child;
    }
    else{
        n->parent->right = right_child;
    }
    
    right_child->left = n;
    n->parent = right_child;
}

void rightRotate(Tree* t, Node* n){
    Node* left_child = n->left;
    n->left = left_child->right;

    if(left_child->right != nullptr){
        left_child->right->parent = n;
    }
    left_child->parent = n->parent;

    if(n->parent == nullptr){
        t->root = left_child;
    }
    else if(n == n->parent->right){
        n->parent->right = left_child;
    }
    else{
        n->parent->left = left_child;
    }

    left_child->right = n;
    n->parent = left_child;
}

void adjust(Tree* t, Node* n){
    Node* tio = nullptr;
    while(n->parent != nullptr && n->parent->color == RED){
        if(n->parent == n->parent->parent->left){
            tio = n->parent->parent->right;
            if(tio != nullptr && tio->color == RED){
                changeColor(n->parent, BLACK);  
                changeColor(tio, BLACK);
                changeColor(n->parent->parent, RED);
                n = n->parent->parent;
            }
            else{
                if(n == n->parent->right){
                    n = n->parent;
                    leftRotate(t, n);
                }
                changeColor(n->parent, BLACK);
                changeColor(n->parent->parent, RED);
                rightRotate(t, n->parent->parent);
            }   
        }
        else{
            tio = n->parent->parent->left;
            if(tio != nullptr && tio->color == RED){
                changeColor(n->parent, BLACK);
                changeColor(tio, BLACK);
                changeColor(n->parent->parent, RED);
                n = n->parent->parent;
            }
            else{
                if(n == n->parent->left){
                    n = n->parent;
                    rightRotate(t, n);
                }
                changeColor(n->parent, BLACK);
                changeColor(n->parent->parent, RED);
                leftRotate(t, n->parent->parent);
            }
        }
    }
    changeColor(t->root, BLACK);
}


void insert(Tree* t, int v){
    Node* new_node = createNode(v);
    Node* y = nullptr;
    Node* x = t->root; //está inicializado como nullptr

    //DECIDE SI VA A LA IZQ O DER DE LA RAIZ
    while(x != nullptr){
        y = x;
        if(new_node->value < x->value){
            x = x->left;
        }
        else{ x = x->right; }
    }
    new_node->parent = y;

    //DECIDE SI VA A LA IZQ O DER DEL PADRE
    if(y == nullptr){
        t->root = new_node;
    }
    else if (new_node->value < y->value)
    {
        y->left = new_node;
    }
    else{ y->right = new_node; }

    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->color = RED;

    adjust(t, new_node);
}   

void printInOrder(Node* n, int space) {
    if (n == nullptr) return;
    
    space += 10;

    // Imprimir el subárbol derecho
    printInOrder(n->right, space);

    // Imprimir el nodo actual
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    if (n->parent != nullptr) {
        if (n == n->parent->left)
            cout << "|----" << n->value << "(" << n->color << ")";
        else
            cout << "|----" << n->value << "(" << n->color << ")";
    } else {
        cout << n->value << "(" << n->color << ")";
    }

    // Imprimir el subárbol izquierdo
    printInOrder(n->left, space);
}


void printTree(Tree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    
    // Llamar a la función de impresión con el nodo raíz y el espacio inicial
    printInOrder(tree->root, 0);
    std::cout << std::endl;
}

int main(){
    Tree* tree = new Tree();
    
    insert(tree, 50);
    insert(tree, 70);
    insert(tree, 40);
    insert(tree, 30);
    insert(tree, 65);
    insert(tree, 35);
    insert(tree, 85);
    insert(tree, 20);
    insert(tree, 90);
    insert(tree, 10);
    insert(tree, 80);
    insert(tree, 5);
    insert(tree, 15);
    insert(tree, 60);
    insert(tree, 55);
    
    cout << "Árbol RB" << endl;
    cout << "RED (0) // BLACK (1)" << endl;
    printTree(tree);

    delete tree;
    return 0;
}

