#include<iostream>
#define N 27
using namespace std;

//NODO
struct TrieNode{
    bool is_final;
    TrieNode* children[N];
};  

//ARBOL
struct TrieTree{
    TrieNode* root;
};

//NUEVO NODO
TrieNode* newNode(){
    TrieNode* node = new TrieNode();
    node->is_final = false;
    for(int i = 0; i < N; i++){
        node->children[i] = nullptr;
    }
    return node;
}

void insert(TrieNode* root, string word){
    TrieNode* current_node = root;
    for(auto w : word){
        int loc = w - 'a';
        if(current_node->children[loc] == NULL){ // mapea el caracter (w), si es NULL 
            current_node->children[loc] = newNode();  // se crea un nuevo nodo
        }
        current_node = current_node->children[loc];
    }
    current_node->is_final = true;
}

bool search(TrieNode* root, string word){
    TrieNode* current_node = root;
    for(auto w : word){
        int loc = w - 'a';
        if(current_node->children[loc] == NULL){ // mapea el caracter (w), si es NULL 
            return false; 
        }
        current_node = current_node->children[loc];
    }
    return (current_node != nullptr && current_node->is_final);
}

void printTrieHelper(TrieNode* node, string prefix) {
    if (node == nullptr) return;

    if (node->is_final) {
        cout << prefix << endl;
    }

    for (int i = 0; i < N; ++i) {
        if (node->children[i] != nullptr) {
            char next_char = 'a' + i;
            printTrieHelper(node->children[i], prefix + next_char);
        }
    }
}

// Función para imprimir el árbol Trie de prefijos
void printTrie(TrieNode* root) {
    printTrieHelper(root, "");
}



int main(){
    TrieTree* arbol = new TrieTree();
    arbol->root = newNode();
    insert(arbol->root, "hola");
    insert(arbol->root, "holas");
    insert(arbol->root, "holita");
    cout<<search(arbol->root, "hola")<<endl;
    cout<<search(arbol->root, "holas")<<endl;
    cout<<search(arbol->root, "holita")<<endl;
    cout<<search(arbol->root, "hol")<<endl;
    cout<<search(arbol->root, "hola")<<endl;
    printTrie(arbol->root);
    return 0;
}