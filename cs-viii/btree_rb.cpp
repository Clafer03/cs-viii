#include<iostream>
using namespace std;

//CONSTRUCCION DE NODO
struct Node{
    int valor;
    bool color; // rojo = false  // negro = true
    Node* left;
    Node* right;
    Node* parent;    
};

//CONSTRUCCION DE ARBOL
struct Tree{
    Node* root = nullptr;
};

//CREAR NODOS
Node* createNode(int v){
    Node* new_node = new Node;
    new_node->valor = v;
    new_node->color = false;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;
    return new_node;
}

Node* searchNode(Tree* t, int v){
    Node* actual_node = t->root;
    while(actual_node != nullptr && actual_node->valor != v){
        if(v < actual_node->valor){
            actual_node = actual_node->left;
        }
        else{
            actual_node = actual_node->right;
        }
    }
    return actual_node;
}

Node* getNextNode(Node* n){
    if(n->right != nullptr){
        n = n->right;
        while(n->left != nullptr){
            n = n->left;
        }
    }
    return n;
}

//COLORES
void changeColor(Node* node, bool c){
    node->color = c;
}

bool nodeColor(Node* node){
    if(node == nullptr){ //nodo nulo tratado como negro
        return true;
    }
    return node->color;
}

//ROTACIONES
void leftRotate(Tree* t, Node* n){
    Node* right_child = n->right;
    n->right = right_child->left;
    if(right_child != nullptr){
        right_child->left->parent = n;
    }
    right_child->parent = n->parent;
    if(n->parent == nullptr){
        t->root = right_child;
    }
    else if(n = n->parent->left){
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
    else if(n = n->parent->right){
        n->parent->right = left_child;
    }
    else{
        n->parent->left = left_child;
    }
    left_child->right = n;
    n->parent = left_child;
}

//INSERCIONES Y AJUSTE
void insertRecursively(Node* actual_node, Node* new_node){
    if(new_node->valor < actual_node->valor){
        if(actual_node->left == nullptr){
            actual_node->left = new_node;
            new_node->parent = actual_node;
        }
        else{ insertRecursively(actual_node->left, new_node); }
    }
    else{
        if(actual_node->right == nullptr){
            actual_node->right = new_node;
            new_node->parent = actual_node;
        }
        else{ insertRecursively(actual_node->right,new_node); }
    }
}

void adjustDelete(Tree* t, Node* n){
    Node* sibling;
    while(n != t->root && nodeColor(n) == true){
        if(n = n->parent->left){
            sibling = n->parent->right;
            if(nodeColor(sibling) == false){
                changeColor(sibling, true);
                changeColor(n->parent, false);
                leftRotate(t, n->parent);
                sibling = n->parent->right;
            }
            if(nodeColor(sibling->left) == true && nodeColor(sibling->right) == true){
                changeColor(sibling, false);
                n = n->parent;
            }
            else{
                if(nodeColor(sibling->right) == true){
                    changeColor(sibling->left, true);
                    changeColor(sibling, false);
                    rightRotate(t, sibling);
                    sibling = n->parent->right;
                }
                changeColor(sibling, nodeColor(n->parent));
                changeColor(n->parent, true);
                changeColor(sibling->right, true);
                leftRotate(t, n->parent);
                n = t->root;
            }
        }
        else{
            sibling = n->parent->left;
            if(nodeColor(sibling) == false){
                changeColor(sibling, true);
                changeColor(n->parent, false);
                rightRotate(t, n->parent);
                sibling = n->parent->left;
            }
            if(nodeColor(sibling->right) == true &&  nodeColor(sibling->left) == true){
                changeColor(sibling, false);
                n = n->parent;
            }
            else{
                if(nodeColor(sibling->left) == true){
                    changeColor(sibling->right, true);
                    changeColor(sibling, false);
                    leftRotate(t, sibling);
                    sibling = n->parent->left;
                }
                changeColor(sibling, nodeColor(n->parent));
                changeColor(n->parent, true);
                changeColor(sibling->left, true);
                rightRotate(t, n->parent);
                n = t->root;
            }
        }
    }
    changeColor(n, true);
}

Node* deleteNode(Tree* t, int v){
    Node* node_to_delete = searchNode(t, v);
    Node* replace_node;
    Node* replace_child;
    if(node_to_delete == nullptr){
        return 0;
    }
    if(node_to_delete->left == nullptr || node_to_delete->right == nullptr){
        replace_node = node_to_delete;
    }
    else{
        replace_node = getNextNode(node_to_delete);
    }
    if(replace_node->left != nullptr){
        replace_child = replace_node->left;
    }
    else{
        replace_child = replace_node->right;
    }
    if(replace_child != nullptr){
        replace_child->parent = replace_node->parent;
    }
    if(replace_node->parent == nullptr){
        t->root = replace_child;
    }
    else{
        if(replace_node = replace_node->parent->left){
            replace_node->parent->left = replace_child;
        }
        else{
            replace_node->parent->right = replace_child;      
        }
    }
    if(replace_node != node_to_delete){
        node_to_delete->valor = replace_node->valor;
    }   
    if(replace_node->color = true){
        adjustDelete(t, replace_child);
    }
    return replace_node;
}

void adjust(Tree* t, Node* n){
    //comprobar si tiene padre en primera? xd
    while(n->parent->color == false){
        if(n->parent = n->parent->parent->left){
            Node* tio = n->parent->parent->right;
            if(tio->color = false){
                changeColor(n->parent, true);
                changeColor(tio, true);
                changeColor(n->parent->parent, false);
                n = n->parent->parent;
            }
            else{
                if(n = n->parent->parent->right){
                    n = n->parent;
                    leftRotate(t, n);
                }
                changeColor(n->parent, true);
                changeColor(n->parent->parent, false);
                rightRotate(t, n->parent->parent);
            }
        }
        else{
            Node* tio = n->parent->parent->left;
            if(tio->color = false){
                changeColor(n->parent, true);
                changeColor(tio, true);
                changeColor(n->parent->parent, false);
                n = n->parent->parent;
            }
            else{
                if(n = n->parent->left){
                    n = n->parent;
                    rightRotate(t, n);
                }
                changeColor(n->parent, true);
                changeColor(n->parent->parent, false);
                leftRotate(t, n->parent->parent);
            }
        }
    }
    changeColor(t->root, true);
}

//INSERCIÓN
void insert(Tree* t, int v){
    Node* new_node = createNode(v);
    if(t == nullptr){
        t = new Tree; // crear el arbol (inicializar)
        t->root = new_node; //ERROR
    }
    else{ insertRecursively(t->root, new_node); }
    changeColor(new_node, false); //rojo
    adjust(t, new_node);
}


int main(){

    Tree* arbol = nullptr;
    insert(arbol, 1);
    insert(arbol, 2);
    insert(arbol, 5);
    insert(arbol, 9);
    insert(arbol, 14);

    return 0;

}
