#ifndef ALGO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float r32;
typedef double r64;

typedef int b32;

typedef struct node_t
{
    int value;
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
} node_t;

#define inline __inline

#define assert(expression) if(!(expression)) { *((int *)0) = 0; }
#define array_count(array) (sizeof(array)/(sizeof((array)[0])))
#define invalid_code_path assert(!"Invalid code path");

void print_array_(int array[], int n)
{
    printf("{ ");
    for(int i = 0; 
        i < n; 
        i++)
    {
        printf("%d ", array[i]);
    }
    printf("}");
    printf("\n");
}
#define print_array(array) print_array_(array, array_count(array))

inline void random_array(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        array[i] = (rand() % 100);
    }
}

inline b32 is_array_sorted(int array[], int n)
{
    b32 result = true;
    for(int i = 1; i < n; i++)
    {
        if(array[i] < array[i - 1])
        {
            result = false;
        }
    }
    return result;
}

inline void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

inline int random_int(int min, int max)
{
    int range = max - min;
    int offset = rand() / (RAND_MAX / range);
    
    int result = min + offset;
    assert((result >= min) && (result <= max));
    return result;
}

void print_tree(node_t *node)
{
    node_t *tree[256];
    
    tree[0] = node;
    int leaves_start_index = 0;
    int leaves_count = 1;
    
    while(1)
    {
        b32 has_non_null_leafs = false;
        
        int new_leaves_start_index = leaves_start_index + leaves_count;
        for(int i = 0; i < leaves_count; i++)
        {
            node_t *leaf = tree[leaves_start_index + i];
            node_t **leaf_left = &tree[new_leaves_start_index + 2*i];
            node_t **leaf_right = &tree[new_leaves_start_index + 2*i + 1];
            
            if(leaf)
            {
                has_non_null_leafs = true;
                *leaf_left = leaf->left;
                *leaf_right = leaf->right;
            }
            else
            {
                *leaf_left = 0;
                *leaf_right = 0;
            }
        }
        
        leaves_start_index = new_leaves_start_index;
        leaves_count *= 2;
        
        if(!has_non_null_leafs)
        {
            break;
        }
    }
    
    int num_nodes = leaves_start_index;

    
    /* This code for printing tree was obtained from
    http://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console */
#define PARENT(i) ((i-1) / 2)
#define LINE_WIDTH 128
    
    int *print_pos = (int *)malloc(num_nodes*sizeof(int));
    int i, j, k, pos, x=1, level=0;
    
    print_pos[0] = 0;
    for(i = 0,j = 1; i < num_nodes; i++,j++) {
        pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow((double)2,level+1))+1);
        
        for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':'=');
        if(tree[i]) printf("%d",tree[i]->value);
        else printf("=");
        
        print_pos[i] = x = pos+1;
        if (j==pow((float)2,level)) {
            printf("\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    
    free(print_pos);
}

void int_to_string(int value, char *output, int output_count)
{
    int i = 0;
    while(value > 0)
    {
        assert(i < output_count);
        output[i++] = (value % 10) + '0';
        value /= 10;
    }
    
    for(int j = 0; j < (i / 2); j++)
    {
        int k = i - j - 1;
        int temp = output[k];
        output[k] = output[j];
        output[j] = temp;
    }
}

// NOTE: Get pointer to element in 2d array represented by a pointer
#define g2d(array, width, i, j) (&((array)[(i)*(width) + (j)]))

#define maximum(a, b) (((a) >= (b)) ? (a) : (b))
#define minimum(a, b) (((a) <= (b)) ? (a) : (b))

#define ALGO_H
#endif