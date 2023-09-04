#include <iostream>
#include <string>

#include "ArbolBinarioBusqueda.h"

using std::cout;
using std::string;

//implementación de clase "CPerson"
class CPerson {

private:
    //atributos de clase.
    size_t id;
    string name;
    string surname;

public:
    //constructor de clase CPerson.
    CPerson(size_t id=0, string name="", string surname="")
        : id(id), name(name), surname(surname) {
    }
    //métodos de clase
    string toString() const {
        return "ID: " + std::to_string(id) + " NAME: " + name + " SURNAME: " + surname;
    }
    //métodos de acceso.
    size_t getID() const {  //para obtener valor de atributo.
        return id;
    }
};

int main() {

    //creando referencia a instancia de tipo "ArbolBinarioBusqueda"
    ArbolBinarioBusqueda<CPerson*>* arbol = new ArbolBinarioBusqueda<CPerson*>(
                                                                    [](CPerson* p)->void { cout << p->toString() << "\n"; }, //1er arg: criterio de impresión.
                                                                     [](CPerson* p1, CPerson* p2)->bool { return p1->getID() < p2->getID(); }); //2do arg: criterio de comparacion "<".

    //agregando elementos al árbol binario de búsqueda: Para este caso recordar que los objetos deben tener un atributo ID, ya que a partir de eso se dará el criterio de comp.
    arbol->insert(new CPerson(5, "Gonzalo", "Zavala"));
    arbol->insert(new CPerson(1, "Flavia", "Gonzalez"));
    arbol->insert(new CPerson(8, "Abby", "Itzel"));
    arbol->insert(new CPerson(17, "Maria", "Litza"));
    arbol->insert(new CPerson(18, "Luciana", "Lisa"));

    //creando referencia a instancia temp. con "ID" del objeto que deseamos eliminar en el árbol.
    CPerson* pToDelete = new CPerson(8);
    //eliminando elemento del árbol.
    arbol->erase(pToDelete);
    delete pToDelete;

    //mostrando los elementos del árbol binario de búsqueda en forma "InOrder".
    std::cout << "\nRECORRIDO: IN-ORDER\n";
    arbol->inOrder();
    std::cout << "\nRECORRIDO: POST-ORDER\n";
    arbol->postOrder();
    std::cout << "\nRECORRIDO: PRE-ORDER\n";
    arbol->preOrder();

    //creando referencia a instancia temp. con "ID" del objeto que deseamos obtener en el árbol.
    CPerson* pToSearch = new CPerson(1);
    //obteniendo elemento del árbol.
    CPerson* item = arbol->get(pToSearch);
    //liberando memoria de referencia a instancia.
    delete pToSearch;

    //verificando si elemento obtenido en "item" es NULL, ya que si no se encuentra el elemento, ese sería su valor.
    if (item != NULL) {
        //mostrando elemento encontrado.
        cout << "\nELEMENTO: " << item->toString() << "\n";
    }
    else {
        //mostrando mensaje en caso el elemento NO sea encontrado.
        cout << "\nELEMENTO NULO!\n";
    }

    //mostrando cantidad de nodos en el árbol.
    cout << "\nNODOS EN EL ARBOL: " << arbol->size();
    //mostrando valor mín. del árbol.
    cout << "\nVALOR MIN: " << arbol->getMinValue()->toString();
    //mostrando valor máx. del árbol.
    cout << "\nVALOR MAX: " << arbol->getMaxValue()->toString();
    //mostrando nivel del árbol.
    cout << "\nNIVEL DEL ARBOL: " << arbol->treeLevel();

    return 0;
}
