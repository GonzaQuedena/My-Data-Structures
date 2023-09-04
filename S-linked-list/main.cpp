#include <iostream>
#include "LinkedList.h"

int main() {

    //creando referencia a una instancia de LinkedList.
    LinkedList<int>* myList = new LinkedList<int>;

    //agregando elementos a la lista.
    myList->push_back(10);
    myList->push_back(20);
    myList->push_back(30);
    myList->push_back(40);
    myList->push_back(50);
    myList->push_back(60);
    myList->push_back(70);
    myList->push_back(80);
    myList->push_back(90);
    myList->push_back(100);

    //eliminando elementos.
    myList->erase(3);   //eliminando en pos. especifica.
    myList->pop_back();      //eliminando en ult. pos.
    myList->pop_front();     //eliminando en primera pos.

    //verificando que lista NO esté vacía.
    if (!myList->empty()) {
        //iterando elementos (indicando que nos muestre en consola).
        myList->iterator([](int v)->void {
            std::cout << v << " ";
        });
    }
    else {
        //si lista está vacía, mostramos el mensaje...
        std::cout << "LISTA VACIA!";
    }

    //liberando memoria de referencia a instancia.
    delete myList;
    return 0;
}
