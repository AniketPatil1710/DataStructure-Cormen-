 #include <stdio.h>
#include <stdlib.h>

#define SUCCESS             1
#define TRUE                1
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY          3

typedef int data_t ;

struct node{
    data_t data ;
    struct node* prev;
    struct node* next;
};

typedef int status_t ;
typedef int bool ;
typedef struct node node_t ;
typedef node_t list_t ;

/*Interface Routines*/

list_t* create_list(void);
status_t isert_start(list_t* p_list , data_t new_data);
status_t insert_end(list_t p_list,data_t new_dat);
status_t insert_after(list_t* p_list,data_t existing_data, data_t new_data);
status_t insert_before(list_t* p_list, data_t existing_data, data_t new_data);
status_t remove_data(list_t* p_list, data_t r_data);
status_t remove_beg(list_t* p_list);
status_t remove_end(list_t* p_list);
bool is_list_empty(list_t* p_list);

/*Helper Routines*/

void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* search_node(list_t* p_list ,data_t search_data);
node_t* get_list_node(data_t data);
void* xmalloc(size_t nr_bytes);

int main(void)
{
    list_t* p_list = NULL ;

    p_list = create_list();

    return(EXIT_SUCCESS);
}

/* Interface Routines*/

list_t* create_list(void)
{
    list_t* p_dummy_node = NULL ;
    p_dummy_node = get_list_node(-1);
    p_dummy_node->prev = p_dummy_node ;
    p_dummy_node->next = p_dummy_node ;

    return(p_dummy_node);
} 


