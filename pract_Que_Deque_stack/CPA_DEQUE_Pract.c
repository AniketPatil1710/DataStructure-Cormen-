/* Deque using DCLL */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* symbolic constants */

#define TRUE            1
#define SUCCESS         1
#define LIST_EMPTY      2
#define DEQUEUE_EMPTY     LIST_EMPTY

/* typedefs */

typedef int data_t ;
typedef int status_t ;
typedef int bool ;
typedef int len_t ;
typedef struct node node_t ;
typedef node_t list_t ;
typedef node_t dequeue_t ;

/* node layout def */

struct node{
    data_t data ;
    node_t* prev ;
    node_t* next ;
};

/* Dequeue Interface Routines Declarations */

dequeue_t* create_dequeue() ;
status_t empty(dequeue_t* p_dequeue ) ;
len_t size(dequeue_t* p_dequeue ) ;
status_t front(dequeue_t* p_dequeue , data_t* p_front_data ) ;
status_t back(dequeue_t* p_dequeue , data_t* p_back_data ) ;
status_t push_front(dequeue_t* p_dequeue , data_t new_data) ;
status_t push_back(dequeue_t* p_dequeue , data_t new_data ) ;
status_t pop_front(dequeue_t* p_dequeue , data_t* p_pop_data ) ;
status_t pop_back(dequeue_t* p_dequeue , data_t* p_pop_data ) ;
void show_dequeue(dequeue_t* p_dequeue , const char* msg) ;
status_t destroy_dequeue(dequeue_t** pp_dequeue) ;

/* List Interface Routines Declarations */

list_t* create_list(void) ;
status_t insert_beg(list_t* p_list , data_t new_data);
status_t insert_end(list_t* p_list , data_t new_data);
status_t get_beg(list_t* p_list , data_t* p_data);
status_t get_end(list_t* p_list , data_t* p_data);
status_t pop_beg(list_t* p_list , data_t* p_data);
status_t pop_end(list_t* p_list , data_t* p_data);
len_t get_length(list_t* p_list);
bool is_list_empty(list_t* p_list);
void show_list(list_t* p_list , const char* msg);
status_t destroy_list(list_t** pp_list);

/*List Auxillary Routines*/

