/*
    Hash table with open hashing
*/

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#define SPACE_OUTPUT std::cout << "---" << std::endl;
#define MAX_BUCKETS 10000

enum Status {
    EMPTY,
    ACTIVE,
    ZOMBIE,
};

struct Node {
    std::string val;
    Status status;
};

class HashTable {
   private:
    std::vector<Node> table;
    int hash(std::string str);
    int activeElements;
    int getSlot(std::string val);

   public:
    HashTable();
    virtual ~HashTable();
    void insert(std::string val);
    bool has(std::string val);
    void remove(std::string val);
    void print();
};

HashTable::HashTable() {
    table.resize(MAX_BUCKETS);
    activeElements = 0;

    for (int i = 0; i < table.size(); i++) {
        table[i].status = EMPTY;
    }
}

HashTable::~HashTable() {}

// naive hash
int HashTable::hash(std::string str) {
    int hsh = 0;
    for (auto &c : str) {
        hsh += c;
    }
    return hsh % MAX_BUCKETS;
}

int HashTable::getSlot(std::string val) {
    int slot = hash(val);

    for (int i = 0; i < MAX_BUCKETS; i++) {
        if (EMPTY == table[slot].status) {
            return -1;
        } else if (ACTIVE == table[slot].status && val == table[slot].val) {
            return slot;
        }

        slot = (slot + 1) % MAX_BUCKETS;
    }

    return -1;
}

void HashTable::insert(std::string val) {
    assert(activeElements < MAX_BUCKETS);

    int slot = hash(val);

    while (ACTIVE == table[slot].status) {
        slot = (slot + 1) % MAX_BUCKETS;
    }

    table[slot].status = ACTIVE;
    table[slot].val = val;
    activeElements++;
}

bool HashTable::has(std::string val) { return getSlot(val) != -1; }

void HashTable::remove(std::string val) {
    int slot = getSlot(val);
    if (-1 == slot) return;
    table[slot].status = ZOMBIE;
    activeElements--;
}

void HashTable::print() {
    for (int i = 0; i < MAX_BUCKETS; i++) {
        if (ACTIVE == table[i].status) {
            std::cout << "[" << i << "]: " << table[i].val << std::endl;
        }
    }
}

int main() {
    HashTable ht;
    ht.insert("Hello");
    ht.insert("Macbook");
    ht.insert("Starbucks");
    ht.insert("Bottle");
    ht.insert("Phone");
    ht.insert("Bitcoin");
    ht.print();

    SPACE_OUTPUT
    ht.remove("Hello");
    ht.remove("Starbucks");
    ht.remove("Nothing");
    ht.print();

    return 0;
}
