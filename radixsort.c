#include "algo.h"

/* The data in input is sorted and stored in output.
   Every x must have the property 0 <= x <= k */
void countingsort_(int input[], int output[], int n, int max)
{
    int *freq = calloc(max + 1, sizeof(int)); // freq[x] = (the number of elements in input such that that element <= x)
    
    for(int i = 0; i < n; i++)
    {
        freq[input[i]]++;
    }
    
    // can prove this inductively
    for(int i = 1; i <= max; i++)
    {
        freq[i] += freq[i - 1];
    }
    
    for(int i = (n - 1); i >= 0; i--)
    {
        int x = input[i];
        output[freq[x] - 1] = x;
        freq[x]--;
    }
    
    free(freq);
}

#define countingsort(input, output, max) countingsort_(input, output, array_count(input), max)

#define byte(n, index) ((n >> (index << 3)) & 0xFF)
void countingsort_by_byte(int input[], int output[], int n, int max, int byte_index)
{
    int *freq = calloc(max + 1, sizeof(int));
    
    for(int i = 0; i < n; i++)
    {
        int x = byte(input[i], byte_index);
        freq[x]++;
    }
    
    for(int i = 1; i <= max; i++)
    {
        freq[i] += freq[i - 1];
    }
    
    for(int i = (n - 1); i >= 0; i--)
    {
        int x = byte(input[i], byte_index);
        output[freq[x] - 1] = input[i];
        freq[x]--;
    }
    
    free(freq);
}

/* Using bytes instead of digits for efficeny */
void radixsort_(int input[], int output[], int n)
{
    int *aux1 = calloc(n, sizeof(int));
    int *aux2 = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) aux1[i] = input[i];
    
    int max = 0xFF;
    for(int byte_index = 0; byte_index < sizeof(int); byte_index++)
    {
        countingsort_by_byte(aux1, aux2, n, max, byte_index);
        
        int *temp = aux1;
        aux1 = aux2;
        aux2 = temp;
    }
    
    for(int i = 0; i < n; i++) output[i] = aux1[i];
}

#define radixsort(input, output) radixsort_(input, output, array_count(input));

int main()
{
    int array[20] = {0};
    int result[20] = {0};
    
    int num_runs = 50;
    for(int i = 0; i < num_runs; i++)
    {
        random_array(array, array_count(array));
        printf("before: ");
        print_array(array);
        
        radixsort(array, result);
        
        printf("after: ");
        print_array(result);
        printf("is sorted?: %d\n", is_array_sorted(result, array_count(array)));
    }
    
    getchar();
    return 0;
}