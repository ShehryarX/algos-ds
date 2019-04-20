/*
    Hash table with closed hashing
*/

#include <iostream>
#include <string>
#include <vector>

#define SPACE_OUTPUT std::cout << "---" << std::endl;

struct Node {
    std::string val;
    Node* next;
};

class HashTable {
   private:
    std::vector<Node*> table;
    int hash(std::string val);
    int numBuckets;
    int size;
    Node* createNode(std::string val);

   public:
    HashTable(int K);
    ~HashTable();
    void insert(std::string val);
    bool remove(std::string val);
    void print();
};

int HashTable::hash(std::string val) {
    int hsh = 0;
    for (auto& c : val) {
        hsh += c;
    }
    return hsh % numBuckets;
}

Node* HashTable::createNode(std::string val) {
    Node* n = new Node;
    n->next = nullptr;
    n->val = val;
    return n;
}

HashTable::HashTable(int K) : numBuckets(K), size(0) { table.resize(K); }

HashTable::~HashTable() {
    for (int i = 0; i < numBuckets; i++) {
        if (nullptr != table[i]) {
            Node* curr = table[i];
            while (nullptr != curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
}

void HashTable::insert(std::string val) {
    int slot = hash(val);
    Node* n = createNode(val);
    n->next = table[slot];
    table[slot] = n;
    size++;
}

bool HashTable::remove(std::string val) {
    int slot = hash(val);

    Node* curr = table[slot];
    if (nullptr == table[slot]) return false;

    if (curr->val == val) {
        table[slot] = curr->next;
        delete curr;
    } else {
        while (nullptr != curr->next) {
            if (curr->next->val == val) {
                curr->next = curr->next->next;
                delete curr->next;
            }
            curr = curr->next;
        }
    }

    return true;
    size--;
}

void HashTable::print() {
    for (int i = 0; i < table.size(); i++) {
        Node* curr = table[i];
        if (nullptr == curr) continue;
        std::cout << "[" << i << "] ";
        while (nullptr != curr) {
            std::cout << curr->val << ", ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

int main() {
    HashTable ht(100);
    ht.insert("Shehryar");
    ht.insert("this");
    ht.insert("is");
    ht.insert("a");
    ht.insert("bad");
    ht.insert("hash");
    ht.insert("fcn");
    ht.print();

    SPACE_OUTPUT

    ht.remove("nothing");
    ht.remove("Shehryar");
    ht.remove("function");
    ht.print();
}
