#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define SUCCESS                 1
#define FAILURE                 0
#define LIST_DATA_NOT_FOUND     0
#define LIST_EMPTY              0

typedef struct node list_t ; 
typedef struct node node_t ; 
typedef int data_t ;
typedef int status_t ;
typedef int len_t ;
typedef int bool ;

struct node{
    int data ;
    node_t* next ;
    node_t* prev ;
};

list_t* create_list(void);
node_t* get_node(data_t new_data ) ;
node_t* locate_node(list_t* p_list , data_t l_data);

status_t insert_end(list_t* p_list , data_t new_data) ;
status_t insert_beg(list_t* p_list , data_t new_data) ;
status_t insert_after(list_t* p_list , data_t e_data , data_t new_data);
status_t insert_before(list_t* p_list , data_t e_data , data_t new_data);

status_t get_beg(list_t *p_list, data_t *p_data); 
status_t get_end(list_t *p_list, data_t *p_data); 
status_t pop_beg(list_t *p_list, data_t *p_data); 
status_t pop_end(list_t *p_list, data_t *p_data); 
status_t destroy_list(list_t **pp_list); 
status_t remove_end(list_t* p_list);
status_t remove_beg(list_t* p_list);
status_t remove_data(list_t* p_list , data_t r_data);

status_t append_list(list_t *p_list1, list_t *p_list2);  
status_t reverse_list(list_t *p_list); 

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size); 
list_t *array_to_list(data_t *p_array, size_t size); 

len_t get_length(list_t* p_list);


bool is_list_empty(list_t* p_list);
bool contains(list_t *p_list, data_t search_data); 
int get_repeat_count(list_t *p_list, data_t search_data); 

void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end);
void generic_delete(node_t* p_delete_node) ;
void show_list(list_t* p_list ,const char* msg);

void* xmalloc(size_t nr_bytes);

int main(void)
{
    int i ;
    list_t* p_list = NULL ;
    p_list = create_list() ;
    int status ;
    int data ;
    int *p_array ;
    size_t size;

    for(i=0 ; i<8 ; ++i)
    {
        insert_end(p_list,i*10);
    }

    show_list(p_list,"Our List:");

    for(i=0 ; i<5 ; ++i)
    {
        insert_beg(p_list,i*20);
    }

    show_list(p_list , "After insert beg:") ;

    remove_beg(p_list);
    remove_beg(p_list);

    show_list(p_list , "After removing first nodes:");
    printf("length of list = %d" , get_length(p_list));
    remove_end(p_list);
    remove_end(p_list);

    show_list(p_list , "After removing last node's:");
    printf("length of list = %d" , get_length(p_list));
    status = remove_data(p_list,20) ;

    show_list(p_list , "After delete:");
    status = remove_data(p_list , 200);

    if(status==0)
    {
        printf("200 is not present\n");
    }
    
    show_list(p_list , "Aftere delete:");

    printf("length of list = %d" , get_length(p_list));

    insert_after(p_list , 30 , 200 ) ;
    show_list(p_list , "After inserting 200 after 30:");
    insert_before(p_list , 40, 300) ;
    show_list(p_list , "After inserting 300 before 40:");
    
    get_beg(p_list,&data);
    printf("\n\n\nbegin node is:%d\n",data);

    get_end(p_list , &data) ;

    printf("last node:%d\n",data);

    pop_beg(p_list,&data);

    printf("poped begin data:%d\n",data);
    show_list(p_list , "After pop:");

    pop_end(p_list,&data);

    printf("poped begin data:%d\n",data);
    show_list(p_list , "After pop end:");
    
    list_to_array(p_list , &p_array , &size);

    for(int i=0 ; i<size ; ++i)
    {
        printf("arr[%d] = %d ->",i,p_array[i]);
    }
    
    reverse_list(p_list);
    show_list(p_list , "Reversed list:");
    return (SUCCESS);
}

list_t* create_list()
{
    list_t* p_list = NULL ;
    p_list = get_node(0);
    p_list->next = p_list ;
    p_list->prev = p_list ;
    return (p_list);
}

status_t insert_end(list_t* p_list , data_t new_data)
{
    generic_insert(p_list->prev , get_node(new_data) , p_list);
    return(SUCCESS);
}

status_t insert_beg(list_t* p_list , data_t new_data)
{
    generic_insert(p_list , get_node(new_data) , p_list->next);
    return(SUCCESS);
}

status_t remove_end(list_t* p_list)
{
    /*list_t* p_node = p_list->prev ;
    p_list->prev->prev->next = p_list ;
    p_list->prev = p_list->prev->prev ;

    free(p_node)*/

    generic_delete(p_list->prev) ;
    return (SUCCESS);
}

status_t remove_beg(list_t* p_list)
{
    generic_delete(p_list->next);
    return(SUCCESS);
}

void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end)
{
    p_mid->next = p_end ;
    p_mid->prev = p_beg ;
    p_beg->next = p_mid ;
    p_end->prev = p_mid ;
}

void generic_delete(node_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next ;
    p_delete_node->next->prev = p_delete_node->prev ;

    free(p_delete_node) ;
    p_delete_node = NULL ;
}

