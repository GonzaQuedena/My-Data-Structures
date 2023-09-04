//
// Created by Gonzalo Quedena on 22/06/2023.
//

#ifndef __DOUBLE__LINKEDLIST_H__
#define __DOUBLE__LINKEDLIST_H__

#include <cstdio>
#include <functional>

using std::function;

#include<iostream>
//implementación de clase DoubleLinkedList
template<class T>
class DoubleLinkedList {

private:
    //enlazando clase Node.
    class Node {

    public:
        //atributos para clase Node.
        T item;       //elemento para almacenar.
        Node* next;   //guarda ubi. de nodo siguiente.
        Node* prev;   //guarda ubi. de nodo anterior.

        //constructor para clase Node.
        Node(T item=NULL, Node* next=nullptr, Node* prev=nullptr)
                : item(item), next(next), prev(prev) {
        }
    };

public:
    //constructor para clase DoubleLinkedList.
    DoubleLinkedList()
        : head(nullptr), end(nullptr), n(0){
    }
    //destructor para clase.
    ~DoubleLinkedList() {
        //verificando si lista tiene elementos.
        if (head != nullptr && end != nullptr) {

            //nodo para obtener nodo inicial
            Node* current = nullptr;
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
    //métodos para clase DoubleLinkedList.
    void push_back(T item) {  //para agregar elementos a últ. posición.
        //creando nodo.
        Node* newNode = new Node(item);
        //verificando si lista está vacía.
        if (head == nullptr && end == nullptr) {
            //agregando primer nodo.
            head = newNode;
            //indicando a end que apunte a head.
            end = head;
        }
        else {
            //agregando nuevo nodo al final.
            end->next = newNode;
            //indicando al últ. nodo que apunte a su anterior.
            newNode->prev = end;
            //actualizando nodo final.
            end = newNode;
        }
        //incrementando cant. de elementos.
        ++n;
    }
    void erase(size_t pos) { //elimina elem. en una pos. específica.
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
                    head = head->next;
                    //evaluando si SOLO existe un nodo, a end le asignamos head(nullptr).
                    if (n == 1) {
                        end = head;
                    }
                }
                else if (current == end) { //evaluando si current y end son el mismo, es decir, es el último nodo.
                    prev->next = nullptr;
                    current->prev = nullptr;
                    end = prev;
                }
                else { //elimina cualquier otro nodo.
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
    void pop_front() { //elimina elem. en primera pos.
        erase(0);
    }
    void pop_back() {  //elimina elem. en últ. pos.
        erase(n - 1);
    }
    void iterator(function<void(T)> func, char it) { //para recorrer elementos de lista.
        //verificando que lista NO esté vacía.
        if (head != nullptr && end != nullptr) {
            //creando referencia current.
            Node* current;
            //evaluando tipo de recorrido a desear (n:normal, r:reverso).
            if (it == 'n') {
                //obteniendo nodo inicial.
                current = head;
            }
            else if (it == 'r'){
                //obteniendo nodo final.
                current = end;
            }

            //recorriendo nodos siempre que NO sea nullptr.
            while (current != nullptr) {
                //aplicando función lambda a elemendo del nodo.
                func(current->item);

                //actualizando nodo current(actual) dependiendo del tipo de recorrido.
                if (it == 'n') {
                    current = current->next;
                }
                else if (it == 'r') {
                    current = current->prev;
                }
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
    //atributos para clase DoubleLinkedList.
    Node* head; //nodo inicialde la lista.
    Node* end;  //nodo final de la lista.
    size_t n;   //indica cant. de elem. almacenados en lista.
};

#endif //__DOUBLE__LINKEDLIST_H__
