# Custom Hashmap Implementation in C

A high-performance Hash Table (Hashmap) data structure built entirely from scratch in C. This project explores the internal mechanics of key-value stores, focusing on memory management, collision resolution, and hashing algorithms without relying on high-level standard libraries.

## 🚀 Features

* **Collision Resolution:** Implements **Open Addressing** using **Double Hashing** to handle collisions and minimize clustering.
* **Dynamic Resizing:** Automatically expands or shrinks the memory footprint based on the load factor (resizes up at >70% load, down at <10%).
* **Custom Hash Function:** Uses a polynomial rolling hash algorithm using prime numbers to ensure uniform distribution of keys.
* **Prime-Sized Buckets:** Automatically calculates the next prime number for table sizes to further reduce collision probability.
* **CRUD Operations:** Full support for `Insert`, `Search`, and `Delete` (using "tombstone" marking for deleted items).

---

## 🧠 What I Learned & Mastered

Building a hashmap is the ultimate test of understanding pointers and algorithmic efficiency.

### 1. Hashmap Theory & Algorithms
* **Collision Handling:** Learned that collisions are inevitable and implemented **Double Hashing** to resolve them. Unlike simple Linear Probing, this method uses a secondary hash function to calculate the step size, ensuring keys are spread uniformly across the array.
* **Hash Functions:** Mastered the math behind converting string keys into integer indices using polynomial rolling hashes (`hash = hash * a + char`), minimizing collisions for similar strings.
* **Prime Numbers:** Understood why hash table sizes should be prime numbers—it reduces the chance that the step size shares a common factor with the table size, which would otherwise result in infinite loops during probing.

### 2. Advanced Memory Management
* **Double Pointers:** Mastered the concept of `ht_item**` (a pointer to a pointer) to create dynamic arrays of item pointers, rather than storing large structs directly in the array.
* **Dynamic Re-allocation:** Implemented a resizing algorithm that doesn't just `realloc`, but creates a completely new, larger table and re-hashes every existing item into it to maintain lookup efficiency.
* **String Duplication:** Learned to safely copy string keys using `strdup` to ensure the hashmap owns its data, preventing errors if the original string variable is modified elsewhere.


---

## 🛠️ How to Build & Run

### Linux / macOS
```bash
gcc main.c hash_table.c prime.c -o hashmap -Wall -Wextra -lm
```

(Note: -lm links the math library required for hashing algorithms)

### Windows (MinGW / PowerShell) ✅

```Bash

gcc main.c hash_table.c prime.c -o hashmap.exe -Wall -Wextra
```