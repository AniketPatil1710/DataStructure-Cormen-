
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

/* Symbolic Constant*/

#define TRUE          1
#define SUCCESS       1
#define LIST_EMPTY    2
#define STACK_EMPTY   LIST_EMPTY

/* typedefs */

typedef int data_t ;
typedef int status_t ;
typedef int bool ;
typedef int len_t ;
typedef struct node node_t ;
typedef node_t list_t  ;
typedef list_t stack_t ;

/* node layout defination */

struct node{
    data_t data ;
    node_t* prev;
    node_t* next ;
};

/* stack interface declaration */

stack_t* create_stack(void);

/*List Interface routines*/

list_t* create_list();
status_t insert_end(list_t* p_list , data_t new_data);
status_t get_end(list_t* p_list , data_t* p_data);
status_t pop_end(list_t* p_list , data_t* p_data);
len_t get_length(list_t* p_list);
bool is_list_empty(list_t* p_list);
void show_list(list_t* p_list , const char* msg);
status_t destroy_list(list_t** pp_list);

/* List Auxillary routines */

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* get_list_node(data_t new_data);

/* Memory Alloation routine */
void* xmalloc(size_t nr_bytes);

int main(void)
{

}

status_t empty(stack_t* p_stack)
{

}

list_t* create_list(list_t* p_list)
{
    node_t* new_node = NULL ;
    p_new_node = get_list_node(0) ;
    p_new_node->next = p_new_node ;
    p_new_node->prev = p_new_node ;

    return (p_new_node);
}


void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end)
{
    p_mid->next = p_end ;
    p_mid->prev = p_beg ;
    p_beg->next = p_mid ;
    p_end->prev = p_mid ;
}

status_t insert_end(list_t* p_list , data_t new_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY);
    }
    generic_insert(p_list->prev , get_list_node(new_data) , p_list);
    return(SUCCESS);
}

status_t get_end(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list)==NULL)
    {
        return(LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;
    return(SUCCESS);
}

status_t pop_end(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list)==NULL)
    {
        return (LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;
    generic_delete(p_list->prev) ;

    return(SUCCESS);
}

len_t get_lengh(list_t* p_list)
{
    len_t len =0 ;
    node_t* p_run = NULL ;
    for(p_run=p_list->next ; p_run != p_list ; p_run = p_run->next , ++len);
    return(len);
}

bool is_list_empty(list_t* p_list)
{
    return (p_list->next == NULL && p_list->prev == NULL);
}

void show_list(list_t* p_list)
{
    node_t* p_run = NULL ;
    if(msg)
    {
        puts(msg);
    }
    printf("[TOP]\n");
    printf("__________________");

    for(p_run = p_list->next ; p_run != p_list ; p_run = p_run->next)
    {
        printf("[%d]\n",p_run->data);
    }
    printf("_____________\n");
    puts("[BOTTOM]");
}

status_t* destroy_list(list_t** p_list)
{
    list_t* p_list = *pp_list ;

    node_t* p_run = NULL , *p_run_next = NULL ;

    for(p_run = p_list->next ; p_run!= p_list ; p_run = p_run_next )
    {
        p_run_next = p_run->next ;
        if(p_run)
        {
            free(p_run);
        }
    }
    if(p_list)
    {
        free(p_list);
        p_list = NULL ;
    }
    *pp_list = NULL ;
    return(SUCCESS);
}

void generic_delete(node_t* p_delete_node)
{
    p_delete_node->next->prev=p_delete_node->prev;
    p_delete_node->prev->next=p_delete_node->next;
    free(p_delete_node);
}

node_t* get_list_node(data_t new_data)
{
    node_t* p_new_node = NULL;
    p_new_node = (node_t*)xmalloc(sizeof(node_t)) ;
    p_new_node->data = new_data ;
    return(p_new_node);
}

void* xmalloc(size_t nr_bytes)
{
    void* p = NULL ;

    p = malloc(nr_bytes);
    if(p==NULL)
    {
        fprintf(stderr , "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    memset(p , 0 , nr_bytes);
    return(0);
}


