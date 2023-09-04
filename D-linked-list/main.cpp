#include <iostream>
#include "DoubleLinkedList.h"

int main() {

    //creando referencia a una instancia de DoubleLinkedList.
    DoubleLinkedList<int>* myList = new DoubleLinkedList<int>;

    //agregando elementos a la lista.
    myList->push_back(10);
    myList->push_back(20);
    myList->push_back(30);
    myList->push_back(40);
    myList->push_back(50);
    myList->push_back(60);

    //eliminando elementos.
    myList->erase(2);
    myList->pop_back();
    myList->pop_front();

    //verificando que lista NO esté vacía.
    if (!myList->empty()) {
        //iterando elementos (indicando que nos muestre en consola).
        myList->iterator([](int v)->void {
            std::cout << v << " ";
        }, 'n');
    }
    else {
        //si lista está vacía, mostramos mensaje...
        std::cout << "LISTA VACIA!";
    }

    //liberando memoria de referencia a instancia.
    delete myList;

    return 0;
}
