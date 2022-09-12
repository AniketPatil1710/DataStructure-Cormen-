/* Doubly Circular Linked List */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

/* Symbolic constants */ 

#define TRUE 1
#define FALSE 0 
#define SUCCESS 1 
#define FAILURE 0 
#define LIST_DATA_NOT_FOUND 2 
#define LIST_EMPTY 3 

/* typedefs */ 
typedef int data_t; 
typedef int status_t; 
typedef int len_t; 
typedef int bool; 
typedef struct node node_t; 
typedef node_t list_t; 

// typedef enum {FALSE=0, TRUE} bool; 

/* node layout definition */ 
struct node{
    data_t data; 
    struct node *prev; 
    struct node *next; 
}; 

/* interface routines declarations */ 
list_t *create_list(void); 

status_t insert_beg(list_t *p_list, data_t new_data); 
status_t insert_end(list_t *p_list, data_t new_data); 
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data); 
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data); 

status_t get_beg(list_t *p_list, data_t *p_data); 
status_t get_end(list_t *p_list, data_t *p_data); 
status_t pop_beg(list_t *p_list, data_t *p_data); 
status_t pop_end(list_t *p_list, data_t *p_data); 

status_t remove_beg(list_t *p_list); 
status_t remove_end(list_t *p_list); 
status_t remove_data(list_t *p_list, data_t r_data); 

len_t get_length(list_t *p_list); 
bool contains(list_t *p_list, data_t search_data); 
bool is_list_empty(list_t *p_list); 
int get_repeat_count(list_t *p_list, data_t search_data); 
void show_list(list_t *p_list, const char *msg); 

list_t *concat_lists(list_t *p_list1, list_t *p_list2); 
// status_t concat_lists_1(list_t* p_list1, list_t* p_list2, list_t** pp_concat_list); 
list_t *merge_lists(list_t *p_list1, list_t *p_list2); 
// status_t concat_lists_2(list_t* p_list1, list_t* p_list2, list_t** pp_list); 
list_t *get_reversed_list(list_t *p_list); 
// status_t get_reversed_list(list_t* p_list, list_t** pp_reversed_list); 

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size); 
list_t *array_to_list(data_t *p_array, size_t size); 
 
status_t append_list(list_t *p_list1, list_t **pp_list2);  
status_t reverse_list(list_t *p_list); 
status_t destroy_list(list_t **pp_list); 

/* list auxillary routines */ 
static void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end); 
static void generic_delete(node_t *p_delete_node); 
static node_t *locate_node(list_t *p_list, data_t search_data); 
static node_t *get_list_node(data_t new_data); 

/* memory allocation routines */ 

static void *xmalloc(size_t size_in_bytes); 