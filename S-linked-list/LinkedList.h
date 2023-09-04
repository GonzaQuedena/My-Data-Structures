//
// Created by Gonzalo Quedena on 22/06/2023.
//

#ifndef __LINKEDLIST_LINKEDLIST_H__
#define __LINKEDLIST_LINKEDLIST_H__

#include<cstdio>
#include<functional>

using std::function;

//implementación de clase LinkedList.
template<class T>
class LinkedList {

private:
    //enlazando clase Node.
    class Node {

    public:
        //atributos para clase Node.
        T item;       //elemento para almacenar.
        Node* next;   //guarda ubi. de nodo siguiente.

        //constructor para clase Node.
        Node(T item=NULL, Node* next=nullptr)
                : item(item), next(next){
        }
    };

public:
    //constructor para clase LinkedList.
    LinkedList()
            : head(nullptr), end(nullptr), n(0){
    }
    //destructor para clase
    ~LinkedList() {
        //verificando si lista tiene elementos.
        if (head != nullptr && end != nullptr) {

            //nodo para obtener nodo inicial.
            Node* current = nullptr;
            //mientras el nodo inicial sea distinto al nodo final.
            while(head != end) {
                //obteniendo nodo inicial.
                current = head;
                //asignando al nodo inicial, el nodo siguiente.
                head = head->next;
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
    //métodos para clase LinkedList.
    void push_back(T item) { //para agregar elementos a últ. posición.
        //creando nodo.
        Node* newNode = new Node(item);
        //verificando si lista está vacía.
        if (head == nullptr && end == nullptr) {
            //agregando primer nodo.
            head = newNode;
            //indicando a end que apunte a head.
            end = head;
            //incrementando cant. de elementos.
            ++n;
        }
        else {
            //agregando nuevo nodo al final.
            end->next = newNode;
            //actualizando nodo final.
            end = newNode;
            //incrementando cant. de elementos.
            ++n;
        }
    }
    void erase(size_t pos) {
        //verificando que lista NO esté vacía.
        if (head != nullptr) {
            //verificando que hacemos a una pos. existente.
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

                //evaluando si head y end son el mismo, es decir, existe 1 nodo.
                if (current == head) {
                    head = head->next;
                    //evaluando si SOLO existe un nodo, a end le asignamos head(nullptr).
                    if (n == 1) {
                        end = head;
                    }
                }
                else if (current == end) {
                    prev->next = nullptr;
                    end = prev;
                }
                else {
                    prev->next = current->next;
                    current->next = nullptr;
                }
                //eliminando nodo.
                delete current;
                //decrementando la cant. de elementos.
                --n;
            }
        }
    }
    void pop_front() { //elimina elem. en primera pos.
        erase(0);
    }
    void pop_back() {  //elimina elem. en últ. pos.
        erase(n - 1);
    }
    void iterator(function<void(T)> func) { //para recorrer elementos de lista.
        //verificando que lista NO esté vacía.
        if (head != nullptr && end  != nullptr) {
            //obteniendo nodo inicial
            Node* current = head;
            //recorriendo nodos siempre que no seas nullptr.
            while(current != nullptr) {
                //aplicando función lambda a elemento del nodo.
                func(current->item);
                //actualizando nodo current(actual).
                current = current->next;
            }
        }
    }
    bool empty() {
        return (head == nullptr && end == nullptr);
    }

    Node* begin() {
        return head;
    }
    Node* _end() {
        return end;
    }

private:
    //atributos para clase LinkedList.
    Node* head;  //nodo inicio de la lista.
    Node* end;   //nodo final de la lista.
    size_t n;    //indica cant. de elem. almacenados en lista.
};

#endif //LINKEDLIST_LINKEDLIST_H