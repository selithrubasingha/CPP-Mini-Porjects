// main.c
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "prime.h"

// Helper function to print search results
void print_search_result(ht_hash_table* ht, const char* key) {
    const char* value = ht_search(ht, key);
    if (value != NULL) {
        printf("Search for '%s': Found -> %s\n", key, value);
    } else {
        printf("Search for '%s': Not Found\n", key);
    }
}

int main() {
    printf("--- Hash Map Implementation Test ---\n");

    // Initialize the hash table
    ht_hash_table* ht = ht_new();
    
    // --- 1. Basic Insertion and Search ---
    printf("\n--- 1. Basic Operations ---\n");
    ht_insert(ht, "apple", "red");
    ht_insert(ht, "banana", "yellow");
    ht_insert(ht, "grape", "purple");

    print_search_result(ht, "apple");    // Should find "red"
    print_search_result(ht, "banana");   // Should find "yellow"
    print_search_result(ht, "orange");   // Should be Not Found

    // --- 2. Testing Updates (Insertion with Existing Key) ---
    printf("\n--- 2. Testing Update ---\n");
    ht_insert(ht, "apple", "green"); // Update "apple" value
    print_search_result(ht, "apple");    // Should find the new value "green"
    
    // --- 3. Testing Deletion ---
    printf("\n--- 3. Testing Deletion ---\n");
    ht_delete(ht, "banana");
    print_search_result(ht, "banana");   // Should be Not Found
    print_search_result(ht, "grape");    // Should still be found
    

    return 0;
}
