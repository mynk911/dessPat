/**
  @file lcthw.h
  LCTHW header.
  header for lcthw solutions.
  */

#ifndef LCTHW_LCTHW_H_
#define LCTHW_LCTHW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lcthw_export.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bstrlib.h"
#include "dbg.h"

/** first exercise.
 * prints a number.
 * @param out FILE pointer
 * @return 0 for success,
 *         otherwise any other number
 */
int LCTHW_EXPORT ex1(FILE* out);

/// second exercise prints and variables
/// print statements
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
int LCTHW_EXPORT ex3(FILE* out);

/// seventh exercise data types
/// print examples of various data types.
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
///
int LCTHW_EXPORT ex7(FILE* out);

/// ex8 if else if in c
/// a demonstration of if else and command line parameters.
///
/// \param argc c command line arguments count, from main()
/// \param argv c command line arguments from main()
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
int LCTHW_EXPORT ex8(int argc, const char *argv[], FILE* out);

/// ex9 while loop and boolean expression
/// prints out in aloop
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
///
int LCTHW_EXPORT ex9(FILE* out);

/// ex10 switch statement
/// switch statement example
///
/// \param argc argument count
/// \param argv arguments
/// \param out file pointer
///
/// \return 0 for success,
///         otherwise some other number
int LCTHW_EXPORT ex10(int argc,const char *argv[], FILE* out);

/// ex11 strings
///
/// \param FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex11(FILE* out);

/// ex12 arrays and sizeof
///
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex12(FILE* out);

/// for loop demo in c
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex13(int argc,const char *argv[], FILE* out);

/// functions demo
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex14(int argc,const char *argv[], FILE* out);

/// demo on pointers and their relation to arrays
///
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex15(FILE* out);

struct Person;

/// Ex 16 structs and pointers to them.
/// create a person with given information.
///
/// \param n name
/// \param a age
/// \param h height
/// \param w weight
///
/// \return person
LCTHW_EXPORT struct Person*
CreatePerson(const char* n, int a, int h, int w);

/// destroys specified person.
///
/// \param p person
void LCTHW_EXPORT DestroyPerson(struct Person** p);

/// prints a person's information.
///
/// \param p person
/// \param out FILE pointer
void LCTHW_EXPORT PrintPerson(FILE* out, struct Person* p);

/*! ex17 heap and stack memory.
 * \param argc argument count
 * \param argv an array of argc c string pointers
 * \param buf output buffer
 */
int LCTHW_EXPORT ex17(int argc, const char *argv[], char* buf);

/// ex18 function pointers via sorting examples.
/// @{
/// prototype for integer comparison functions
typedef int (*compare_cb) (int a, int b);
/// prototype for integer sorting functions
typedef int* (*sort_cb) (int* numbers, int count, compare_cb cmp);
LCTHW_EXPORT int sorted_order(int a, int b);
LCTHW_EXPORT int reversed_order(int a, int b);
/// returns a % b (diffeent results for different algos)
LCTHW_EXPORT int strange_order(int a, int b);
LCTHW_EXPORT int* bubble_sort(int *numbers, int count, compare_cb cmp);
LCTHW_EXPORT int* selection_sort(int *numbers, int count, compare_cb cmp);
/// @}

/// ex19 debug macros demonstration
/// @{
LCTHW_EXPORT int test_check(const char* file_name);
LCTHW_EXPORT int test_sentinel(int code);
LCTHW_EXPORT int test_check_mem();
LCTHW_EXPORT int test_check_debug();
/// @}

/// ex22 scope in C demo
/// @(
LCTHW_EXPORT extern int THE_SIZE;
LCTHW_EXPORT int get_age();
LCTHW_EXPORT int* age();
LCTHW_EXPORT void set_age(int age);
LCTHW_EXPORT double update_ratio(double ratio);
LCTHW_EXPORT int get_size();
LCTHW_EXPORT void scope_demo(int count);
/// @}

/// ex23 duffs device
/// @{
LCTHW_EXPORT int normal_copy(char* from, char* to, int count);
LCTHW_EXPORT int duffs_device(char* from, char* to, int count);
/// @}

/// ex24 reading stream input
/// \param in input FILE
/// \param out output FILE
LCTHW_EXPORT int ex24(FILE* in, FILE* out);

/// ex25 reads inpute from in according to fmt
/// fmt is similar to printf fmt accept it's restricted to c,d and s without
/// any modifiers. for s you provide two inputs int and char**.
/// \param in
/// \param fmt
/// \return
///
LCTHW_EXPORT int read_scan(FILE* in, const char* fmt, ...);

