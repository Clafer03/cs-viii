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

//ROTACIONES
void leftRotate(Tree* t, Node* n){
    Node* right_child = n->right;
    n->right = right_child->left;
    if(right_child != nullptr){
        right_child->left->parent = n;
    }
    right_child->parent = n->parent;
}

void rightRotate(){

}

//COLORES
void changeColor(Node* nodo, bool c){
    nodo->color = c;
}
bool nodeColor(Node* node){
    if(node = nullptr){ //nodo nulo tratado como negro
        return true;
    }
    return node->color;
}

int main(){

}





// class rbTree{
//     private:
//         Node* root;
//         bool root_color;
//     public:
//         rbTree(){
//             root = nullptr;
//             root_color = true;
//         }

//     void insert(int v){
//         Node* new_node = createNode(v);
//         if(rbTree == NULL){
            
//         }
//     }
// };