#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;
const int MAX_SIZE = 100000;


void inserta_datos(){
    int n = 0; 
    cout << "Ingrese la cantidad de valores a ingresar en el arreglo: ";
    cin >> n;
    if(n <= 0 && n > MAX_SIZE){  // Si es un valor negativo o si sobrepasa el valor máximo ...  
        cout << "La cantidad ingresada no es válida";
        return;
    }
    else{
        int i = 0;
        int arreglo[MAX_SIZE];
        srand(time(0));
        auto start = chrono::system_clock::now();
        while(i < n){arreglo[i] = rand() * 1000; i++;} //n

        i = 0;
        cout << "Los valores generados son: \n";
        while(i<n) {cout << arreglo[i] << '\n'; i++;} //n
        
        auto finish = chrono::system_clock::now();
        chrono::duration<double> tiempo = finish - start;
        cout<<"El tiempo de ejecución es: " << tiempo.count();
    }
}

int main(){
    inserta_datos();
    return 0;
}

 