/// ex32 Doubly linked lists
/// @{
typedef struct ListNode {
    struct ListNode* next;
    struct ListNode* prev;
    const void* value;
} ListNode;

typedef struct List {
    size_t count;
    ListNode* first;
    ListNode* last;
} List;

LCTHW_EXPORT List* List_create();
LCTHW_EXPORT void List_destroy(List* list);
LCTHW_EXPORT void List_clear(List* list);
LCTHW_EXPORT void List_clear_destroy(List* list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

LCTHW_EXPORT void List_push(List* list,const void* value);
LCTHW_EXPORT const void* List_pop(List* list);
LCTHW_EXPORT void List_unshift(List* list,const void* value);
LCTHW_EXPORT const void* List_shift(List* list);
LCTHW_EXPORT const void* List_remove(List* list, ListNode* node);

#define LIST_FOREACH(L,S,M,V) ListNode* V = NULL;\
    for(V = L->first; V!= NULL; V=V->M)
/// @}

/// ex33 LinkedList algorithms
/// @{
typedef int (*ListCompare) (const char*,const char*);
int List_bubble_sort (List*, ListCompare);
List* List_merge_sort (List*, ListCompare);
/// @}

/// ex34 Dynamic Array
/// @{
typedef struct DArray {
    size_t end;
    size_t max;
    size_t element_size;
    size_t expand_rate;
    const void **contents;
} DArray;

DArray* DArray_create(size_t element_size, size_t initial_max);
void DArray_destroy(DArray* array);
void DArray_clear(DArray* array);
int DArray_expand(DArray* array);
int DArray_contract(DArray* array);
int DArray_push(DArray* array,const void * el);
const void* DArray_pop(DArray* array);
void DArray_clear_destroy(DArray* array);

#define DAarray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void DArray_set(DArray* array, size_t i, void* el)
{
    check(i < array->max, "DArray: attempt to set past max")
    if(i > array->end)
        array->end = i;
    array->contents[i] = el;
error:
    return;
}

static inline const void* DArray_get(DArray* array, size_t i)
{
    check(i < array->max, "DArray: attempt to get past max")
    return array->contents[i];
error:
    return NULL;
}

static inline const void* DArray_remove(DArray* array, size_t i)
{
    const void* el = array->contents[i];
    array->contents[i] = NULL;
    return el;
}

static inline void* DArray_new(DArray* array)
{
    check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.")
    return calloc(1, array->element_size);
error:
    return NULL;
}

#define DArray_free(E) free((E))
/// @}


/// ex35 Sorting and searching
/// @{
typedef int (*DArray_compare)(const void* a, const void* b);
int DArray_qsort(DArray* array, DArray_compare cmp);
int DArray_hsort(DArray* array, DArray_compare cmp);
int DArray_msort(DArray* array, DArray_compare cmp);

typedef union RMElement {
    uint64_t raw;
    struct {
        uint32_t key;
        uint32_t value;
    } data;
} RMElement;

typedef struct RadixMap {
    size_t max;
    size_t end;
    uint32_t counter;
    RMElement* contents;
    RMElement* temp;
} RadixMap;

RadixMap* RadixMap_create(size_t max);
void RadixMap_destroy(RadixMap* map);
void RadixMap_sort(RadixMap* map);
RMElement* RadixMap_find(RadixMap* map, uint32_t key, size_t* lb);
int RadixMap_add(RadixMap* map, uint32_t key, uint32_t value);
int RadixMap_delete(RadixMap* map, RMElement* el);

typedef enum  {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} VariantType;

typedef struct Variant {
    VariantType type;
    union {
        int as_integer;
        float as_float;
        const char* as_string;
    } data;
} Variant;

void Variant_print(Variant* var);
/// @}

/// ex37 hashmaps
/// @{

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void* a, void* b);
typedef uint32_t (*Hashmap_hash)(void* key);

typedef struct Hashmap {
    DArray* buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
    void* key;
    void* data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode* node);

Hashmap* Hashmap_create(Hashmap_compare compare,Hashmap_hash hash);
void Hashmap_destroy(Hashmap* map);

int Hashmap_set(Hashmap* map, void* key, void* data);
void* Hashmap_get(Hashmap* map, void* key);

int Hashmap_traverse(Hashmap* map, Hashmap_traverse_cb traverse_cb);

void* Hashmap_delete(Hashmap* map, void* key);
/// @}

/// ex38 hashmap algorithms
/// @{
uint32_t Hashmap_fnv1a_hash(void* data);
uint32_t Hashmap_adler32_hash(void* data);
uint32_t Hashmap_djb_hash(void* data);
void Hashmap_generate_distribution(Hashmap_hash hash_func, uint32_t* stats, int buckets);
/// @}

