/* Doubly Circular Linked List */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*Simply Constants */

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY 3

/* Typedefs */

typedef int data_t ;
typedef int status_t;
typedef int len_t ;
typedef int bool ;
typedef struct node node_t ;
typedef struct node node_t ;
typedef node_t list_t;

/*node layout defination*/

struct node{
    data_t data ;
    struct node *prev;
    struct node *next;
};

/*interface routines declarartions*/

list_t *create_list(void);

status_t insert_beg(list_t *p_list,data_t new_data);
status_t insert_end(list_t *p_list,data_t new_data);
status_t insert_after(list_t *p_list,data_t e_data , data_t new_data);
status_t insert_before(ist_t *p_list,data_t e_data,mdata_t new_data);

status_t get_beg(list_t *p_list,data_t new_data);
status_t get_end(list_t *p_list,data_t *p_data);
status_t pop_beg(list_t *p_list,data_t *p_data);
status_t pop_end(list_t *p_list,data_t *p_data);

status_t remove_beg(list_t *p_list);
status_t remove_data(list_t *p_list , data_t r_data);
status_t remove_end(list_t *p_list);

len_t get_length(list_t *p_list);
bool contains(list_t *p_list,data_t search_data);
bool is_list_empty(list_t *p_list);
int get_repeat_count(list_t *p_list , data_t search_data);
void show_list(list_t *p_list,const char *msg);

list_t *concat_lists(list_t *p_list1 , list_t *p_list2);

list_t *merge_lists(list_t p_list1 , list_t *p_list2);
list_t *get_reversed_list(list_t *p_list);

status_t list_to_array(list_t *p_list , data_t **pp_array , size_t *p_size);
status_t *array_to_list(data_t *p_array , size_t size);

/*list auxillary routines*/

void generic_insert(node_t *p_beg , node_t *p_mide , node_t *p_end);
void generic_delete(node_t *p_delete_node);
node_t *locate_node(list_t *p_list,data_t search_data);
node_t *get_list_node(data_t new_data);

/*memory allocation routines*/

void xmalloc(size_t size_in_bytes);

int *xmalloc(size_t size_in_bytes);

int main(void)
{
    status_t s;
    data_t data;
    len_t len ;
    list_t *p_list = NULL ;
    list_t *p_list1 = NULL , *p_list2 = NULL ;
    list_t *p_concat_list = NULL;
    list_t *p_merge_list = NULL ;
    list_t *p_reversed_list = NULL;

    p_list = create_list();

    assert(get_beg(p_list , &data) == LIST_EMPTY);
}

list_t *create_list(void)
{
    node_t *p_new_node = NULL:
    p_new_node = get_list_node(0);
    p_new_node->next = p_new_node;
    p_new_node->prev = p_new_node;
    return(p_new_node);
}

status_t insert_beg(list_t *p_list , data_t new_data);
{
    generic_insert(p_list , get_list_node(new_data) , p_list->next);
    return(SUCCESS);
}

status_t insert_end(list_t *p_list , data_t new_data)
{
    generic_insert(p_list->prev , get_list_node(new_data),p_list);
    return(SUCCESS);
}

status_t insert_after(list_t *p_list,data_t e_data ,data_t new_data)
{
    node_t *pe_node = locate_node(p_list , e_data);
    if(pe_data ==NULL)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    generic_insert(pe_node , get_list_node(e_data),pe_node->next);
    return(SUCCESS);
}

status_t insert_before(list_t *p_list , data_t e_data , data_t new_data)
{
    node_t *pe_node = locate_node(p_list , e_data);
    if(pe_node == NULL)
    {
        return(LIST_DATA_NOT_FOUND);
    }

    generic_insert(pe_node , get_list_node(new_data),pe_node->next);
    return(SUCCESS);
}

status_t get_beg(list_t *p_list , data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY);
    }
    *p_data = p_list->next->data ;
    return(SUCCESS);
}

status_t get_end(list_t *p_list , data_t *p_data)
{
    if(is_list_empty(p_list) ==TRUE)
    {
        return (LIST_EMPTY);
    }

    *p_data = p_list->prev->data ;
    return(SUCCESS);

}

status_t pop_beg(list_t *p_list , data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY);
    }
    *p_data = p_list->prev->data;
    generic_delete(p_list->next);
    return(SUCCESS);
}

status_t pop_end(list_t *p_list , data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return(LIST_EMPTY);
    }

    *p_data = p_list->next->data ;
    generic_delete(p_list->end);

    return (SUCCESS);
}

status_t pop_end(list_t *p_list,)

void generic_insert(node_t *p_beg , node_t *p_mid , node_t *p_end)
{
    p_mid->next = p_end ;
    p_mid->prev = p_beg ;
    p_beg->next = p_mid ;
    p_end->prev = p_mid ;
}

void generic_delete(node_t *p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev ;
    p_delete_node->prev->next = p_delete_node->next ;
    free(p_delete_node);
}

node_t* locate_node(list_t *p_list , data_t search_data)
{
    node_t *p_run ;
    for(p_run = p_list->next ; p_run!=p_list ; p_run = p_run->next)
    {
        if(p_run->data == search_data)
        {
            return(p_run);
        }
    }

    return(NULL);
}
node_t *get_list_node(data_t new_data)
{
    node_t *p_new_node = NULL ;
    p_new_node = (node_t*)xmalloc(sizeof(node_t));
    p_new_node->data = new_data ;
    p_new_node->prev = NULL ;
    p_new_node->next = NULL ;
    return(p_new_node);

}



void *xmalloc(size_t size_in_bytes)
{
    void *p= NULL;
    p = malloc(size_in_bytes);
    assert(p,0,sizeof(node_t));

    return(0);
}
