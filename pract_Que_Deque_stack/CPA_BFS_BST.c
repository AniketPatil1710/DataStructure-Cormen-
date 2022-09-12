/* Binary Search Tree */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/* Symbolic Constants */

#define SUCCESS             1
#define FAILURE             0
#define TRUE                1
#define FALSE               0
#define BST_DATA_NOT_FOUND  2
#define BST_EMPTY           3

#define LIST_EMPTY          4
#define QUEUE_EMPTY         LIST_EMPTY



/* typedefs */

typedef int data_t;
typedef int status_t;
typedef int bool;
typedef struct bst_node bst_node_t;
typedef struct bst bst_t;

typedef bst_node_t* queue_data_t;
typedef struct node node_t;
typedef node_t list_t;
typedef list_t queue_t;



/* BST node layout defination */

struct bst_node{
    data_t data;
    bst_node_t* left;
    bst_node_t* right;
    bst_node_t* parent;
};

struct bst{
    bst_node_t* p_root_node;
    int nr_elements;
};


/* QUEUE node layout defination */

struct node{
    queue_data_t data;
    node_t* prev;
    node_t* next;
};


/* QUEUE Interface Routines Declarations */

queue_t* create_queue(); 
status_t empty(queue_t* p_queue); 
status_t front(queue_t* p_queue, queue_data_t* p_front_data);
status_t back(queue_t* p_queue, queue_data_t* p_back_data);
status_t push(queue_t* p_queue, queue_data_t new_data);  
status_t pop(queue_t* p_queue, queue_data_t* p_pop_data);
status_t destroy_queue(queue_t** pp_queue); 


/* List Interface Routines Declarations */

list_t* create_list(void);
status_t insert_end(list_t* p_list, queue_data_t new_data);
status_t get_beg(list_t* p_list, queue_data_t* p_data);
status_t get_end(list_t* p_list, queue_data_t* p_data);
status_t pop_beg(list_t* p_list, queue_data_t* p_data);
bool is_list_empty(list_t* p_list);
status_t destroy_list(list_t** pp_list);


/* List Auxillary routines */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* get_list_node(queue_data_t new_data);


/* BST Interface Routines Declarations */

bst_t* create_bst(void);

status_t insert_bst(bst_t* p_bst, data_t new_data);

void inorder(bst_t* p_bst);
void preorder(bst_t* p_bst);
void postorder(bst_t* p_bst);

void bfs_tree(bst_t* p_bst);

status_t destroy_bst(bst_t** pp_bst);


/* BST Auxilary routines */

bst_node_t* get_bst_node(data_t new_data);
void inorder_node(bst_node_t* p_node);
void preorder_node(bst_node_t* p_node);
void postorder_node(bst_node_t* p_node);
void destroy_bst_node(bst_node_t* p_node);

/* Memory Allocation routine */
void* xmalloc(size_t nr_elements);





int main(void){

    bst_t* p_bst = NULL;
    data_t bst_data[] = {100, 50, 150, 25, 75, 65, 125, 175, 130};
    int a_size = sizeof(bst_data) / sizeof(bst_data[0]);
    int i;

    p_bst = create_bst();

    for(i = 0; i < a_size; ++i)
        assert(insert_bst(p_bst, bst_data[i]) == SUCCESS);
    
    puts("\nINORDER: ");
    inorder(p_bst);

    puts("\nPREORDER: ");
    preorder(p_bst);

    puts("\nPOSTORDER: ");
    postorder(p_bst);

    puts("\nBFS: ");
    bfs_tree(p_bst);

    assert(destroy_bst(&p_bst) == SUCCESS && p_bst == NULL);

    return(EXIT_SUCCESS);
}




bst_t* create_bst(void){
    bst_t* p_bst = NULL;
    p_bst = (bst_t*)xmalloc(sizeof(bst_t));
    p_bst->p_root_node = NULL;
    p_bst->nr_elements = 0;
    return(p_bst);
}

status_t insert_bst(bst_t* p_bst, data_t new_data){
    bst_node_t* p_new_node = get_bst_node(new_data);
    bst_node_t* p_run = p_bst->p_root_node;

    /* CASE 1: Tree is Empty */
    if(p_bst->p_root_node == NULL){
        p_bst->p_root_node = p_new_node;
        return(SUCCESS);
    }

    /* CASE 2: Tree is Non-Empty */
    while(TRUE){
        if(new_data <= p_run->data){
           if(p_run->left == NULL){
              p_run->left = p_new_node;
              break;
           } else
              p_run = p_run->left;
        } else{
           if(p_run->right == NULL){
              p_run->right = p_new_node;
              break;
           } else
              p_run = p_run->right;
        }
    }
    p_bst->nr_elements += 1;
    return(SUCCESS);
}


void inorder(bst_t* p_bst){
    inorder_node(p_bst->p_root_node);
}

void preorder(bst_t* p_bst){
    preorder_node(p_bst->p_root_node);
}

