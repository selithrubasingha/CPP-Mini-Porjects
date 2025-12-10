#ifndef HASH_TABLE_H // <-- Header guards are essential!
#define HASH_TABLE_H
#include <stddef.h> // Include for size_t, which is good practice

// --- Constants ---
#define HT_INITIAL_BASE_SIZE 53

//this is not the normal way of defining structs, the typedef word is used
//so now we won't need to write struct this and struct that when making a specific struct
//simply we don't need to write "struct" word often
typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int base_size;
    int size;
    int count;
    //pointer to a pointer
    ht_item** items;
} ht_hash_table;

//double pointers are used in multidimensional arrays
//"he_hash_table" contains the adress to a place where all the other adresses of hit_items are sotres!

// Inside hash_table.h


// --- Public Function Declarations ---

// 1. Creation and Deletion
ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table* ht);

// 2. Core Operations
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
// IMPORTANT: Corrected to return const char* as intended in ht_search body
const char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);

// The resizing helper functions are usually internal (static)
// and do not need a declaration here, unless you want them accessible externally.

#endif // HASH_TABLE_H