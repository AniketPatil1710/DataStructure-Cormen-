#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <string.h>

struct bst_node
{
    int data; // data_t data; 
    struct bst_node* left; 
    struct bst_node* right; 
    struct bst_node* parent; 
}; 

struct bst
{
    struct bst_node* p_root_node; // bst_node_t* p_root_node; 
    int nr_elements; 
}; 

struct bst* create_bst(void);
void inorder(struct bst* p_bst); 
void preorder(struct bst* p_bst); 
void postorder(struct bst* p_bst); 
int destroy_bst(struct bst** pp_bst); 

/* aux routines */ 
struct bst_node* get_bst_node(int new_data);
void* xmalloc(size_t nr_bytes);

void inorder_node(struct bst_node* p_node); 
void preorder_node(struct bst_node* p_node); 
void postorder_node(struct bst_node* p_node); 

void destroy_bst_node(struct bst_node* p_node); 

int main(void)
{
    struct bst* p_bst = NULL; 
    int bst_data[] = {100, 50, 150, 25, 75, 65, 125, 175, 130}; 
    int a_size = sizeof(bst_data) / sizeof(bst_data[0]); 
    int i; 
    int status; 

    p_bst = create_bst(); 
    for(i = 0; i < a_size; ++i)
    {
        status = insert_bst(p_bst, bst_data[i]); 
        assert(status == 1); 
    }
    
    puts("INORDER:"); 
    inorder(p_bst); 

    puts("PREORDER:"); 
    preorder(p_bst); 

    puts("POSTORDER:"); 
    postorder(p_bst); 
    
    status = destroy_bst(&p_bst); 
    assert(status == 1 && p_bst == NULL); 

    return (0); 
}

struct bst* create_bst(void)
{
    return (struct bst*)xmalloc(sizeof(struct bst)); 
}

int insert_bst(struct bst* p_bst, int new_data)
{
    struct bst_node* p_new_node = NULL;
    struct bst_node* p_run = NULL;  /* Correct node's address */ 
    p_new_node = get_bst_node(new_data);

    /* case 1: Given bst is empty */ 
    if(p_bst->p_root_node == NULL)
    {
        p_bst->p_root_node = p_new_node; 
        ++p_bst->nr_elements; 
        return (1); 
    }

    /* case 2: Given bst is non-empty */ 
    p_run = p_bst->p_root_node; 
    while(1)
    {
        if(new_data <= p_run->data)
        {
            if(p_run->left == NULL)
            {
                p_run->left = p_new_node; 
                p_new_node->parent = p_run; 
                break; 
            }
            else
            {
                p_run = p_run->left; 
            }
        }
        else
        {
            if(p_run->right == NULL)
            {
                p_run->right = p_new_node; 
                p_new_node->parent = p_run; 
                break; 
            }
            else
            {
                p_run = p_run->right;    
            }
        }
    }

    p_bst->nr_elements += 1; 
    return (1); 
}

void inorder(struct bst* p_bst)
{
    printf("[BEG]\t"); 
    inorder_node(p_bst->p_root_node); 
    puts("[END]"); 
}

void preorder(struct bst* p_bst)
{
    printf("[BEG]\t"); 
    preorder_node(p_bst->p_root_node); 
    puts("[END]");
}

void postorder(struct bst* p_bst)
{
    printf("[BEG]\t"); 
    postorder_node(p_bst->p_root_node); 
    puts("[END]");
}

void inorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
        return; 
    inorder_node(p_node->left); 
    printf("[%d]\t", p_node->data); 
    inorder_node(p_node->right); 
}

void preorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
        return; 
    printf("[%d]\t", p_node->data);
    preorder_node(p_node->left); 
    preorder_node(p_node->right); 
}

void postorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
        return; 
    postorder_node(p_node->left); 
    postorder_node(p_node->right); 
    printf("[%d]\t", p_node->data); 
}

int destroy_bst(struct bst** pp_bst)
{
    struct bst* p_bst = *pp_bst; 
    destroy_bst_node(p_bst->p_root_node); 
    free(p_bst); 
    p_bst = NULL; 
    *pp_bst = NULL; 
    return (1); 
}

struct bst_node* get_bst_node(int new_data)
{
    struct bst_node* p_new_node = NULL; 

    p_new_node = (struct bst_node*)xmalloc(sizeof(struct bst_node)); 
    p_new_node->data = new_data; 
    p_new_node->left = NULL; 
    p_new_node->right = NULL; 
    p_new_node->parent = NULL; 

    return (p_new_node); 
}

void destroy_bst_node(struct bst_node* p_node)
{
    if(p_node == NULL)
        return; 
    destroy_bst_node(p_node->left); 
    destroy_bst_node(p_node->right); 
    free(p_node); 
}

void* xmalloc(size_t nr_bytes)
{
    void* p = NULL; 
    p = malloc(nr_bytes); 
    assert(p); 
    memset(p, 0, nr_bytes); 
    return (p); 
}