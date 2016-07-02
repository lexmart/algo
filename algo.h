#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

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