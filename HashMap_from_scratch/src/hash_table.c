// hash_table.c
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#define HT_PRIME_1 151
#define HT_PRIME_2 163
#define HT_INITIAL_BASE_SIZE 53
static ht_item HT_DELETED_ITEM = {NULL, NULL};

//const char* k means: "A pointer to the beginning of a string representing the key."
//const char* v means: "A pointer to the beginning of a string representing the value."
static ht_item* ht_new_item(const char* k, const char* v) {
    //malloc--> memory allocation | calcs the no of bytes needed for ht_item struct
    ht_item* i = malloc(sizeof(ht_item));

    //strup | string duplicate | duplicates the string passed to it and returns a pointer to the duplicated string
    i->key = strdup(k);
    i->value = strdup(v);

    //returns the adress 
    return i;
}


// ht_hash_table* ht_new() {
//     //this is the adress , not the actual struct
//     ht_hash_table* ht = malloc(sizeof(ht_hash_table));

//     ht->size = 53;
//     ht->count = 0;
//     //size_t is a special type of integer! this tells the coompiler
//     //"Treat the integer value in ht->size as a size_t value for this function call."
//     //53* 4bytes for the adress list of items!
//     ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
//     return ht;
// }


static void ht_del_item(ht_item* i) {
    //undoing what ever malloc did and strdup did , if not this will call memory leaks
    free(i->key);
    free(i->value);
    free(i);
}


void ht_del_hash_table(ht_hash_table* ht) {
    //this items is a adress to where a bunch of other adresses are stored
    // in c , this bunch of adresses is treated as an array
    //so we can use array syntax! items[i]
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    //after all the adresses in the bunch is freed , you need to free the bunch itself
    free(ht->items);
    //and free the strcut as well
    free(ht);
}

//why do we hash?? hashing produces a random integer for the certain string , 
//with these int , we have the power of SUPER FAST LOOPUP times ,cause strings are slower than ints
static int ht_hash(const char* s , const int a,const int m ){
    long hash = 0;
    //strlrn checks the length of the string s
    const int len_s = strlen(s);
    //calculates a value that is somewhat random based on the string s
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    //the somewhat random value is between 0 and m-1 (53 in this casee)
    return (int)hash;
}
//it is inevitable that the same hash value be in 2 or more different strings
//so in the saem hash(bucket) there may be multiple items


//double hashing is the way to resolve collision conflicts, it won't reduce conflicts , 
//but it will uniformly spread the hash inside the 53 buckets
static int ht_get_hash(const char* s , const int num_buckets,const int attempt){
    //some random prime number definitions at the top of the file
    const int hash_a = ht_hash(s,HT_PRIME_1,num_buckets);
    const int hash_b = ht_hash(s,HT_PRIME_2,num_buckets);
    //if collision=0 ,then it isonly hashed one time.
    //but if it collides, then the second part will kick in and make a hash somewhat far away fromthe` first one.
    //the (hash_b + 1) is to avoid getting a zero value for hash_b 
    //and num_buckets modulus to make sure it stays within the bounds of the array
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

//insert key value pair into the hash table
void ht_insert(ht_hash_table* ht,const char* key , const char* value){
    //the resize logic(came in later)
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    //makes an new item
    ht_item* item = ht_new_item(key,value);
    //generates a hash and checks if prev data is there (collision)
    int index = ht_get_hash(item->key,ht->size,0);
    ht_item* cur_item = ht->items[index];

    //this while loop activates only when there is a collision
    int i=1;
    while (cur_item != NULL ) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        //we jump randomly here and there until we find an emtpy bucket
        index = ht_get_hash(item->key,ht->size,i);
        cur_item = ht->items[index];
        i++;
    }

    //finally assigning the item to the hash table
    ht->items[index]=item;
    ht->count++;
}

// hash_table.c
void ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        // Check if the keys match (by jumping around using double hashing)
        //strcmp | sting compare | compares two strings and returns 0 if they are equal
        //strcmp--> (-)value if str1 < str2 | 0 if str1 == str2 | (+)value if str1 > str2 ALPHABETICALLY
        if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                // Key found, you can process the item here
                return item->value ;
            }

        }
            index = ht_get_hash(item->key, ht->size, i);
            item = ht->items[index];
            i++;
        
    } 
    // Key not found
    return NULL;
}

// hash_table.c



void ht_delete(ht_hash_table* ht, const char* key) {
    //the scale down logic
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    //does the saem key finding loopy thing
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {

        //if the item i am checking is not deleted...
        if (item != &HT_DELETED_ITEM) {
            //is this IS the key i am looking for ...
            if (strcmp(item->key, key) == 0) {
                //delete (free all the memory) for the item 
                ht_del_item(item);
                //but the adress in the bucket remains the same , just point it to the special deleted item
                ht->items[index] = &HT_DELETED_ITEM;
                ht->count--;
                return;

            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    //decrement the count too

}

// hash_table.c
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->base_size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc((size_t)ht->base_size, sizeof(ht_item*));
    return ht;
}


ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

//what happeens inside this mehtod? 
// we create a new has_table new_ht WITH A NEW SIZE, copy everything into it from the prev ht
//then we new_ht to ht and vice versa , we used the temporary new_ht to remodify the ht with a new size!!
static void ht_resize(ht_hash_table* ht , int base_size){
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    //copying the items to nre_ht
    for(int i=0;i<ht->size;i++){
        ht_item* item = ht->items[i];
        if(item != NULL && item != &HT_DELETED_ITEM){
            ht_insert(new_ht,item->key,item->value);
        }
    //modifying the ht to have the new size and count
    ht->base_size = new_ht->base_size;
    ht->size = new_ht->size;

    //tranferring all the items from new_ht to ht
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;  

    //deleting the new_ht because we don't need it anymore
    ht_del_hash_table(new_ht);

    }
}

// for simplicity , there are two small mehtods to resize up and down
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
