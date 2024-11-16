#pragma once
#include "../../kernel_utils.c"
typedef struct HashTable HashTable;

HashTable* HashTable_create(void);

void HashTable_destroy(HashTable* table);

void* HashTable_get(HashTable* table, const char* key);
const char* HashTable_set(HashTable* table, const char* key, void* value);

size_t HashTable_length(HashTable* table);

// Hash table iterator: create with HashTable_iterator, iterate with HashTable_next.
typedef struct {
    const char* key;  // current key
    void* value;      // current value

    // Don't use these fields directly.
    HashTable* _table;       // reference to hash table being iterated
    size_t _index;    // current index into HashTable._entries
} HashTableIterator;

HashTableIterator HashTable_iterator(HashTable* table);

bool HashTable_next(HashTableIterator* it);

typedef struct {
    const char* key;  // key is NULL if this slot is empty
    void* value;
} HashTable_entry;

// Hash table structure: create with HashTable_create, free with HashTable_destroy.
struct HashTable {
    HashTable_entry* entries;  // hash slots
    size_t capacity;    // size of _entries array
    size_t length;      // number of items in hash table
};