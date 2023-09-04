#include <iostream>
#include "HashTable.h"
int main() {
    HashTable<int>* hashTable = new HashTable<int>(4);
    hashTable->insert("Gonzalo", 20);
    hashTable->insert("Luciana", 18);
    hashTable->insert("Miguel", 58);
    hashTable->insert("Maria", 17);
    hashTable->insert("Carlos", 21);
    hashTable->insert("Jose", 24);
    hashTable->insert("Bustinza", 25);
    hashTable->insert("Luana", 22);
    hashTable->insert("Zubieta", 38);

    hashTable->erase("Luana");

    hashTable->iterator([](int v)->void { std::cout << v << " ";});

    std::cout << "\nObteniendo valor: " <<   hashTable->get("Mer");
    return 0;
}