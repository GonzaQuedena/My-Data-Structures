//
// Created by Gonzalo Quedena on 23/06/2023.
//

#ifndef __CIRCULAR_DOUBLY_LINKED_LIST_H__
#define __CIRCULAR_DOUBLY_LINKED_LIST_H__

#include <cstdio>
#include <functional>

using std::function;

//implementación de la clase CircularDoublyLinkedList.
template<typename T>
class CircularDoublyLinkedList {

private:
    //enlazando clase Node.
    class Node {

    public:
        //atributos para clase CircularDoublyLinkedList.
        T item;        //elemento a almacenar.
        Node* next;    //guarda ubi. del nodo siguiente.
        Node* prev;    //guarda ubi. del nodo anterior.

        //constructor para clase Node.
        Node(T item=NULL, Node* next=nullptr, Node* prev=nullptr)
            : item(item), next(next), prev(prev) {
        }
    };

public:
    //constructor para clase CircularDoublyLinkedList.
    CircularDoublyLinkedList()
        : head(nullptr), end(nullptr), n(0){
    }
    //destructor para clase.
    ~CircularDoublyLinkedList() {
        //verificando si la lista tiene elementos.
        if (head != nullptr && end != nullptr) {

            //nodo para obtener nodo inicial.
            Node* current = nullptr;
            //desconectando extremos.
            head->prev = nullptr;
            end->next = nullptr;

            //mientras el nodo inicial sea distinto al nodo final.
            while (head != end) {

                //obteniendo nodo final.
                current = end;
                //asignando al nodo final, el nodo anterior.
                end = end->prev;
                //asignando al anterior del nodo current(actual) nullptr.
                current->prev = nullptr;
                //asignando al siguiente del nodo final nullptr.
                end->next = nullptr;
                //eliminando nodo current(actual).
                delete current;
            }

            //obteniendo último nodo restante.
            current = head;
            //asignando al nodo inicial (nullptr).
            head = head->next;
            //asignando al nodo final el inicial.
            end = head;
            //eliminando nodo current(actual).
            delete current;
        }
    }
    //métodos para la clase CircularDoublyLinkedList.
    void push_back(T item) {  //para agregar elementos a últ. posición.
        //creando nodo.
        Node* newNode = new Node(item);
        //verificando si lista está vacía.
        if (head == nullptr && end == nullptr) {
            //agregando primer nodo;
            head = newNode;
            //indicando que en apunte a head.
            end = head;
            //indicando que el sig. de end apunte a head.
            end->next = head;
            //indicando que el ant. de head apunte a end.
            head->prev = end;
        }
        else {
            //agregando nuevo nodo al final.
            end->next = newNode;
            //indicando al últ. nodo que apunte a su anterior.
            newNode->prev = end;
            //actualizando nodo final.
            end = newNode;
            //actualizando nodos extremos.
            end ->next = head;
            head->prev = end;
        }
        //incrementando cant. de elementos.
        ++n;
    }
    void erase(size_t pos) {
        //verificando que lista NO esté vacía.
        if (head != nullptr && end != nullptr) {
            //verificando que hacemos ref. a una pos. existente.
            if (pos >= 0 && pos < n) {

                //obteniendo nodo inicial.
                Node* current = head;
                //inicializando nodo en nullptr (este nodo tomará nodo anterior a current).
                Node* prev = nullptr;

                //actualizando nodos siempre que no lleguemos a la pos. deseada.
                for (int i = 0; i != pos; ++i) {
                    prev = current;
                    current = current->next;
                }

                //evaluando si current y head son el mismo, es decir, no hizo recorrido.
                if (current == head) {

                    //evaluamos que la cant. de elem. sea mayor a 1.
                    if (n > 1) {

                        //actualizamos head al sig. nodo.
                        head = head->next;
                        //actualizamos el nodo ant. de head al último nodo.
                        head->prev = end;

                        //desconectamos nodo current(actual).
                        current->prev = nullptr;
                        current->next = nullptr;
                    }
                    else {  //eliminando cuando queda SOLO 1 elemento.

                        //actualizamos sig. de nodo end a nullptr.
                        end->next = nullptr;
                        //actualizamos ant. de nodo head a nullptr;
                        head->prev = nullptr;
                        //actualizando head a nullptr.
                        head = head->next;
                        //actualizando nodo final a nullptr.
                        end = head;
                    }
                }
                else if (current == end) { //evaluando si current y end son el mismo, es decir, es el último nodo.
                    current->prev = nullptr;
                    current->next = nullptr;

                    prev->next = head;
                    head->prev = prev;
                    end = prev;
                }
                else { //eliminando cualquier otro nodo.
                    prev->next = current->next;
                    current->next->prev = prev;
                }
                //eliminando nodo.
                delete current;
                //decrementando la cant. de elementos.
                --n;
            }
        }
    }
    void pop_front() {  //elimina elem. en primera pos.
        erase(0);
    }
    void pop_back() {  //elimina elem. en últ. pos.
        erase(n - 1);
    }
    void iterator(function<void(T)> func, char it) {  //para recorre elementos de lista.
        //verificamos que lista NO esté vacía.
        if (head != nullptr && end != nullptr) {
            //creando referencia current.
            Node* current;
            //evaluando tipo de recorrido a desear (n:normal, r:reverso).
            if (it == 'n') {
                //obteniendo nodo inicial.
                current = head;
            }
            else if (it == 'r') {
                //obteniendo nodo final.
                current = end;
            }

            for (int i = 0; i < n; ++i) {
                //aplicando función lambda a elemento del nodo.
                func(current->item);

                //actualizando nodo current(actual) dependiendo del tipo de recorrido.
                if (it == 'n') {
                    current = current->next;
                }
                else if(it == 'r') {
                    current = current->prev;
                }
            }
        }
    }
    bool empty() {
        return (head == nullptr && end == nullptr);
    }

private:
    Node* head;  //nodo inicial de lista.
    Node* end;   //nodo final de lista.
    size_t n;    //indica cant. de elem. almacenados en lista.
};


#endif //__CIRCULAR_DOUBLY_LINKED_LIST_H__
