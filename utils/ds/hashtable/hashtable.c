#pragma once
#include "./hashtable.h"
#define INITIAL_CAPACITY 16  // must not be zero

HashTable* HashTable_create(void) {
    // Allocate space for hash table struct.
    HashTable* table = malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // Allocate (zero'd) space for entry buckets.
    table->entries = calloc(table->capacity, sizeof(HashTable_entry));
    if (table->entries == NULL) {
        free(table); // error, free table before we return!
        return NULL;
    }
    return table;
}

void HashTable_destroy(HashTable* table) {
    // First free allocated keys.
    for (size_t i = 0; i < table->capacity; i++) {
        free((void*)table->entries[i].key);
    }

    // Then free entries array and table itself.
    free(table->entries);
    free(table);
}
