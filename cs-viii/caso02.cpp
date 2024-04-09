#include <iostream>

using namespace std;

class union_find {
private: 
    int* parent;
    int* size;

public:

    union_find(int n){
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++){
            parent[i] = i;
            size[i] = 1; // Cada conjunto tiene inicialmente un solo elemento
        }
    }

    int find(int x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSet (int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY){
            return ;
        }

        if (size[rootX] < size[rootY]){
            parent[rootX] = rootY;
            size[rootY] = size[rootX];
        }
        else{
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }   
};

int main (){
    union_find uf(12);

    uf.unionSet(1, 0);
    uf.unionSet(2, 0);
    uf.unionSet(3, 2); 

    uf.unionSet(5, 4);
    uf.unionSet(6, 4);
    uf.unionSet(7, 6);

    uf.unionSet(9, 8);
    uf.unionSet(10, 8);
    uf.unionSet(11, 10);

    // uf.unionSet(1,0);
    // uf.unionSet(2,0);
    // uf.unionSet(2,3);

    // uf.unionSet(4,0);
    // uf.unionSet(4,5);
    // uf.unionSet(6,7);
    // uf.unionSet(6,4);

    // uf.unionSet(8,0);
    // uf.unionSet(9,8);
    // uf.unionSet(10,8);
    // uf.unionSet(11,10);

    cout << "¿El elemento 1 y el elemento 3 son equivalentes? " << endl;

    if (uf.find(1) == uf.find(3)){
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    cout << "¿El elemento 2 y el elemento 9 son equivalentes?" << endl;
    if (uf.find(2) == uf.find(9)){
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    cout << "¿El elemento 4 y el elemento 7 son equivalentes?" << endl;
    if (uf.find(4) == uf.find(7)){
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    cout<<uf.find(0)<<endl;

   return 0;
}