/// ex39 String algorithms
/// @{
typedef struct StringScanner {
    bstring in;
    const unsigned char* haystack;
    size_t hlen;
    const unsigned char* needle;
    size_t nlen;
    size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;

int String_find(bstring in, bstring what);
StringScanner *StringScanner_create(bstring in);
int StringScanner_scan(StringScanner* scan, bstring tofind);
void StringScanner_destroy(StringScanner* scan);
/// @}

/// ex40 binary search trees
/// @{
typedef int(*BSTree_compare)(void* a, void *b);

typedef struct BSTreeNode {
    void* key;
    void* data;

    struct BSTreeNode* left;
    struct BSTreeNode* right;
    struct BSTreeNode* parent;
} BSTreeNode;

typedef struct BSTree {
    int count;
    BSTree_compare compare;
    BSTreeNode* root;
} BSTree;

typedef int(*BSTree_traverse_cb)(BSTreeNode* node);

BSTree* BSTree_create(BSTree_compare compare);
void BSTree_destroy(BSTree* map);

int BSTree_set(BSTree* map, void* key, void* data);
void* BSTree_get(BSTree* map, void* key);

int BSTree_traverse(BSTree* map, BSTree_traverse_cb traverse_cb);

void* BSTree_delete(BSTree* map, void* key);
/// @}

/// ex42 stacks and queues
/// @{
typedef struct Stack {
    List* stk;
} Stack;

Stack* Stack_create()
{
    Stack* stack = (Stack *) calloc(1, sizeof (Stack));
    stack->stk = List_create();
    return stack;
}

void Stack_destroy(Stack* stack)
{
    List_destroy(stack->stk);
    free(stack);
}

void Stack_push(Stack* stack, const void* value)
{
    List_push(stack->stk, value);
}

const void * Stack_peek(Stack* stack)
{
    return List_last(stack->stk);
}

size_t Stack_count(Stack* stack)
{
    return List_count(stack->stk);
}

const void* Stack_pop(Stack* stack)
{
    return List_pop(stack->stk);
}

typedef struct Queue {
    List* que;
} Queue;

Queue* Queue_create()
{
    Queue* queue = (Queue *) calloc(1, sizeof (Queue));
    queue->que = List_create();
    return queue;
}

void Queue_destroy(Queue* queue)
{
    List_destroy(queue->que);
    free(queue);
}

void Queue_enqueue(Queue* queue, const void* value)
{
    List_push(queue->que, value);
}

const void * Queue_peek(Queue* queue)
{
    return List_first(queue->que);
}

size_t Queue_count(Queue* queue)
{
    return List_count(queue->que);
}

const void* Queue_dequeue(Queue* queue)
{
    return List_shift(queue->que);
}
/// @}

/// ex43 simple statistics engine
/// @{
typedef struct Stats {
    double sum;
    double sumsq;
    unsigned long n;
    double min;
    double max;
} Stats;

Stats* Stats_recreate(double sum, double sumsq, unsigned long n,
                      double min, double max);
Stats* Stats_create(void);
double Stats_mean(Stats* st);
double Stats_stddev(Stats* st);
void Stats_sample(Stats* st, double s);
void Stats_dump(Stats* st);
/// @}

/// ex44 RingBuffer
/// @{
typedef struct {
    char* buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer* RingBuffer_create(int length);
void RingBuffer_destroy(RingBuffer* buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);
int RingBuffer_write(RingBuffer *buffer, char* data, int length);
bstring RingBuffer_gets(RingBuffer *buffer, int amount);

#define RingBuffer_available_data(B) \
    (((B)->end + 1) % (B)->length - (B)->start - 1)
#define RingBuffer_available_space(B) ((B)->length - (B)->end -1)
#define RingBuffer_full(B) (RingBuffer_available_data((B)) - (B)->length == 0)
#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)
#define RingBuffer_puts(B, D) RingBuffer_write((B), bdata((D)), blength((D)))
#define RingBuffer_get_all(B) \
    RingBuffer_gets((B), RingBuffer_available_data((B)))
#define RingBuffer_starts_at(B) ((B)->buffer + (B->start))
#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)
#define RingBuffer_commit_read(B, A) \
    ((B)->start = ((B)->start + (A)) % (B)->length)
#define RingBuffer_commit_write(B, A) \
    ((B)->end = ((B)->end + (A)) % (B)->length)
/// @}

#ifdef __cplusplus
}
#endif

#endif
