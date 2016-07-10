#include "algo.h"

// returns optimal parens that minimize # of operations
void matrix_parenthesize(int *matricies, int *memo, int *sols, int n)
{
    for(int j = 0; j < n; j++)
    {
        for(int i = j; i >= 0; i--)
        {
            int index = i*n + j;
            
            if(i == j)
            {
                memo[index] = 0;
            }
            else
            {
                memo[index] = (1 << 29);
                for(int k = i; k < j; k++)
                {
                    int new_memo = memo[i*n + k] + memo[(k+1)*n + j] + matricies[i]*matricies[k+1]*matricies[j+1];
                    if(new_memo < memo[index])
                    {
                        memo[index] = new_memo;
                        sols[index] = k;
                    }
                }
            }
        }
    }
}

void print_solution(int *sols, int i, int j, int n)
{
    if(i == j)
    {
        printf("M_%d", i);
    }
    else
    {
        printf("(");
        int k = sols[i*n + j];
        print_solution(sols, i, k, n);
        print_solution(sols, k+1, j, n);
        printf(")");
    }
}

int main()
{
    int n = 6; // number of matricies
    int matricies[6+1] = {30, 35, 15, 5, 10, 20, 25}; // matrix i has dimension p[i] x p[i+1]
    int *memo = calloc(n*n, sizeof(int));
    int *sols = calloc(n*n, sizeof(int));
    matrix_parenthesize(matricies, memo, sols, n);
    print_solution(sols, 0, n-1, n);
    
    printf("\n\n\n");
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i <= j)
            {
                printf("%d\t", memo[i*n + j]);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}