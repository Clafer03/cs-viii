#include<iostream>
using namespace std;

int main()
{
    int n  = 5;

    for(int i = 0; i < n; i++){
        cout << "Numero actual : " << i << endl; 
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << "Valor i : " << i << " Valor j: " << j << endl;
        }
    }
    return 0;
}

