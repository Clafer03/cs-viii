#include <iostream>
#include <string>
//#include <stdlib.h> descomenta si se cierra la pantalla al compilar
#define max 5
using namespace std;


typedef struct {
  int final;
  int inicio;
  string vector[max];
} queue;

void Crear(queue &Cola) {
  Cola.final = -1;
  Cola.inicio = -1;
}

bool IsEmpty(queue Cola) {
  if(Cola.final == -1) {
    return true;
  } // else? no es necesario, C y C++, cuando encuentran un return AUTOMÁTICAMENTE dejan de ejcutar lo que esté después
  return false;
}

int getElements(queue Cola) {
  //Si estás vacía pues es 0 la cantidad
  if(IsEmpty(Cola)) {
    return 0;
  }

  //si inicio es menor que final está en un estado "normal", así que solo hago diferencia de posiciones
  if(Cola.inicio < Cola.final) {
    return Cola.final - Cola.inicio + 1;
  }
  //En este punto no entró al if anterior, por tanto es cuando inicio sea mayor o igual que final (aunque es igual en IsEmpty)
  return max - Cola.inicio + Cola.final + 1;
}

bool IsFull(queue Cola) {
  if(getElements(Cola) == max) {
    return true;
  }
  return false;
}


void Add(queue &Cola, string elemento) {
  if(!IsFull(Cola)) {//if(1)

    if(IsEmpty(Cola)) { //Si es la primera vez que se mete algo, pues incrementamos inicio y YA NO MAS
      Cola.inicio++;
    }

    /*
      Si el final esta en el tope y NO ESTÁ FULL PORQUE SI ENTRÓ AQUÍ ES PORQUE EN EL IF(1) DIO FALSO!
      Y como no está llena y está en el tope final SI O SI la posición 0 al menos está vacía...
    */
    if(Cola.final == max - 1) {
      Cola.final = 0;
    } else { //Ya sea que esté en el punto "normal" o "circular", siempre se aumenta final
      Cola.final++;
    }

    Cola.vector[Cola.final] = elemento;
    cout << "Add: <" << elemento << ">" << endl;
    cout << "inicio: " << Cola.inicio << endl;
    cout <<"final: " << Cola.final << "\n" << endl;
  } else {
    cout << "Esta llena, no pudo entrar <" << elemento << ">" << endl;
  }
}

/*
  Función que borra un elemento de la cola, la paso por referencia porque quiero modificar la cola
*/
void Del(queue &Cola) {
  if(!IsEmpty(Cola)) {

    cout << "Se ha borrado " << Cola.vector[Cola.inicio] << endl; //Es OBVIO que todavia no se ha borrado
    //Pero lo imprimo antes de borrar para poder mostrarlo ._.

    if(getElements(Cola) == 1) {
      Crear(Cola); //kha?
      /*
        Recuerda que si hay un solo elemento, al borarlo debe quedar vacía la cola.
        Y en que condiciones la cola está vacia? cuando inicio = -1 y final = -1, o sea lo que hace "Crear"
        Reutilizar código papu
      */
    } else {
      Cola.inicio++; //Cuando no haya un solo elemento, pues corremos el inicio hacia adelante
      //asi dejamos vacia la posicion donde estaba para que mas adelante en algun punto se haga circular en Add...
    }
  } else {
    cout << "Vacia no se puede borrar nada" << endl;
  }
}

/*
  Recorre una cola circular EN ORDEN simulando una cola no circular (es decir del primero al ultimo).
  La idea de las colas circulares es eficientar el proceso de las normales.
  Por ejemplo para añadir un nuevo elemento en una normal hay que recorrer cada elemento y ponerlo en una posición
  anterior a la que estaba (si hay 1000 elementos pues se hace un bucle de 1000)
  por eso es mejor hacerlas circular, para eficientar su funcionamiento interno y no estar haciendo bucles al agregar.
*/
void Recorrer(queue Cola) {
  if(!IsEmpty(Cola)) {
    int x;
    //Como esta vaina es circular, y queremos recorrerla del primero al ultimo, hay que chequear sus dos estados
    if(Cola.inicio <= Cola.final) {
      for(x = 0; x <= Cola.final; x++) {
        cout << "Cola.vector["<< x << "]: " << Cola.vector[x] << endl;
      }
    } else {
      //kha?
      for(x = Cola.inicio; x < max; x++) {
        cout << "Cola.vector["<< x << "]: " << Cola.vector[x] << endl;
      }
      for(x = 0; x <= Cola.final; x--) {
        cout << "Cola.vector["<< x << "]: " << Cola.vector[x] << endl;
      }
      /*
        Bueno, supongase esta situación
        i = inicio de la cola
        f = final de la cola
            f     i
        0 1 2 3 4 5 6
        e f g     c d
        Primero recorremos de la posición 5 a la 6,
        Luego de que llegue a 6 (max - 1) (lo que es lo mismo que escribir x < max o x <= max - 1 en el for)
        pues todavia nos falta una parte (de 0 a 2)
        por tanto recorremos de 0 al final
      */
    }
  } else {
    cout << "nada que ver" << endl;
  }
}

int main() {

  queue Cola;
  Crear(Cola);
  //Add(Cola,"Soy un ejemplo");
  //Del();
  //Recorrer(Cola,false);
  //asi se usan las funciones, ahora experimenta

  //system("pause"); //descomentar si se cierra la pantalla al compilar
  return 1;