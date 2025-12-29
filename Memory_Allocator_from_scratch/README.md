# Custom Memory Allocator

 implementation of standard C memory allocation functions (`malloc`, `free`, `realloc`, `calloc`) built from scratch. This project replaces the system's default memory allocator with a custom implementation managed via a linked list of memory blocks.

## 🧠 What I Learned

Building this project provided deep insights into low-level systems programming:

* **Memory Architecture:** How computers manage memory layout (Stack vs. Heap vs. Data Segments).
* **Heap Management:** Understanding how the heap grows and shrinks using system calls (`sbrk`) and how the Operating System creates the illusion of infinite memory.
* **Allocator Internals:** How standard functions like `malloc` and `free` actually work under the hood using block splitting, coalescing, and metadata headers.
* **Pointer Arithmetic:** mastered complex pointer manipulation, specifically working with `void*`, type casting, and calculating memory offsets (e.g., accessing block headers via `(header_t*)block - 1`).
* **Library Interposition:** Learned how to use `LD_PRELOAD` to "inject" a custom shared library into a running process, overriding system default functions.

## 🛠️ Features

* **`malloc(size_t size)`**: Allocates memory by finding a free block or extending the heap.
* **`free(void *block)`**: Marks a block as free for reuse or returns memory to the OS if it's at the end of the heap.
* **`calloc(size_t num, size_t nsize)`**: Allocates memory for an array and initializes all bytes to zero.
* **`realloc(void *block, size_t size)`**: Resizes an existing memory block, moving data to a new location if necessary.
* **Thread Safety**: Uses `pthread_mutex` to ensure safe access to the global linked list in multi-threaded environments.

## 🚀 Getting Started

### Prerequisites

* **Linux** or **WSL (Windows Subsystem for Linux)**: Recommended environment.
* **macOS**: Supported (with `DYLD_INSERT_LIBRARIES`), but system binaries like `ls` are protected by SIP.
* **Windows (Native)**: Not supported directly because this project relies on `unistd.h` and `sbrk()`, which are POSIX-specific system calls. **Use WSL.**

### 1. Clone the Repository

```bash
git clone [https://github.com/YOUR_USERNAME/Memory_Allocator.git](https://github.com/YOUR_USERNAME/Memory_Allocator.git)

cd Memory_Allocator
```
### 2. Compile the Library
We compile the code as a Shared Object (.so) file so it can be loaded dynamically at runtime.

For Linux / WSL:
```Bash
gcc -o memalloc.so -fPIC -shared memalloc.c -pthread
```
* -fPIC: Generate Position Independent Code (required for shared libraries).

* -shared: Create a shared library.

* -pthread: Link the pthread library for mutex locks.

For macOS:

```Bash

gcc -o memalloc.so -fPIC -shared memalloc.c -pthread
```
(Note: macOS typically uses .dylib, but .so works for this testing purpose).

## 🧪 How to Run & Test
You don't need to change your code to use this allocator! We use the Library Interposition technique to force the system to use our allocator instead of the default one.

### The "One-Shot" Test
Run any standard command (like ls) using your allocator:

```Bash

LD_PRELOAD=$PWD/memalloc.so ls
```
If you added debug `write()` statements in your code, you will see your messages appear alongside the file listing.

## Testing with a Custom Program

This repository includes a `test.c` file to verify that `malloc` and `free` are working correctly in a clean environment.

1. Compile the test program (normally, without linking the library):

```Bash

gcc -o test test.c
```
2. Run it with your custom allocator injected:

```Bash

LD_PRELOAD=$PWD/memalloc.so ./test
```
If successful, the program should run using your custom logic instead of the system default.

## Note for macOS Users
On macOS, `LD_PRELOAD` is replaced by `DYLD_INSERT_LIBRARIES`. Also, macOS has System Integrity Protection (SIP) which prevents injecting libraries into system binaries (like `ls`). You must test using the compiled `test` binary:

```Bash

DYLD_INSERT_LIBRARIES=$PWD/memalloc.so ./test
```