#include "algo.h"

typedef struct
{
    int *items;
    int items_size;
    int heap_size;
} heap_t;

heap_t init_heap()
{
    heap_t result = {0};
    return result;
}

void free_heap(heap_t *heap)
{
    free(heap->items);
}

inline int parent_node(int i)
{
    return (i/2);
}

inline int left_child(int i)
{
    return (2*i);
}

inline int right_child(int i)
{
    return (2*i) + 1;
}

inline void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// NOTE: for reasons nodes are 1-indexed
inline int *get_node(heap_t *heap, int i)
{
    int *result = &heap->items[i-1];
    return result;
}

/* Assumes that left and right subtrees are max-heaps but node-i might violate heap property. */
void max_heapify_down(heap_t *heap, int i)
{
    while(1)
    {
        int left = left_child(i);
        int right = right_child(i);
        int max = i;
        
        if((left <= heap->heap_size) && (*get_node(heap, left) > *get_node(heap, max)))
        {
            max = left;
        }
        
        if((right <= heap->heap_size) && (*get_node(heap, right) > *get_node(heap, max)))
        {
            max = right;
        }
        
        if(max != i)
        {
            swap(get_node(heap, i), get_node(heap, max));
            i = max;
        }
        else
        {
            break;
        }
    }
}

/* Assumes that node-i is root for a  max-heap but that node-i might violate heap property with its parent */
void max_heapify_up(heap_t *heap, int i)
{
    int *parent = get_node(heap, parent_node(i));
    int *child = get_node(heap, i);
    while((i > 1) && (*parent < *child))
    {
        swap(parent, child);
        i = parent_node(i);
        
        parent = get_node(heap, parent_node(i));
        child = get_node(heap, i);
    }
}

void build_max_heap(heap_t *heap, int array[], int n)
{
    heap->items_size = n;
    heap->heap_size = n;
    
    if(heap->items)
    {
        free(heap->items);
    }
    heap->items = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++)
    {
        heap->items[i] = array[i];
    }
    
    int last_non_leaf = n/2;
    for(int i = last_non_leaf; i >= 1; i--)
    {
        max_heapify_down(heap, i);
    }
}

/* Priority Queue operations: Maximum, ExtractMaximum, IncreaseKey, Insert
*/

int heap_maximum(heap_t *heap)
{
    int result = *get_node(heap, 1);
    return result;
}

int heap_extract_maximum(heap_t *heap)
{
    assert(heap->heap_size >= 1);
    int max = *get_node(heap, 1);
    
    *get_node(heap, 1) = *get_node(heap, heap->heap_size);
    heap->heap_size--;
    max_heapify_down(heap, 1);
    
    return max;
}

void heap_increase_key(heap_t *heap, int i, int new_key)
{
    int *node = get_node(heap, i);
    assert(new_key >= *node);
    
    *node = new_key;
    max_heapify_up(heap, i);
}

void heap_double_size(heap_t *heap)
{
    int *new_items = malloc(2*heap->items_size*sizeof(int));
    for(int i = 0; i < heap->items_size; i++)
    {
        new_items[i] = heap->items[i];
    }
    heap->items_size = 2*heap->items_size;
    heap->items = new_items;
}

void heap_insert(heap_t *heap, int key)
{
    if(heap->heap_size >= heap->items_size)
    {
        heap_double_size(heap);
    }
    
    *get_node(heap, ++heap->heap_size) = key;
    max_heapify_up(heap, heap->heap_size);
}

/* this version of heap sort is not "in place" since build_max_heap copies, but it would be trivial to change */
void heap_sort(int array[], int n)
{
    heap_t heap = init_heap();
    build_max_heap(&heap, array, n);
    
    for(int i = n; i >= 1; i--)
    {
        int max = heap_extract_maximum(&heap);
        array[i-1] = max;
    }
}

int main()
{
    int a[9] = {8, 3, 7, 3, 1, 6, 3, 7, 12};
    
#if 0
    heap_t heap = init_heap();
    build_max_heap(&heap, a, array_count(a));
    print_array_(heap.items, heap.heap_size);
#endif
    
#if 0
    heap_sort(a, array_count(a));
    print_array(a);
#endif
    
#if 0
    heap_t heap = init_heap();
    build_max_heap(&heap, a, array_count(a));
    print_array_(heap.items, heap.heap_size);
    while(heap.heap_size)
    {
        printf("%d\n", heap_extract_maximum(&heap));
    }
#endif
    
#if 0
    heap_t heap = init_heap();
    build_max_heap(&heap, a, array_count(a));
    print_array_(heap.items, heap.heap_size);
    
    heap_increase_key(&heap, heap.heap_size, 10);
    print_array_(heap.items, heap.heap_size);
    while(heap.heap_size)
    {
        printf("%d\n", heap_extract_maximum(&heap));
    }
#endif
    
#if 0
    heap_t heap = init_heap();
    build_max_heap(&heap, a, array_count(a));

    int b[5] = {34, 0, 10, -5, 8};
    for(int i = 0; i < array_count(b); i++)
    {
        heap_insert(&heap, b[i]);
    }
    
    print_array_(heap.items, heap.heap_size);
    while(heap.heap_size)
    {
        printf("%d\n", heap_extract_maximum(&heap));
    }
#endif
    
    getchar();
    return 0;
}