void generic_insert(node_t* p_beg , node_t* p_mid , node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* get_list_node(data_t new_data);

/*Memory Allocation routines*/
void* xmalloc(size_t nr_bytes);

int main()
{
    data_t data; 
    
    dequeue_t* p_dequeue = NULL; 

    puts("\n\t\t\t DEQUEUE\n");

    p_dequeue = create_dequeue();
    show_dequeue(p_dequeue, "\n\t***** create_dequeue( ) operation *****");

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Dequeue: %d\n", size(p_dequeue));

    
	assert(empty(p_dequeue) == DEQUEUE_EMPTY);
	assert(size(p_dequeue) == 0);
    assert(front(p_dequeue, &data) == DEQUEUE_EMPTY); 
    assert(back(p_dequeue, &data) == DEQUEUE_EMPTY); 
    assert(pop_front(p_dequeue, &data) == DEQUEUE_EMPTY);
    assert(pop_back(p_dequeue, &data) == DEQUEUE_EMPTY); 



    puts("\n\n\t***** push_front( ) operations *****");
    for(data = 0; data < 5; ++data){
        assert(push_front(p_dequeue, data) == SUCCESS); 
        printf("push_front(%d)", data);
		show_dequeue(p_dequeue, "");
        puts("\n");
    }

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Queue: %d\n", size(p_dequeue));

	puts("\n\n\t***** push_back( ) operations *****");
    for(data = 5; data < 10; ++data){
        assert(push_back(p_dequeue, data) == SUCCESS); 
        printf("push_back(%d)", data);
		show_dequeue(p_dequeue, "");
        puts("\n");
    }

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Queue: %d\n", size(p_dequeue));

    puts("\n\n\t***** front( ) operation *****");
    assert(front(p_dequeue, &data) == SUCCESS);
    printf("Front data: %d\n", data);

	puts("\n\n\t***** back( ) operation *****");
    assert(back(p_dequeue, &data) == SUCCESS);
    printf("Back data: %d\n", data);
    

    puts("\n\n\t***** pop_front( ) & pop_back( ) *****");
    while(empty(p_dequeue) != DEQUEUE_EMPTY){
        assert(pop_front(p_dequeue, &data) == SUCCESS); 
        show_dequeue(p_dequeue, "pop_front(): "); 
        printf("\nPopped data: %d\n\n\n", data);

		assert(pop_back(p_dequeue, &data) == SUCCESS); 
        show_dequeue(p_dequeue, "pop_back(): "); 
        printf("\nPopped data: %d\n\n\n", data);
    }


	puts("\t***** size( ) operation *****");
	printf("Size of Dequeue: %d\n", size(p_dequeue));
    

    assert(destroy_dequeue(&p_dequeue) == SUCCESS && p_dequeue == NULL);

    return (EXIT_SUCCESS); 
}

dequeue_t* create_dequeue()
{
    return(create_list());
}

status_t empty(dequeue_t* p_dequeue)
{
    if(is_list_empty(p_dequeue))
        return (DEQUEUE_EMPTY);
}

len_t size(dequeue_t* p_dequeue)
{
    return(get_length(p_dequeue));
}
status_t front(dequeue_t* p_dequeue, data_t* p_front_data){
	return(get_beg(p_dequeue, p_front_data));
}

status_t push_front(dequeue_t* p_dequeue, data_t new_data){
	return(insert_beg(p_dequeue, new_data));
}

status_t push_back(dequeue_t* p_dequeue, data_t new_data){
	return(insert_end(p_dequeue, new_data));
}

status_t back(dequeue_t* p_dequeue, data_t* p_back_data){
	return(get_end(p_dequeue, p_back_data));
}
status_t pop_front(dequeue_t* p_dequeue , data_t* p_pop_data)
{
    return(pop_beg(p_dequeue , p_pop_data));
}

status_t pop_back(dequeue_t* p_dequeue , data_t* p_pop_data)
{
    return(pop_end(p_dequeue , p_pop_data));
}

void show_dequeue(dequeue_t* p_dequeue , const char* msg)
{
    return(show_list(p_dequeue , msg));
}

status_t destroy_dequeue(dequeue_t** pp_dequeue){
	return(destroy_list(pp_dequeue));
}


list_t* create_list(void)
{
    node_t* p_new_node = NULL ;
    p_new_node = get_list_node(0);
    p_new_node->next = p_new_node ;
    p_new_node->prev = p_new_node ;
    return(p_new_node);

}

status_t insert_beg(list_t* p_list, data_t new_data)
{
    generic_insert(p_list , get_list_node(new_data), p_list->next);
    return(SUCCESS);
}

status_t insert_end(list_t* p_list , data_t new_data)
{
    generic_insert(p_list->prev, get_list_node(new_data) , p_list);
    return (SUCCESS);
}

status_t get_beg(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
    {
        return(LIST_EMPTY);
    }
    *p_data = p_list->next->data ;

    return(SUCCESS);
}

status_t get_end(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
    {
        return(LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;
    return(SUCCESS);
}

status_t pop_beg(list_t* p_list , data_t* p_data)
{
    if(is_list_empty(p_list))
    {
        return(LIST_EMPTY);
    }
    *p_data = p_list->next->data ;
    generic_delete(p_list->next) ;

    return(SUCCESS);
}

status_t pop_end(list_t* p_list, data_t* p_data)
{
    if(is_list_empty(p_list))
    {
        return(LIST_EMPTY);
    }
    *p_data = p_list->prev->data ;
    generic_delete(p_list->prev);
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
    free(p_delete_node);
}

len_t get_length(list_t* p_list)
{
    len_t len ;
    node_t* p_run ;
    for(p_run=p_list->next , len=0 ; p_run!=p_list ; p_run=p_run->next , ++len);
    return(len);
}

bool is_list_empty(list_t* p_list)
{
    return (p_list->next == p_list && p_list->prev==p_list);
}

void show_list(list_t* p_list , const char* msg)
{
    node_t* p_run = NULL ;
    if(msg)
        puts(msg);
    printf("[Front] |");

    for(p_run = p_list->next ; p_run!=p_list ; p_run=p_run->next)
    {
        printf("[%d] |",p_run->data);
    }
    puts("[Back]");
}

status_t destroy_list(list_t** pp_list)
{
    list_t* p_list = *pp_list ;
    node_t* p_run = NULL , *p_run_next = NULL ;

    for(p_run = p_list->next ; p_run!= p_list ; p_run = p_run_next)
    {
        p_run_next = p_run->next ;
        if(p_run)
            free(p_run);
    }
    if(p_list)
    {
        free(p_list);
        p_list = NULL ;
    }
    *pp_list = NULL ;
    return(SUCCESS);
}

list_t* get_list_node(int new_data)
{
    node_t* p_new_node = NULL ;
    p_new_node = (node_t*)xmalloc(sizeof(node_t));
    p_new_node->data = new_data ;
    return(p_new_node);
}

void* xmalloc(size_t nr_bytes)
{
    void* p ;
    p = (void*)malloc(nr_bytes);

    if(p == NULL)
    {
        fprintf(stderr , "Out of memory.");
        exit(EXIT_FAILURE);
    }
    memset(p,0,nr_bytes);
    return(p);
}

