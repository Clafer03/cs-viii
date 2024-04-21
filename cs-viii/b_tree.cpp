#include <iostream>
#include <vector>
using namespace std;

class BTreeNode{
    private:
        int t, n;
        bool leaf;
        vector<int> keys;
        vector<BTreeNode*> children;  //vector que contiene la clase BTreeNode, haciendo posible la generación de los nodos hijos

    public:
        BTreeNode(int _t, bool _leaf)
        {
            this->t = _t;
            this->leaf = _leaf;
            n = 0;
            keys.resize(2*t-1);
            children.resize(2*t);
        }

        void traverse(){
            int i = 0;
            while(i < n){
                if(!leaf){
                    children[i]->traverse();
                }
                cout << " ";
                cout << keys[i];
                i += 1;
            }
            if(!leaf){
                children[i]->traverse();
            }
        }
        void insertNonFull(int k)
        {
            int i = n - 1;
            if(leaf){
                while(i >= 0 && keys[i] > k){
                    keys[i+1] = keys[i];
                    i -= 1;
                }
                keys[i+1] = k;
                n += 1;
            }
            else{
                while(i >= 0 && keys[i] > k){
                    i += 1;
                }
                if(children[i+1]->n==2*t+1){
                    splitChild(i+1, children[i+1]);
                    if(keys[i+1] < k){
                        i += 1;
                    }
                }
                children[i+1]->insertNonFull(k);
            }

        }
        void splitChild(int i, BTreeNode* y){
            BTreeNode* z = new BTreeNode(y->t, y->leaf);
            z-> n = t-1;
            for(int j = 0; j < t-1; j++){
                z->keys[j] = y->keys[j+t];
            }
            if(!y->leaf){
                for(int j = 0; j < t; j++){
                    z->children[j] = y->children[j+t];
                }
            }
            y->n = t - 1;

            for(int j = n; j >= i + 1; j--){
                children[j+1] = children[j];
            }
            children[i+1] = z;
            for(int j = n-1; j>= i; j--){
                keys[j+1] = keys[j];
            } 
            keys[i] = y->keys[t-1];
            n += 1;
        }
};

class BTree{
    private:
        BTreeNode* root;
        int t;
    public:
        
        BTree(int _t){
            root = nullptr;
            t = _t;
        }

        void traverse(){
            if(root != nullptr){
                root->traverse();
            }
        }

        void insert(int k){
            if(root = nullptr){
                root = new BTreeNode(t, true);
                root->keys[0] = keys;
                root.n = 1;
            }
        }
};


int main(){

}