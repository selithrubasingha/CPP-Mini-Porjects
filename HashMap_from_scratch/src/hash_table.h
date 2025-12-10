#ifndef HASH_TABLE_H // <-- Header guards are essential!
#define HASH_TABLE_H

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

// 1. Declaration for creating the hash table
ht_hash_table* ht_new();

// 2. Declaration for deleting the hash table
void ht_del_hash_table(ht_hash_table* ht);

#endif // HASH_TABLE_H