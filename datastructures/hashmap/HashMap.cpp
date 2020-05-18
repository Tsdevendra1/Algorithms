//
// Created by Tharuka Devendra on 18/05/2020.
//

#include "HashMap.h"

void HashMap::insert(int value) {

    loadFactor = ((float)storage.size()/(float)storageSize);
}

void HashMap::remove(int value) {

}

int HashMap::hashFunction(int value) {
    return (value % storageSize);
}

