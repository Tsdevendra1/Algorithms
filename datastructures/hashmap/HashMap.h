//
// Created by Tharuka Devendra on 18/05/2020.
//

#ifndef ALGORITHMS_HASHMAP_H
#define ALGORITHMS_HASHMAP_H


#include <vector>

class HashMap {
public:
    explicit HashMap(int storageSize): storageSize(storageSize), storage(std::vector<int>(storageSize)){};
    void remove(int value);
    void insert(int value);
private:
    std::vector<int> storage;
    int storageSize;
    int hashFunction(int value);
    float loadFactor = 0;

};


#endif //ALGORITHMS_HASHMAP_H
