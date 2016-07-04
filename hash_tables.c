#include "algo.h"

typedef struct hash_entry_t
{
    int value;
    struct hash_entry_t *next;
    b32 removed;
} hash_entry_t;

#define HASH_CONSTANT 0.8342f

/* Chaining hash table */

typedef struct 
{
    hash_entry_t *slots[10];
} hash_table_chaining_t;

void init_hash_table(hash_table_chaining_t *table)
{
    for(int i = 0; i < array_count(table->slots); i++) table->slots[i] = 0;
}

void free_hash_table(hash_table_chaining_t *table)
{
    for(int slot_index = 0; slot_index < array_count(table->slots); slot_index++)
    {
        hash_entry_t *entry = table->slots[slot_index];
        while(entry)
        {
            hash_entry_t *temp_entry = entry;
            entry = entry->next;
            free(temp_entry);
        }
        table->slots[slot_index] = 0;
    }
}

inline int hash1(int hash_count, int value)
{
    if(value < 0) value = -value;
    r32 result = (HASH_CONSTANT*value);
    result = (result - (int)result)*hash_count;
    return (int)result;
}

hash_entry_t *search_chaining(hash_table_chaining_t *table, int value)
{
    int hash_value = hash1(array_count(table->slots), value);
    
    hash_entry_t *entry = table->slots[hash_value];
    while(entry)
    {
        if(entry->value == value)
        {
            return entry;
        }
        entry = entry->next;
    }
    
    return 0;
}

void insert_chaining(hash_table_chaining_t *table, int value)
{
    if(!search_chaining(table, value))
    {
        int hash_value = hash1(array_count(table->slots), value);
        
        hash_entry_t *new_entry = malloc(sizeof(hash_entry_t));
        new_entry->value = value;
        new_entry->next = table->slots[hash_value];
        table->slots[hash_value] = new_entry;
    }
}

void delete_chaining(hash_table_chaining_t *table, int value)
{
    int hash_value = hash1(array_count(table->slots), value);
    
    hash_entry_t *entry = table->slots[hash_value];
    
    if(entry->value == value)
    {
        table->slots[hash_value] = entry->next;
        free(entry);
    }
    else
    {
        hash_entry_t *prev_entry;
        do
        {
            prev_entry = entry;
            entry = entry->next;
        }
        while(entry && entry->value != value);
        
        if(entry)
        {
            hash_entry_t *temp_entry = entry;
            prev_entry->next = entry->next;
            free(entry);
        }
    }
}

/* Probing hash table */

typedef struct
{
    hash_entry_t *slots[15];
} hash_table_probing_t;

inline int hash2(int hash_count, int value)
{
    int result = (value + 3) % hash_count;
    if(result < 0) result = -result;
    return result;
}

inline int double_hash_probe(int hash_count, int value, int probe_index)
{
    int result = (hash1(hash_count, value) + probe_index*hash2(hash_count, value)) % hash_count;
    return result;
}

hash_entry_t *search_probing(hash_table_probing_t *table, int value)
{
    hash_entry_t *result = 0;
    for(int probe_index = 0; probe_index < array_count(table->slots); probe_index++)
    {
        int hash_value = double_hash_probe(array_count(table->slots), value, probe_index);
        hash_entry_t *entry = table->slots[hash_value];
        
        if(entry == 0) break;
        if(!entry->removed && entry->value == value)
        {
            result = entry;
            break;
        }
    }
    return result;
}

void insert_probing(hash_table_probing_t *table, int value)
{
    for(int probe_index = 0; probe_index < array_count(table->slots); probe_index++)
    {        
        int hash_value = double_hash_probe(array_count(table->slots), value, probe_index);
        hash_entry_t *entry = table->slots[hash_value];
        
        if((entry == 0) || ((entry != 0) && entry->removed))
        {
            hash_entry_t *new_entry = malloc(sizeof(hash_entry_t));
            new_entry->removed = false;
            new_entry->value = value;
            table->slots[hash_value] = new_entry;
            return;
        }
    }
    assert("out of space");
}

void delete_probing(hash_table_probing_t *table, int value)
{
    for(int probe_index = 0; probe_index < array_count(table->slots); probe_index++)
    {        
        int hash_value = double_hash_probe(array_count(table->slots), value, probe_index);
        hash_entry_t *entry = table->slots[hash_value];
        
        if(entry == 0) break;
        if(!entry->removed && (entry->value == value))
        {
            entry->removed = true;
        }
    }
}


int main()
{
    srand(time(0));
    
    hash_table_chaining_t table;
    init_hash_table(&table);
    
    insert_chaining(&table, 4);
    insert_chaining(&table, 8);
    insert_chaining(&table, 12);
    insert_chaining(&table, 54);
    insert_chaining(&table, 4);
    insert_chaining(&table, 0);
    insert_chaining(&table, 64);
    insert_chaining(&table, 97);
    insert_chaining(&table, -50);
    
    hash_entry_t *result = 0;

    delete_chaining(&table, 0);
    
    result = search_chaining(&table, 4);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_chaining(&table, 64);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_chaining(&table, 54);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_chaining(&table, -3);
    printf("address: %p, value %d\n", result, ((result == NULL) ? -1 : result->value));
    
    delete_chaining(&table, 54);
    result = search_chaining(&table, 54);
    printf("address: %p, value %d\n", result, ((result == NULL) ? -1 : result->value));

    
    
    printf("------------\n\n\n");
    
    
    
    hash_table_probing_t table2;
    for(int i = 0; i < array_count(table2.slots); i++) table2.slots[i] = 0;
    
    insert_probing(&table2, 4);
    insert_probing(&table2, 8);
    insert_probing(&table2, 12);
    insert_probing(&table2, 54);
    insert_probing(&table2, 4);
    insert_probing(&table2, 0);
    insert_probing(&table2, 64);
    insert_probing(&table2, 97);
    insert_probing(&table2, -50);

    delete_probing(&table2, 54);
    insert_probing(&table2, 54);

    
    result = 0;

    delete_probing(&table2, 0);
    
    result = search_probing(&table2, 4);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_probing(&table2, 64);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_probing(&table2, 54);
    printf("address: %p, value %d\n", result, result->value);
    
    result = search_probing(&table2, -3);
    printf("address: %p, value %d\n", result, ((result == NULL) ? -1 : result->value));
    
    delete_probing(&table2, 54);
    result = search_probing(&table2, 54);
    printf("address: %p, value %d\n", result, ((result == NULL) ? -1 : result->value));
    
    getchar();
}