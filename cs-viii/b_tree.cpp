#include <iostream>
#include <vector>
using namespace std;

class BTreeNode{
    private:
        int t, n;
        bool leaf;
        vector<int> keys;
        vector<BTreeNode*> children;     
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
                    i = i -1;
                }
                keys[i+1] = k;
                n = n + 1;
            }

        }
        splitChild(int i, BTreeNode* y);


};

class BTree{
    private:
        BTreeNode* raiz;
        int t;
    public:
        
        BTree(int _t){
            raiz = nullptr;
            t = _t;
        }

        void traverse(){
            if(raiz != nullptr){
                traverse() = raiz;
            }
        }
};


int main(){

}