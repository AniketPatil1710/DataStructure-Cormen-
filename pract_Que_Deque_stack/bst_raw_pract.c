#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SUCCESS     1
#define FAILURE     0

typedef struct bst_node bst_node_t ;
typedef struct bst bst_t ;
typedef int data_t ;
typedef int status_t ;
typedef int bool ;

struct bst_node
{
    int data ;
    struct bst_node* left ;
    struct bst_node* right ;
    struct bst_node* parent ;
};

struct bst
{
    struct bst_node* p_root_node ;
    int nr_elements ;
};
 
struct bst* create_bst(void);

void inorder(struct bst* p_bst);
void preorder(struct bst* p_bst);
void postorder(struct bst* p_bst);
void inorder_node(struct bst_node* p_node);
void preorder_node(struct bst_node* p_node);
void postorder_node(struct bst_node* p_node);

status_t destroy_bst(bst_t** pp_bst);

bst_node_t* search_node(bst_t* p_bst , data_t search_data);

bool search_data(bst_t* p_bst , data_t search_data);
void destroy_bst_node(bst_node_t* p_bst);

/*struct bst_node* get_bst_node(int new_data)
{
    struct bst_node* p_new_node = NULL ;
    p_new_node = (struct bst_t*)xmalloc(sizeof(struct bst_node));
    p_new_node->data = new_data ;
    p_new_node->right = NULL ;
    p_new_node->left = NULL ;
    p_new_data->parent = NULL ;

    return(p_new_node);
}*/
int insert_bst(struct bst* p_bst , int new_data);
void* xmalloc(size_t nr_bytes);

int main(void)
{
    struct bst* p_bst = NULL ;
    int bst_data[] = {100 , 50 , 150 , 25 , 75 , 65 , 125, 175, 130};

    int bst_search_data[] = {100 , 150 , 25 , -1 , 200} ;

    int a_size = sizeof(bst_data)/sizeof(bst_data[0]);

    int i ;
    int status ;

    p_bst = create_bst() ;
    for(i = 0 ; i<a_size ; ++i)
    {
        status = insert_bst(p_bst,bst_data[i]);
        assert(status==1);
    }
    printf("\nInorder Traversal:\n");
    inorder(p_bst);
    printf("\npreorder Traversal:\n");
    preorder(p_bst);
    printf("\npostorder Traversal:\n");
    postorder(p_bst);

    a_size = sizeof(bst_search_data)/sizeof(bst_search_data[0]);

    printf("\nSearched elements:\n");
    for(i= 0 ; i<a_size  ; ++i)
    {
        status = search_data(p_bst,bst_search_data[i]);
        if(status)
            printf("%d is present BST\n",bst_search_data[i]);
        else
            printf("%d is not present BST\n",bst_search_data[i]);
    }

    status = destroy_bst(&p_bst);
    assert(status==1 && p_bst==NULL);

    void destroy_bst_node(bst_node_t* p_node) ;
    return(SUCCESS);
}

struct bst* create_bst(void)
{
    struct bst* p_bst = NULL ;
    p_bst = (struct bst*)xmalloc(sizeof(struct bst));
    return(p_bst);
}
bst_node_t* get_bst_node(data_t new_data)
{
    bst_node_t* p_new_node = NULL ;
    p_new_node = (bst_node_t*)xmalloc(sizeof(bst_node_t));
    p_new_node->data = new_data ;
    p_new_node->right = NULL ;
    p_new_node->left = NULL ;
    p_new_node->parent = NULL ;

    return(p_new_node);

}

void* xmalloc(size_t nr_bytes)
{
    void* p = NULL ;
    p = malloc(nr_bytes);
    assert(p);
    memset(p,0,nr_bytes);
    return(p);
}


int insert_bst(struct bst* p_bst , data_t new_data)
{
    struct bst_node* p_new_node = NULL ;
    struct bst_node* p_run = NULL ; /*Correct node's address */
    p_new_node = get_bst_node(new_data);

    /* case 1:Given BST is Empty*/

    if(p_bst->p_root_node == NULL)
    {
        p_bst->p_root_node = p_new_node ;
        ++(p_bst->nr_elements);
        return(SUCCESS);
    }
    /* case2 : Given BST is not Empty */
    p_run = p_bst->p_root_node ;
    while(1)
    {
        if(new_data <= p_run->data)
        {
            if(p_run->left == NULL)
            {
                p_run->left = p_new_node ;
                p_new_node->parent = p_run ;
                break;
            }
            else{
                p_run = p_run->left ;
                continue;
            }
        }
        else
        {
                if(p_run->right==NULL)
                {
                    p_run->right = p_new_node ;
                    p_new_node->parent = p_run ;
                    break;
                }
                else{
                    p_run = p_run->right ;
                    continue; 
                }
        }
    }     
    p_bst->nr_elements += 1 ;
    return (1) ;
}
void inorder(struct bst* p_bst)
{
    inorder_node(p_bst->p_root_node);
}
void preorder(struct bst* p_bst)
{
    preorder_node(p_bst->p_root_node);
}
void postorder(struct bst* p_bst)
{
    postorder_node(p_bst->p_root_node);
}
void inorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
    {
        return ;
    }
    inorder_node(p_node->left);
    printf("[%d]\t",p_node->data);
    inorder_node(p_node->right);
}

void preorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
    {
        return ;
    }
    printf("[%d]\t",p_node->data);
    preorder_node(p_node->left);
    preorder_node(p_node->right);
}

void postorder_node(struct bst_node* p_node)
{
    if(p_node == NULL)
    {
        return ;
    }
    postorder_node(p_node->left);
    postorder_node(p_node->right);
    printf("[%d]\t",p_node->data);
}

status_t destroy_bst(bst_t** pp_bst)
{
    bst_t* p_bst = *pp_bst ;
    destroy_bst_node(p_bst->p_root_node);
    free(p_bst);
    p_bst = NULL ;
    *pp_bst = NULL ;

    return(SUCCESS);
}

status_t search_data(bst_t* p_bst , data_t search_data)
{
    bst_node_t* p_node = NULL ;
    p_node = search_node(p_bst , search_data);
    return(p_node!=NULL);
}

struct bst_node* search_node(bst_t* p_bst , int search_data)
{
    struct bst_node* p_node = NULL ;

    p_node = p_bst->p_root_node ;

    while(p_bst != NULL)
    {
        if(p_node->data == search_data)
        {
            break;
        }
        else if(search_data <= p_node->data)
        {
            p_node = p_node->left ;
        }
        else{
            p_node = p_node->right ;
        }
    }
    return (p_node);
}

void destroy_bst_node(bst_node_t* p_node)
{
    if(p_node == NULL)
        return;
    destroy_bst_node(p_node->left);
    destroy_bst_node(p_node->right);
    free(p_node);
}

/*BST auxilary - Stack interface */
