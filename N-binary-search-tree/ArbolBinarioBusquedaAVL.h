//
// Created by Gonzalo Quedena on 01/07/2023.
//

#ifndef __ARBOL_BINARIO_BUSQUEDA_AVL_H__
#define __ARBOL_BINARIO_BUSQUEDA_AVL_H__

#include <cstdlib>
#include <functional>
#include <algorithm>

using std::function;
using std::max;

//implementación de clase Arbol Binario de Busqueda
template<class T>
class ArbolBinarioBusquedaAVL {

private:
    //enlazando clase Node.
    class Node {

    public:
        //atributos de clase Node.
        Node* right;        //nodo derecho.
        Node* left;         //nodo izquierdo.
        size_t height;      //altura.
        T item;             //elemento almacenado.

        //constructor de clase Node.
        Node(T item = NULL)
            : item(item), height(1) {

            right = left = nullptr;
        }
    };
    //métodos de clase PRIVADOS.
    size_t __getNodeHeight(Node* root) {  //para obtener altura de un nodo.

        if (root == nullptr) {
            return 0;
        }
        else {
            return root->height;
        }
    }
    void __updateHeight(Node*& root) {  //para actualizar altura de un nodo.

        //obteniendo altura por su izquierda.
        size_t leftH = __getNodeHeight(root->left);
        //obteniendo altura por su derecha.
        size_t rightH = __getNodeHeight(root->right);

        //actualizando la altura del nodo.
        root->height  = 1 + max(leftH, rightH);
    }
    Node* __rotateRight(Node*& root) { //para realizar rotación a la derecha.

        Node* new_root = root->left;
        Node* right_subTree = new_root->right;

        //realizando rotación.
        new_root->right = root;
        root->left = right_subTree;

        //actualizando alturas de los nodos afectados.
        __updateHeight(root);
        __updateHeight(new_root);

        //retornando nueva raíz.
        return new_root;
    }
    Node* __rotateLeft(Node*& root) { //para realizar rotación a la izquierda.

        //obteniendo nodo derecho de la raíz.
        Node* new_root = root->right;
        //obteniendo nodo izquierdo de "new_root".
        Node* left_subTree = new_root->left;

        //realizando rotación.
        new_root->left = root;
        root->right = left_subTree;

        //actualizando alturas de los nodos afectados.
        __updateHeight(root);
        __updateHeight(new_root);

        //retornando nuevo nodo.
        return new_root;
    }
    short __getBalance(Node* root) { //para obtener factor de equilibrio de nodo.

        if (root == nullptr) {
            return 0;
        }
        else {
            return __getNodeHeight(root->left) - __getNodeHeight(root->right);
        }
    }
    Node* __insert(Node*& root, T item) {  //para insertar un elemento al árbol.

        //verificando si llegamos al límite del árbol, según valor del elemento.
        if (root == nullptr) {
            //agregando nuevo Node(hoja) al árbol.
            return new Node(item);
        }
        //verificando elemento menor.
        else if (comparation(item, root->item)) { // <
            //llamada recursiva hacia la hoja izq. del nodo rama.
            root->left = __insert(root->left, item);
        }
        //verificando elemento mayor.
        else if (comparation(root->item, item)) { // >
            //llamada recursiva hacia la hoja der. del nodo rama.
            root->right = __insert(root->right, item);
        }
        //valor duplicado, NO permitido.
        else root;

        //actualizando altura del nodo actual.
        __updateHeight(root);

        //obteniendo factor de balance/equilibrio del nodo actual.
        short balanceFactor = __getBalance(root);

        //1er caso: desbalance hacia la izquierda-izquierda (LEFT-LEFT).
        if (balanceFactor > 1 && comparation(item, root->left->item)) {
            return __rotateRight(root);
        }
        //2do caso: desbalance hacia la derecha-derecha (RIGHT-RIGHT).
        else if (balanceFactor < -1 && comparation(root->right->item, item)){
            return __rotateLeft(root);
        }
        //3er caso: desbalance hacia la izquierda-derecha (LEFT-RIGHT).
        else if (balanceFactor > 1 && comparation(root->left->item, item)) {
            root->left = __rotateLeft(root->left);
            return __rotateRight(root);
        }
        //4to caso: desbalance hacia la derecha-izquierda (RIGHT-LEFT).
        else if (balanceFactor < - 1 && comparation(item, root->right->item)) {
            root->right = __rotateRight(root->right);
            return __rotateLeft(root);
        }

        //en caso no se necesite rotación, retornamos directamente la raíz.
        return root;
    }
    Node* __erase(Node*& root, T item) {  //para borrar un elemento del árbol.

        //verificando si raíz está vacía.
        if (root == nullptr) {
            return root;
        }
        //moviendo root a elemento por la izquierda.
        else if (comparation(item, root->item)) {
            root->left = __erase(root->left, item);
        }
        //moviendo root a elemento por la derecha.
        else if (comparation(root->item, item)) {
            root->right = __erase(root->right, item);
        }
        //en caso encontremos el elemento.
        else {

            //evaluando si la der. O izq. del nodo son nullptr.
            if (root->left == nullptr || root->right == nullptr) {

                //tomamos aquel que NO sea nullptr.
                Node* current = (root->left != nullptr) ? root->left : root->right;

                //1er caso: raiz sin hijos.
                if (current == nullptr) {
                    current = root;
                    root = nullptr;
                }
                //2do caso: raiz con UN hijo.
                else {
                    root = current;
                }

                delete current;
            }
            else {
                //3er caso: nodo tiene dos hijos.
                Node* current = __getMinValue(root->right);
                root->item = current->item;
                root->right = __erase(root->right, current->item);
            }
        }

        //evaluando si el nodo raíz(árbol), quedó vacío.
        if (root == nullptr) {
            //en ese caso, retornamos la raíz directamente.
            return root;
        }
        //si no quedó vacío, evaluamos si hay necesidad de rotar.
        else {

            //obteniendo factor de balanceo del nodo.
            short balanceFactor = __getBalance(root);

            //verificando la rotación a realizar.
            if (balanceFactor > 1 && __getBalance(root->left) >= 0) {
                return __rotateRight(root);
            }
            if (balanceFactor > 1 && __getBalance(root->left) < 0) {
                root->left = __rotateLeft(root->left);
                return __rotateRight(root);
            }
            if (balanceFactor < -1 && __getBalance(root->right) <= 0) {
                return __rotateLeft(root);
            }
            if (balanceFactor < -1 && __getBalance(root->right) > 0) {
                root->right = __rotateRight(root->right);
                return __rotateLeft(root);
            }
        }

        //en caso no realice ninguna rotación, retornamos la raíz directamente.
        return root;
    }
    size_t __size(Node* root) {  //para obtener la cant. de nodos del árbol.

        //verificanodo que la raíz en la que se encuentre NO sea nullptr.
        if (root == nullptr) {
            return 0;
        }
        //sino, retornamos la suma de todos los nodos retornamos por la izq. y der.
        else {
            return 1 + __size(root->left) + __size(root->right);
        }
    }
    size_t __treeLevel(Node* root) {

        //evaluando que la raíz no sea nullptr.
        if (root != nullptr) {
            //en ese caso, obtenemos el acumulado de los nodos contados por la izq.
            size_t izq = __treeLevel(root->left) + 1;
            //en ese caso, obtenemos el acumulado de los nodos contados por la der.
            size_t der = __treeLevel(root->right) + 1;

            //retornamos el mayor de ambos.
            return ((izq > der) ? izq : der);
        }

        //valor de retorno en caso no existan valores.
        return -1;
    }

