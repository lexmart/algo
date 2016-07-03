#include "algo.h"
#include "quicksort.c"

int naive_selection(int array[], int i)
{
    // assumes array is sorted
    return array[i-1];
}

int random_partition(int array[], int p, int r)
{
    int pivot = random_int(p, r);
    swap(&array[r], &array[pivot]);
    return partition(array, p, r);
}

// Find the i-th smallest number in array, O(n) expected.
int selection_search_(int array[], int p, int r, int i)
{
    if(p == r)
    {
        return array[p];
    }
    
    int q = random_partition(array, p, r);
    int left_array_count = q - p + 1;
    
    int result;
    
    if(left_array_count == i)
    {
        result = array[q];
    }
    else if(left_array_count > i)
    {
        result = selection_search_(array, p, q - 1, i);
    }
    else
    {
        result = selection_search_(array, q + 1, r, i - left_array_count);
    }
    
    return result;
}
#define selection_search(array, i) selection_search_(array, 0, array_count(array) - 1, i)

void random_test_case()
{
    int array1[20];
    int array2[20];
    random_array(array1, array_count(array1));
    for(int i = 0; i < array_count(array1); i++) array2[i] = array1[i];
    
    int i = random_int(1, array_count(array1) + 1);
    
    quicksort(array1);
    int correct_answer = naive_selection(array1, i);
    
    int test_answer = selection_search(array2, i);
    
    print_array(array1);
    printf("i= %d, correct_answer= %d, test_answer= %d, passed= %d\n", 
           i, correct_answer, test_answer, (correct_answer == test_answer));
}

int main()
{
    srand(time(NULL));
    int num_tests = 20;
    for(int i = 0; i < num_tests; i++)
    {
        random_test_case();
    }
    getchar();
}