node_t* locate_node(list_t* p_list , data_t l_data)
{
    node_t* p_run = NULL ;

    for(p_run = p_list->next ; p_run!=p_list ; p_run=p_run->next)
    {
        if(p_run->data==l_data)
        {
            return(p_run);
        }
    }
    return (NULL);
}

status_t remove_data(list_t* p_list , data_t r_data)
{
    node_t* p_del_node = locate_node(p_list , r_data);

    if(p_del_node==NULL)
    {
        return(LIST_DATA_NOT_FOUND);
    }
    generic_delete(p_del_node);
    return (SUCCESS);
}

status_t append_list(list_t *p_list1, list_t *p_list2)
{
    p_list1->prev->next = p_list2->next ;
    p_list2->prev->next = p_list1 ;
    p_list2->next->prev = p_list1->prev ;
    p_list1->prev = p_list2->prev ;
    free(p_list2);
    p_list2 = NULL ;
    return(SUCCESS);    
}

status_t insert_after(list_t* p_list , data_t e_data , data_t new_data)
{
    node_t* p_node = locate_node(p_list , e_data) ;

    if(p_node==NULL)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    generic_insert(p_node , get_node(new_data) , p_node->next) ;

    return (SUCCESS) ;
}

status_t insert_before(list_t* p_list , data_t e_data , data_t new_data)
{
    node_t* p_node = locate_node(p_list , e_data);

    if(p_node == NULL )
    {
        return(LIST_DATA_NOT_FOUND);
    }

    generic_insert(p_node->prev , get_node(new_data) , p_node) ;
    return (SUCCESS);
}

bool is_list_empty(list_t* p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list);
}

status_t get_beg(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }

    *p_data = p_list->next->data ;
    return(SUCCESS);
}

status_t get_end(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;

    return(SUCCESS) ;
} 

status_t pop_beg(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }

    *p_data = p_list->next->data ;
    generic_delete(p_list->next) ;

    return(SUCCESS);
}

status_t pop_end(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;
    generic_delete(p_list->prev) ;

    return(SUCCESS);
} 

bool contains(list_t *p_list, data_t search_data)
{
    return (locate_node(p_list,search_data) != NULL) ;
}

len_t get_length(list_t* p_list)
{
    list_t* p_run = NULL ;
    int len ;

    for(p_run=p_list->next , len=0 ; p_run!=p_list ; p_run = p_run->next , ++len);

    return(len);
}

void show_list(list_t* p_list , const char* msg)
{
    node_t* p_run = NULL ;

    if(msg)
        puts(msg);

    for(p_run = p_list->next ; p_run!=p_list ; p_run = p_run->next)
    {
        printf("[%d]->",p_run->data);
    }
    printf("\n");
}

node_t* get_node(data_t new_data)
{
    node_t* p_node = NULL ;
    p_node = (node_t*) xmalloc(sizeof(node_t));
    p_node->data = new_data ;
    p_node->next = NULL ;
    p_node->prev = NULL ;

    return (p_node);
}

status_t list_to_array(list_t* p_list , int** pp_array , size_t* p_size)
{
    data_t* p_array ;
    len_t list_len ;
    node_t* p_run ;
    int i ;

    list_len = get_length(p_list); 
    p_array = (data_t*)xmalloc(list_len * sizeof(data_t));

    for(p_run=p_list->next , i=0 ; p_run!=p_list ; p_run = p_run->next , ++i)
    {
        p_array[i] = p_run->data;
    }
    *pp_array = p_array ;
    *p_size = list_len ;
    return(SUCCESS) ;
}
list_t *array_to_list(data_t *p_array, size_t size)
{
    list_t* p_list = create_list();
    int i ;
    for(i=0 ; i<size ; ++i)
    {
        insert_end(p_list,p_array[i]);
    }

    return(p_list);
}

status_t reverse_list(list_t *p_list)
{
    node_t *p_run , *p_prev_run , *p_prev_orig ;

    p_prev_orig = p_list->prev ;

    for(p_run = p_list->prev->prev ; p_run != p_list ; p_run = p_prev_run )
    {
        p_prev_run = p_run->prev ;
        generic_insert(p_list->prev , p_run , p_list );
    }
    p_prev_orig->prev = p_list ;
    p_list->next = p_prev_orig ;
    return(SUCCESS);
}
int get_repeat_count(list_t *p_list, data_t search_data)
{
    int count = 0 ;
    node_t* p_run = NULL ;

    for(p_run=p_list->next ; p_run!=p_list ; p_run = p_run->next)
    {
        if(p_run->data = search_data)
        {
            ++count ;
        }
    }

    return (count) ;
}

status_t destroy_list(list_t **pp_list)
{
    list_t* p_list = *pp_list ;
    node_t* p_run, *p_prev_run;

    for(p_run = p_list->next ; p_run!=p_list ; p_run = p_prev_run)
    {
        p_prev_run = p_run->next ;
        free(p_run) ;
    }
    free(p_list);
    p_list = NULL ;
    return (SUCCESS);
}

void* xmalloc(size_t nr_bytes)
{
    void *p = NULL ;
    p = malloc(nr_bytes) ;
    assert(p);
    memset(p,0,nr_bytes);
    return(p);
}
