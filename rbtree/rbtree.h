#ifndef _RBTREE_H 
#define _RBTREE_H 

#include <stdio.h>

#define SUCCESS 1 

typedef struct rb_node rbnode_t;
typedef struct rb_tree rbtree_t;  
typedef enum color color_t; 
typedef int data_t; 
typedef int status_t; 

enum color
{
    RED = 0, 
    BLACK
}; 

struct rb_node
{
    data_t data; 
    color_t color; 
    struct rb_node* left; 
    struct rb_node* right; 
    struct rb_node* parent; 
}; 

struct rb_tree
{
    rbnode_t* root_node; 
    rbnode_t* nil; 
    int N; 
}; 

/* RB Tree interface routines */ 
rbtree_t* create_rbtree(void); 
status_t insert_into_rbtree(rbtree_t* p_rbtree, data_t new_data); 
status_t remove_from_rbtree(rbtree_t* p_rbtree, data_t r_data); 
status_t destroy_rbtree(rbtree_t** pp_rbtree); 

void preorder_walk(rbtree_t* p_rbtree); 
void inorder_walk(rbtree_t* p_rbtree); 
void postorder_walk(rbtree_t* p_rbtree); 

/* Auxillary routines */ 

void preorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil); 
void inorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil); 
void postorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil);

void destroy_node_level(rbnode_t* p_root_node, rbnode_t* nil); 

rbnode_t* get_rbnode(data_t new_data, rbnode_t* nil); 
void *xcalloc(size_t nr_elements, size_t size_per_element); 

#endif 