void postorder(bst_t* p_bst){
    postorder_node(p_bst->p_root_node);
}

void bfs_tree(bst_t* p_bst){
    queue_t* p_queue = NULL;
    p_queue = create_queue();

    queue_data_t p_run = NULL;

    push(p_queue, p_bst->p_root_node);
    
    while(empty(p_queue) != QUEUE_EMPTY){
        pop(p_queue, &p_run);
        printf("[%3d]\t", p_run->data);
        if(p_run->left != NULL)
            push(p_queue, p_run->left);
        if(p_run->right != NULL)
            push(p_queue, p_run->right);
    }
    destroy_queue(&p_queue);
}

status_t destroy_bst(bst_t** pp_bst){
    destroy_bst_node((*pp_bst)->p_root_node);
    *pp_bst = NULL;
    return(SUCCESS);
}


bst_node_t* get_bst_node(data_t new_data){
    bst_node_t* p_new_bst_node = NULL;
    p_new_bst_node = (bst_node_t*)xmalloc(sizeof(bst_node_t));
    p_new_bst_node->data = new_data;
    return(p_new_bst_node);
}

void inorder_node(bst_node_t* p_node){
    if(p_node == NULL)
        return;
    inorder_node(p_node->left);
    printf("[%3d]\t", p_node->data);
    inorder_node(p_node->right);
}

void preorder_node(bst_node_t* p_node){
    if(p_node == NULL)
        return;
    printf("[%3d]\t", p_node->data);
    preorder_node(p_node->left);
    preorder_node(p_node->right);
}

void postorder_node(bst_node_t* p_node){
    if(p_node == NULL)
        return;
    postorder_node(p_node->left);
    postorder_node(p_node->right);
    printf("[%3d]\t", p_node->data);
}

void destroy_bst_node(bst_node_t* p_node){
    if(p_node == NULL)
        return;
    destroy_bst_node(p_node->left);
    destroy_bst_node(p_node->right);
    free(p_node);
}

void* xmalloc(size_t nr_elements){
    void* p = NULL;
    p = malloc(nr_elements);
    if(p == NULL){
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    memset(p, 0, nr_elements);
    return(p);
}



queue_t* create_queue(){
    return(create_list());
} 

status_t empty(queue_t* p_queue){
    if(is_list_empty(p_queue))
        return(QUEUE_EMPTY);
} 

status_t front(queue_t* p_queue, queue_data_t* p_front_data){
	return(get_beg(p_queue, p_front_data));
}

status_t back(queue_t* p_queue, queue_data_t* p_back_data){
	return(get_end(p_queue, p_back_data));
}

status_t push(queue_t* p_queue, queue_data_t new_data){
    return(insert_end(p_queue, new_data));
}

status_t pop(queue_t* p_queue, queue_data_t* p_pop_data){
    return(pop_beg(p_queue, p_pop_data));
}

status_t destroy_queue(queue_t** pp_queue){
    return(destroy_list(pp_queue));
}


list_t* create_list(void){
    list_t* p_list = NULL;
    p_list = get_list_node(NULL);
    p_list->next = p_list;
    p_list->prev = p_list;
    return(p_list);
}

status_t insert_end(list_t* p_list, queue_data_t new_data){
    generic_insert(p_list->prev, get_list_node(new_data), p_list);
    return(SUCCESS);
}

status_t get_beg(list_t* p_list, queue_data_t* p_data){
	if(is_list_empty(p_list))
		return(LIST_EMPTY);
	*p_data = p_list->next->data;
	return(SUCCESS);	
}

status_t get_end(list_t* p_list, queue_data_t* p_data){
    if(is_list_empty(p_list))
        return(LIST_EMPTY);
    *p_data = p_list->prev->data;
    return(SUCCESS);
}

status_t pop_beg(list_t* p_list, queue_data_t* p_data){
	if(is_list_empty(p_list))
		return(LIST_EMPTY);
	*p_data = p_list->next->data;
	generic_delete(p_list->next);
	return(SUCCESS);
}

bool is_list_empty(list_t* p_list){
    return(p_list->prev == p_list && p_list->next == p_list);
}

status_t destroy_list(list_t** pp_list){
    list_t* p_list = *pp_list;
    node_t* p_run = NULL, *p_run_next = NULL;
    for(p_run = p_list->next; p_run != p_list; p_run = p_run_next){
        p_run_next= p_run->next;
        if(p_run)
            free(p_run);
    }
    if(p_list){
        free(p_list);
        p_list = NULL;
    }
    *pp_list = NULL;
    return(SUCCESS);
}

/* List Auxillary routines */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end){
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void generic_delete(node_t* p_delete_node){
    p_delete_node->prev->next = p_delete_node->next;
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node);
}

node_t* get_list_node(queue_data_t new_data){
    node_t* p_new_node = NULL;
    p_new_node = (node_t*)xmalloc(sizeof(node_t));
    p_new_node->data = new_data;
    return(p_new_node);
}

