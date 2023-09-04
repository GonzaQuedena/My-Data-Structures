//
// Created by Gonzalo Quedena on 25/06/2023.
//
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <list>
#include <vector>
#include <functional>
#include <cstdio>
#include <string>
#include <iostream>

using std::list;
using std::vector;
using std::string;
using std::function;
using std::find;

//implementación clase HashTable
template<class T>
class HashTable {

private:
    //enlazando e implementación de clase Node.
    class Node {

    public:
        //atributos de clase Node.
        string key;
        T item;
        //constructor de clase Node.
        Node(string key="", T item=NULL)
                : key(key), item(item) {
        }
    };
    //método hash
    size_t hashMethod(const std::string& str, size_t index = 0) const {    //genera índice a partir de clave
        if (index >= str.length()) {
            return 0;
        }
        size_t claveActual = (size_t)str[index];

        return claveActual + hashMethod(str, index + 1);
    }

public:
    //constructor de clase HashTable
    HashTable(const size_t TABLE_SIZE = 5) {
        //creando referencia a instancia del vector.
        table = new vector<list<Node>>;
        //inicializando espacios de la tabla.
        for (size_t i = 0; i < TABLE_SIZE; ++i) {
            list<Node> list;
            table->push_back(list);
        }
    }
    //destructor de clase HashTable
    ~HashTable() {
        //vaciando listas de la tabla.
        for (size_t i  = 0; i < table->size(); ++i) {
            table->at(i).clear();
        }
        //liberando memoria de tabla.
        delete table;
    }
    //métodos de clase HashTable.
    void insert(const string& key, T item) {    //para insertar elementos a la tabla.
        //var. para verificar si existe clave.
        bool existe = false;
        //obteniendo código hash.
        size_t index = hashMethod(key) % table->size();
        //recorriendo lista.
        for (Node& node : table->at(index)) {
            //verificamos si la clave ingresada YA existe.
            if (node.key == key) {
                //si existe, reemplazamos su valor.
                node.item = item;
                //actualizamos valor de var. "existe".
                existe = true;
            }
        }

        //verificando en caso NO exista la clave.
        if (!existe) {
            //en caso NO exista, ingresamos en últ. pos de mi lista el elemento.
            table->at(index).push_back(Node(key, item));
            //incrementamos la cant. de elementos.
            ++size;
        }
    }
    T get(const string& key) const {    //para obtener elemento.
        T val = NULL;
        //obteniendo código hash.
        size_t index =  hashMethod(key) % table->size();

        //buscando clave en la lista correspondiente al índice
        for (Node& node : table->at(index)) {
            //verificamos si la clave ingresada YA existe.
            if (node.key == key) {
                //actualizamos valor de var. "existe".
                val = node.item;
            }
        }

        return val;
    }
    void erase(const string& key) {    //para eliminar elemento.
        //obteniendo código hash.
        size_t index =  hashMethod(key) % table->size();

        //recorriendo lista del índice "index" correspondiente.
        for (auto it = table->at(index).begin(); it != table->at(index).end(); ++it) {
            //buscando clave en la lista correspondiente al índice.
            if (it->key == key) {
                //borrar el par clave-valor de la lista
                table->at(index).erase(it);
                return;
            }
        }
    }
    void iterator(function<void(T)> func) {    //para iterar los elementos de cada lista.
        //recorriendo tabla.
        for (int i = 0; i < table->size(); ++i) {
            //verificando que la lista en "i" NO este vacia.
            if (!table->at(i).empty()) {
                //recorriendo contenido de la lista.
                for (const Node& _iter : table->at(i)) {
                    func(_iter.item);
                }
                if (i < table->size() - 1) {
                    std::cout << "\n";
                }
            }
        }
    }
private:
    //atributos de clase HashTable
    vector<list<Node>>* table;       //tabla hash.
    size_t size;                             //cant. elementos.
};

#endif //__HASHTABLE_H__