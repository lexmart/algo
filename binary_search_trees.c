#include "algo.h"

typedef struct bst_t
{
    node_t *root;
} bst_t;


bst_t create_bst()
{
    bst_t result;
    result.root = 0;
    return result;
}

void free_tree(node_t *node)
{
    if(node)
    {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

void verify_children_linked_to_parents(node_t *node)
{
    if(node)
    {
        if(node->left) assert(node->left->parent == node);
        if(node->right) assert(node->right->parent == node);
        verify_children_linked_to_parents(node->left);
        verify_children_linked_to_parents(node->right);
    }
}

/* Assuming all keys are distinct */
node_t *search(bst_t *tree, int value)
{
    node_t *current = tree->root;
    
    while(current && current->value != value)
    {
        if(value <= current->value)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    
    return current;
}

node_t *minimum(node_t *sub_tree)
{
    assert(sub_tree);
    while(sub_tree->left)
    {
        sub_tree = sub_tree->left;
    }
    return sub_tree;
}

node_t *maximum(node_t *sub_tree)
{
    assert(sub_tree);
    while(sub_tree->right)
    {
        sub_tree = sub_tree->right;
    }
    return sub_tree;
}

node_t *successor_from_value(bst_t *tree, int value)
{
    node_t *result = 0;
    
    node_t *node = search(tree, value);
    if(node->right)
    {
        result = minimum(node->right);
    }
    else
    {
        while(node->parent && node->parent->right == node)
        {
            node = node->parent;
        }
        result = node->parent;
    }
    
    return result;
}

node_t *successor_from_node(bst_t *tree, node_t *node)
{
    node_t *result = 0;
    
    if(node->right)
    {
        result = minimum(node->right);
    }
    else
    {
        while(node->parent && node->parent->right == node)
        {
            node = node->parent;
        }
        result = node->parent;
    }
    
    return result;    
}

void insert(bst_t *tree, int value)
{
    assert(search(tree, value) == 0); // avoid duplicates
    
    node_t *parent = 0;
    node_t *current = tree->root;
    
    while(current != 0)
    {
        parent = current;
        if(value <= current->value) current = current->left;
        else current = current->right;
    }
    
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->left = 0;
    new_node->right = 0;
    
    if(parent == 0)
    {
        tree->root = new_node;
    }
    else if(value <= parent->value)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }
    
    new_node->parent = parent;
}

void transplant(bst_t *tree, node_t *dest_tree, node_t *source_tree)
{
    if(dest_tree->parent == 0)
    {
        tree->root = source_tree;
    }
    else if(dest_tree == dest_tree->parent->left)
    {
        dest_tree->parent->left = source_tree;
    }
    else
    {
        dest_tree->parent->right = source_tree;
    }
    
    if(source_tree)
    {
        source_tree->parent = dest_tree->parent;
    }
}

void delete(bst_t *tree, node_t *deleted_node)
{
    assert(deleted_node);
    
    if(deleted_node->left == 0)
    {
        transplant(tree, deleted_node, deleted_node->right);
    }
    else if(deleted_node->right == 0)
    {
        transplant(tree, deleted_node, deleted_node->left);
    }
    else
    {
        node_t *replacement_node = minimum(deleted_node->right);
        
        if(replacement_node->parent != deleted_node)
        {
            transplant(tree, replacement_node, replacement_node->right);
            replacement_node->right = deleted_node->right;
            deleted_node->right->parent = replacement_node;
        }
        
        replacement_node->left = deleted_node->left;
        deleted_node->left->parent = replacement_node;
        replacement_node->parent = deleted_node->parent;
        transplant(tree, deleted_node, replacement_node);
        
    }
}

/* assumes array has all distinct integers */
void binary_search_tree_sort(int *array, int n)
{
    bst_t bst = create_bst();
    for(int i = 0; i < n; i++)
    {
        insert(&bst, array[i]);
    }
    
    node_t *current_node = minimum(bst.root);    
    for(int i = 0; i < n; i++)
    {
        array[i] = current_node->value;
        current_node = successor_from_node(&bst, current_node);
    }
    
    free_tree(bst.root);
}

int main()
{
    int array[10] = {7, 3, 1, 8, 4, 9, -7, 23, -5, 2};
    binary_search_tree_sort(array, array_count(array));
    print_array(array);
    
    bst_t bst = create_bst();

    insert(&bst, 1);
    insert(&bst, 6);
    insert(&bst, 3);
    insert(&bst, 9);
    insert(&bst, 0);
    insert(&bst, 10);
    insert(&bst, 2);
    insert(&bst, 7);
    insert(&bst, 5);
    insert(&bst, 8);
    insert(&bst, -4);
    insert(&bst, -2);
    verify_children_linked_to_parents(bst.root);

    
    print_tree(bst.root);
    delete(&bst, search(&bst, 6));
    print_tree(bst.root);
    
    verify_children_linked_to_parents(bst.root);
    
    free_tree(bst.root);
    
    getchar();
}