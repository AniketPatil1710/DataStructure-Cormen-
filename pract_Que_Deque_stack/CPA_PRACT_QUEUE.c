/*Queue Using DCLL*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*Symbolic Constants*/

#define TRUE        1
#define SUCCESS     1
#define LIST_EMPTY  2
#define QUEUE_EMPTY LIST_EMPTY

/*typedefs*/

typedef int data_t ;
typedef int status_t ;
typedef int bool ;
typedef int len_t ;
typedef struct node node_t ;
typedef node_t list_t ;
typedef list_t queue_t ;

/*node layout defination*/

struct node{
    data_t data  ;
    node_t* next ;
    node_t* prev ;
};

/* Queue Interface Routines Declarations*/

queue_t* create_queue();
status_t empty(queue_t* p_queue);
len_t size(queue_t* p_queue);
status_t front(queue_t* p_queue , data_t* p_front_data);
status_t back(queue_t* p_queue , data_t* p_back_data);
status_t push(queue_t* p_queue , data_t new_data);
status_t pop(queue_t* p_queue , data_t* p_pop_data);
void show_queue(queue_t* p_queue , const char* msg);
status_t destroy_queue(queue_t** pp_list);


/* List Interface routines Declarations*/
list_t* create_list(void);
status_t insert_end(list_t* p_list , data_t new_data);
status_t get_beg(list_t* p_list , data_t* p_data);
status_t get_end(list_t* p_list , data_t* p_data);
status_t pop_beg(list_t* p_list , data_t* p_data);
len_t get_length(list_t* p_list);
void show_list(list_t* p_list , const char* msg);
status_t destroy_list(list_t** p_list);
bool is_list_empty(node_t* p_list);
/* List Auxillary routines */

void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* get_list_node(data_t new_data);

/* Memory Allocation routines */

void* xmalloc(size_t nr_bytes);


int main(void)
{
  data_t data; 
    
    queue_t* p_queue = NULL; 

    puts("\n\t\t\t QUEUE\n");

    p_queue = create_queue();
    show_queue(p_queue, "\n\t***** create_queue( ) operation *****");

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Queue: %d\n", size(p_queue));

    
	assert(empty(p_queue) == QUEUE_EMPTY);
	assert(size(p_queue) == 0);
    assert(front(p_queue, &data) == QUEUE_EMPTY); 
    assert(back(p_queue, &data) == QUEUE_EMPTY); 
    assert(pop(p_queue, &data) == QUEUE_EMPTY); 


    puts("\n\n\t***** push( ) operations *****");
    for(data = 0; data < 5; ++data){
        assert(push(p_queue, data) == SUCCESS); 
        printf("push(%d)", data);
		show_queue(p_queue, "");
        puts("\n");
    }

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Queue: %d\n", size(p_queue));

    puts("\n\n\t***** front( ) operation *****");
    assert(front(p_queue, &data) == SUCCESS);
    printf("Front data: %d\n", data);

	puts("\n\n\t***** back( ) operation *****");
    assert(back(p_queue, &data) == SUCCESS);
    printf("Back data: %d\n", data);
    

    puts("\n\n\t***** pop( ) operations *****");
    while(empty(p_queue) != QUEUE_EMPTY){
        assert(pop(p_queue, &data) == SUCCESS); 
        show_queue(p_queue, "pop(): "); 
        printf("\nPopped data: %d\n\n\n", data);
    }


	puts("\t***** size( ) operation *****");
	printf("Size of Queue: %d\n", size(p_queue));
    

    assert(destroy_queue(&p_queue) == SUCCESS && p_queue == NULL);

    return (EXIT_SUCCESS); 
}

queue_t* create_queue()
{
    return(create_list());
}

status_t empty(queue_t* p_queue)
{
    if(is_list_empty(p_queue))
        return(QUEUE_EMPTY);
}

len_t size(queue_t* p_queue)
{
    return(get_length(p_queue));
}

status_t front(queue_t* p_queue , data_t* p_front_data)
{
    return(get_beg(p_queue,p_front_data));
}

status_t back(queue_t* p_queue , data_t* p_back_data)
{
    return(get_end(p_queue,p_back_data));
}

status_t push(queue_t* p_queue , data_t new_data)
{
    return(insert_end(p_queue,new_data));
}

status_t pop(queue_t* p_queue , data_t* p_pop_data)
{
    return(pop_beg(p_queue,p_pop_data));
}

void show_queue(queue_t* p_queue , const char* msg)
{
    return(show_list(p_queue , msg));
}

status_t destroy_queue(queue_t** pp_queue)
{
    return(destroy_list(pp_queue));
}
list_t* create_list(void)
{
    node_t* p_new_node = NULL ;
    p_new_node = get_list_node(0);
    p_new_node->next = p_new_node ;
    p_new_node->prev = p_new_node ;
    return(p_new_node);
}

status_t insert_end(list_t* p_list , data_t new_data)
{
    generic_insert(p_list->prev , get_list_node(new_data) , p_list);
    return(SUCCESS) ;
}

status_t get_beg(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
        return(LIST_EMPTY)
    *p_data = p_list->next->data ;

    return (SUCCESS);
}

status_t pop_beg(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
        return(LIST_EMPTY)
    *p_data = p_list->next->data ;
    generic_delete(p_list->next);

    return(SUCCESS);

}

len_t get_length(list_t* p_list)
{
    len_t len ;
    node_t* p_run = NULL ;
    for(p_run = p_list->next , len=0 ; p_run!=p_list ; p_run = p_run->next , ++len)

    return (len);
}

status_t get_end(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
        return(LIST_EMPTY)
    *p_data = p_list->prev->data ;

    return (SUCCESS);
}

status_t destroy_list(list_t** pp_list)
{
    list_t* p_list = *pp_list ;
    node_t* p_run = NULL , *p_run_next = NULL ;

    for(p_run = p_list->next ; p_run!=p_list ; p_run = p_run_next)
    {
        p_run_next = p_run->next ;
        if(p_run)
            free(p_run);
        
    }
    if(p_list)
    {
        free(p_list);
        p_list=NULL;
    }
    *pp_list = NULL ;
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
}

bool is_list_empty(list_t* p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list);
}

void show_list(list_t* p_list , const char* msg)
{
    node_t* p_run = NULL ;
    if(msg)
        puts(msg) ;
    
    printf("[FRONT] |") ;
    for(p_run = p_list->next ; p_run!=p_list ; p_run = p_run->next)
    {
        printf("[%d] |",p_run->data);
    }
    puts("[BACK]");
}
node_t* get_list_node(data_t new_data)
{
    node_t* p_new_node = NULL ;
    p_new_node = (node_t*)xmalloc(sizeof(node_t));
    p_new_node->data = new_data ;
    return(p_new_node); 
}

void* xmalloc(size_t nr_bytes)
{
    void* p;
    p = malloc(nr_bytes);
    if(p==NULL)
    {
        fprintf(stderr,"Out of Memory.");
    }
    memset(p,0,nr_bytes);
    return(p) ;
}