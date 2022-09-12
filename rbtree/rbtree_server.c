#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "rbtree.h"

rbtree_t* create_rbtree(void)
{
    rbtree_t* p_rbtree = (rbtree_t*)xcalloc(1, sizeof(rbtree_t)); 
    p_rbtree->N = 0; 
    p_rbtree->nil = (rbnode_t*)xcalloc(1, sizeof(rbnode_t)); 
    p_rbtree->nil->data = -1; 
    p_rbtree->nil->color = BLACK; 
    p_rbtree->nil->left = NULL; 
    p_rbtree->nil->right = NULL; 
    p_rbtree->nil->parent = NULL; 
    p_rbtree->root_node = p_rbtree->nil; 
    return (p_rbtree); 
}

status_t destroy_rbtree(rbtree_t** pp_rbtree)
{
    rbtree_t* p_rbtree = *pp_rbtree; 

    destroy_node_level(p_rbtree->root_node, p_rbtree->nil); 
    free(p_rbtree->nil); 
    free(p_rbtree); 

    *pp_rbtree = NULL; 
    return (SUCCESS); 
}

void preorder_walk(rbtree_t* p_rbtree)
{
    puts("Preorder walk:"); 
    printf("[START]<->"); 
    preorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]"); 
}

void inorder_walk(rbtree_t* p_rbtree)
{
    puts("Inorder walk:"); 
    printf("[START]<->"); 
    inorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]"); 
}

void postorder_walk(rbtree_t* p_rbtree)
{
    puts("Postorder walk:"); 
    printf("[START]<->"); 
    postorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]"); 
}

/* Implementation of auxillary routines */ 

void destroy_node_level(rbnode_t* p_root_node, rbnode_t* nil)
{
    if(p_root_node != nil)
    {
        preorder_node_walk(p_root_node->left, nil); 
        preorder_node_walk(p_root_node->right, nil); 
        free(p_root_node); 
    }   
}

void preorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        printf("[%d]<->", p_rbnode->data); 
        preorder_node_walk(p_rbnode->left, nil); 
        preorder_node_walk(p_rbnode->right, nil); 
    }   
}

void inorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    { 
        preorder_node_walk(p_rbnode->left, nil);
        printf("[%d]<->", p_rbnode->data); 
        preorder_node_walk(p_rbnode->right, nil); 
    }  
}

void postorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        preorder_node_walk(p_rbnode->left, nil); 
        preorder_node_walk(p_rbnode->right, nil); 
        printf("[%d]<->", p_rbnode->data); 
    }
}

rbnode_t* get_rbnode(data_t new_data, rbnode_t* nil)
{
    rbnode_t* p_new_rbnode = NULL; 

    p_new_rbnode = (rbnode_t*)xcalloc(1, sizeof(rbnode_t)); 
    p_new_rbnode->data = new_data; 
    p_new_rbnode->color = RED; 
    p_new_rbnode->left = nil; 
    p_new_rbnode->right = nil; 
    p_new_rbnode->parent = nil; 

    return (p_new_rbnode); 
}

void *xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    assert(p != NULL); 
    return (p); 
}