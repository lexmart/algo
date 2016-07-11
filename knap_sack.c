#include "algo.h"

int knap_sack(int num_items, int max_weight, int values[], int weights[])
{
    int *memo = calloc((num_items + 1)*(max_weight + 1), sizeof(int));
    int w = (max_weight + 1);
    
    for(int weight = 0; weight <= max_weight; weight++) *g2d(memo, w, 0, weight) = 0;
    for(int item = 0; item <= num_items; item++) *g2d(memo, w, item, 0) = 0;
    
    for(int item = 1; item <= num_items; item++)
    {
        for(int weight = 1; weight <= max_weight; weight++)
        {
            int item_weight = weights[item - 1];
            int item_value = values[item - 1];
            
            int max_value = *g2d(memo, w, item - 1, weight);
            if(weight - item_weight >= 0)
            {
                max_value = maximum(max_value, *g2d(memo, w, item - 1, weight - item_weight) + item_value);
            }
            *g2d(memo, w, item, weight) = max_value;
        }
    }
    
    for(int item = 0; item <= num_items; item++)
    {
        for(int weight = 0; weight <= max_weight; weight++)
        {
            printf("%d\t", *g2d(memo, w, item, weight));
        }
        printf("\n");
    }
    
    int result = *g2d(memo, w, num_items, max_weight);
    return result;
}

int main()
{
    int weights[] = {1, 5, 3, 4};
    int values[] = {15, 10, 9, 5};
    
    printf("%d\n", knap_sack(array_count(weights), 8, values, weights));
    
    return 0;
}