    Node* __getMinValue(Node* root) {

        //verificando si la raíz es nullptr
        //O si llegamos al límite del recorrido por la izq.
        if (root == nullptr || root->left == nullptr) {
            //en ese caso retornamos
            return root;
        }

        //en caso NO estemos en el límite, seguimos buscando...
        return __getMinValue(root->left);
    }
    Node* __getMaxValue(Node* node) {

        //verificando si la raíz es nullptr
        //O si llegamos al límite del recorrido por la der.
        if (node == nullptr || node->right == nullptr) {
            return root;
        }

        //en caso NO estemos en el límite, seguimos buscando...
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
        else return root;
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
    void __postOrder(Node* root) {  //para recorrer elementos del árbol en "postOrder".

        //verificanodo que la raíz en la que se encuentre NO sea nullptr.
        if (root != nullptr) {
            __postOrder(root->left);
            __postOrder(root->right);
            print(root->item);
        }
    }
    void __preOrder(Node* root) {  //para recorrer elementos del árbol en "preOrder".

        //verificar que la raíz en la que se encuentre No sea nullptr.
        if (root != nullptr) {
            print(root->item);
            __preOrder(root->left);
            __preOrder(root->right);
        }
    }

public:
    //constructor de clase Arbol Binario Busqueda.
    ArbolBinarioBusquedaAVL(function<void(T)> proceso, function<bool(T, T)> criterio)
        : root(nullptr) {
        //inicializando criterio de proceso(impresión).
        this->print = proceso;
        //inicializando criterio de comparación.
        this->comparation = criterio;
    }

    //métodos de clase PÚBLICOS.
    void insert(T item) {  //para insertar un elemento.
        root = this->__insert(root, item);
    }
    void erase(T item) {  //para eliminar un elemento.
        root = this->__erase(root, item);
    }
    size_t size() {  //para obtener cant. de nodos.
        return this->__size(root);
    }
    size_t treeLevel() {  //para obtener nivel de árbol.
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
    T getMinValue() {  //para obtener valor mín. del árbol.
        return this->__getMinValue(root)->item;
    }
    T getMaxValue() {  //para obtener valor máx. del árbol.
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

#endif //__ARBOL_BINARIO_BUSQUEDA_AVL_H__
