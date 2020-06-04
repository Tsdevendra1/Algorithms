//
// Created by Tharuka Devendra on 04/06/2020.
//

#include "Trie.h"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <numeric>
#include <sstream>
using namespace std;

int ALPHABET_SIZE = 26;

class TrieNode {
public:
    bool isEndOfWord = false;
    vector<TrieNode*> children;
    TrieNode(): children(ALPHABET_SIZE, nullptr) {}
};

class Trie {
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string &word) {
        TrieNode *currentNode = this->root;
        for (auto letter: word) {
            int letterIndex = letter - 'a';
            if (!currentNode->children[letterIndex]) {
                currentNode->children[letterIndex] = new TrieNode();
            }
            currentNode = currentNode->children[letterIndex];
        }

        currentNode->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode *currentNode = this->root;
        for (auto letter: word) {
            int letterIndex = letter - 'a';
            if (currentNode) {
                currentNode = currentNode->children[letterIndex];
            } else {
                break;
            }
        }

        return currentNode != nullptr && currentNode->isEndOfWord;
    }
};

void testTrie(){
    auto trie = new Trie();
    vector<string> keys = {"the","a","there","anaswe","any",
            "by","their"};
    for (auto word: keys) {
        trie->insert(word);
    }

    cout << trie->search("the") << endl;
    cout << trie->search("these") << endl;
    cout << trie->search("their") << endl;
    cout << trie->search("thaw") << endl;
}
