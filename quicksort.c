#include "algo.h"

/* CLRS implementation */

int partition(int array[], int p, int r)
{
    int pivot = array[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
    {
        if(array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    
    int mid = i + 1;
    swap(&array[mid], &array[r]);
    return mid;
}

void quicksort_(int array[], int p, int r)
{
    if(p < r)
    {
        int q = partition(array, p, r);
        quicksort_(array, p, q-1);
        quicksort_(array, q+1, r);
    }
}

#define quicksort(array) quicksort_(array, 0, array_count(array) - 1)

/* My iterative implementation */

typedef struct
{
    int p;
    int r;
} range_t;

// NOTE: This stack size is more than large enough because for lg(n) > 256 implies a REALLY big n.
//       With the caveat that if we don't randomize our quicksort we risk not being able to
//       balance sufficiently in which case this stack size does become a problem.
static range_t stack[256];
static int stack_size;
#define push(range) stack[stack_size++] = (range)
#define pop() (stack[--stack_size])
#define empty() (stack_size <= 0)

void quicksort_iterative_(int array[], int n)
{
    stack_size = 0;
    
    range_t range;
    range.p = 0;
    range.r = n - 1;
    push(range);
    
    while(!empty())
    {
        range_t cur_range = pop();
        if(cur_range.p < cur_range.r)
        {
            range_t left, right;
            int q = partition(array, cur_range.p, cur_range.r);
            
            left.p = cur_range.p;
            left.r = q - 1;
            push(left);
            
            right.p = q + 1;
            right.r = cur_range.r;
            push(right);
        }
    }
}

#define quicksort_iterative(array) quicksort_iterative_(array, array_count(array))

#if 0
int main()
{
    srand(time(0));
#if 0
    int array[9] = {7, 3, 4, 7, 1, 0, 4, 2, -4};
    quicksort(array);
    print_array(array);
#endif
    
    int array[20] = {0};
    
    int num_runs = 5;
    for(int i = 0; i < num_runs; i++)
    {
        random_array(array, array_count(array));
        printf("before: ");
        print_array(array);

#if 0
        quicksort(array);
#else
        quicksort_iterative(array);
#endif
        
        printf("after: ");
        print_array(array);
        printf("is sorted?: %d\n", is_array_sorted(array, array_count(array)));
    }
    
    getchar();
    return 0;
}
#endif