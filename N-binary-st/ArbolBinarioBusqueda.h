//
// Created by Gonzalo Quedena on 30/06/2023.
//

#ifndef __ARBOL_BINARIO_BUSQUEDA_H__
#define __ARBOL_BINARIO_BUSQUEDA_H__

#include <cstdlib>
#include <functional>

using std::function;
using std::max;

//implementación de clase Arbol Binario de Busqueda
template<class T>
class ArbolBinarioBusqueda {

private:
    //enlazando clase Node.
    class Node {

    public:
        //atributos de clase Node.
        Node* right;        //nodo derecho.
        Node* left;         //nodo izquierdo.
        T item;             //elemento almacenado.

        //constructor de clase Node.
        Node(T item=NULL)
            : item(item), right(nullptr), left(nullptr) {
        }
    };

    //métodos de clase PRIVADOS.
    void __insert(Node*& root, T item) {  //para insertar un elemento al árbol.

        //verificando si llegamos al límite del árbol, según valor del elemento.
        if (root == nullptr) {
            //agregando nuevo Node(hoja) al árbol.
            root = new Node(item);
        }
        //verificando elemento menor.
        else if (comparation(item, root->item)) { // <
            //llamada recursiva hacia la hoja izq. del nodo rama.
            __insert(root->left, item);
        }
        //verificando elemento mayor.
        else if(comparation(root->item, item)) { // >
            //llamada recursiva hacia la hoja der. del nodo rama.
            __insert(root->right, item);
        }
    }
    void __erase(Node*& root, T item) {

        //verificando si árbol vacío.
        if (root == nullptr)return;
        
        if (comparation(item, root->item)) {
            __erase(root->left, item);
        }
        else if (comparation(root->item, item)) {
            __erase(root->right, item);
        }
        //si se encontró el nodo a eliminar.
        else {

            //1er caso: cuando el nodo a eliminar no tiene hijos o es una hoja
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            }
            //2do:cuando el nodo a eliminar tiene solo un hijo
            else if (root->left == nullptr) {
                Node* temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root;
                root = root->left;
                delete temp;
            }
            //3er caso: cuando el nodo a eliminar tiene dos hijos
            else {
                Node* minNode = __getMinValue(root->right);
                root->item = minNode->item;
                __erase(root->right, minNode->item);
            }
        }
    }
    size_t __size(Node* root) {  //para obtener la cant. de nodos del árbol.

        //verificanodo que la raíz en la que se encuentre NO sea nullptr.
        if (root == nullptr) {
            return 0;
        }
        else {
            return 1 + __size(root->left) + __size(root->right);
        }
    }
    size_t __treeLevel(Node* root) {

        if (root != nullptr) {
            size_t izq = __treeLevel(root->left) + 1;
            size_t der = __treeLevel(root->right) + 1;

            return ((izq > der) ? izq : der);
        }

        return -1;
    }

    Node* __getMinValue(Node* node) {

        if (node == nullptr) {
            return nullptr;
        }
        else if (node->left == nullptr) {
            return node;
        }

        return __getMinValue(node->left);
    }
    Node* __getMaxValue(Node* node) {

        if (node == nullptr) {
            return nullptr;
        }
        else if (node->right == nullptr) {
            return node;
        }

        return __getMaxValue(node->right);
    }
    Node* __get(Node* root, T item) {  //para obtener un elemento del árbol

        //verificando si árbol vacío.
        if (root == nullptr)return nullptr;

        //verificando elemento menor.
        else if (comparation(item, root->item)) {
            return __get(root->left, item);
        }
        //verificando elemento mayor.
        else if (comparation(root->item, item)) {
            return __get(root->right, item);
        }
        //si se encontró el nodo a buscar.
        else {
            return root;
        }
    }
    //formas de recorrido.
    void __inOrder(Node* root) {  //para recorrer elementos del árbol en "inOrder".

        //verificanodo que la raíz en la que se encuentre NO sea nullptr.
        if (root != nullptr) {
            __inOrder(root->left);
            print(root->item);
            __inOrder(root->right);
        }
    }
    void __postOrder(Node* root) {  //para recorrer elementos del árbol en "inOrder".

        //verificanodo que la raíz en la que se encuentre NO sea nullptr.
        if (root != nullptr) {
            __postOrder(root->left);
            __postOrder(root->right);
            print(root->item);
        }
    }
    void __preOrder(Node* root) {

        //verificar que la raíz en la que se encuentre No sea nullptr.
        if (root != nullptr) {
            print(root->item);
            __preOrder(root->left);
            __preOrder(root->right);
        }
    }

public:
    //constructor de clase Arbol Binario Busqueda.
    ArbolBinarioBusqueda(function<void(T)> proceso, function<bool(T, T)> criterio)
        : root(nullptr) {
        //inicializando criterio de proceso(impresión).
        this->print = proceso;
        //inicializando criterio de comparación.
        this->comparation = criterio;
    }

    //métodos de clase PÚBLICOS.
    void insert(T item) {  //para insertar un elemento.
        this->__insert(root, item);
    }
    void erase(T item) {
        this->__erase(root, item);
    }
    size_t size() {  //para obtener cant. de nodos.
        return this->__size(root);
    }
    size_t treeLevel() {
        return this->__treeLevel(root);
    }
    T get(T item) {  //para obtener el elemento.

        //obteniendo o NO obteniendo elemento solicitado.
        Node* nI = this->__get(root, item);

        //verificando si se LOGRÓ obtener el elemento.
        if (nI != nullptr) {
            //en ese caso, retornamos el elemento de ese nodo.
            return nI->item;
        }
        else {
            //en caso NO, retornamos NULL.
            return NULL;
        }
    }
    T getMinValue() {
        return this->__getMinValue(root)->item;
    }
    T getMaxValue() {
        return this->__getMaxValue(root)->item;
    }
    //formas de recorrido.
    void inOrder() {
        this->__inOrder(root);
    }
    void postOrder() {
        this->__postOrder(root);
    }
    void preOrder() {
        this->__preOrder(root);
    }


private:
    //atributos de clase Arbol Binario Busqueda.
    Node* root;    //nodo raiz del árbol.

    typedef function<bool(T, T)> comp; //criterio de comparación para elementos
    comp comparation;

    typedef function<void(T)> process; //criterio de proceso.
    process print;
};

#endif //__ARBOL_BINARIO_BUSQUEDA_H__
