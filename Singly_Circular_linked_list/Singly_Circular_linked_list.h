
#pragma once 

#define SUCCESS 1
#define TRUE    1
#define FALSE   0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY

typedef int data_t;
typedef int status_t;
typedef int len_t ;
typedef int Bool ;

typedef struct node node_t ;
typedef node_t list_t ;

struct node
{
    data_t data ;
    struct node* next ;
};

list_t* create_list(void);

status_t insert_start(list_t* p_list , data_t new_data) ;
status_t insert_end(list_t* p_list , data_t new_data) ;
status_t insert_after(list_t* p_list , data_t e_data , data_t new_data);
status_t insert_before(list_t* p_list , data_t e_data , data_t new_data);

status_t get_start(list_t* p_list , data_t* p_start_data);
status_t get_end(list_t* p_list , data_t* p_end_data);
status_t pop_start(list_t* p_list , data_t* p_start_data);
status_t* pop_end(list_t* p_list , data_t* p_start_data);;

status_t remove_start(list_t* p_list);
staus_t remove_end(list_t* p_list);
status_t remove_data(list_t* p_list , data_t r_data);

len_t get_lengh(list_t* p_list);
Bool is_empty(list_t* p_list);
Bool is_memeber(list_t* p_list , data_t s_data);
void show(list_t* p_list );


list_t* concat(list_t* p_list_1 , list_t* p_list_2);
list_t* merge(list_t* p_list_1  , list_t* p_list_2);
list_t* get_reversed_list(list_t* p_list1);

status_t append(list_t* p_list_1 , list_t* p_list2);
status_t reverse_list(list_t* p_list);

void to_array(list_t* p_list , data_t** p_array , size_t* p_size);
list_t* to_list(list_t* p_array , size_t size);

status_t destroy_list(list_t** pp_list);

static void generic_insert(list_t* p_beg , list_t* p_mid , node_t* p_end);
static void generic_delete(list_t* p_prev_node , node_t* p_delete_node ) ;
static node_t* search_node(list_t* p_list , data_t s_data);
static node_t* get_node(data_t new_data);
static void* xmalloc(size_t nr_bytes);