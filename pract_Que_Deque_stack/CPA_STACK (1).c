/* STACK Using DCLL */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/* Symbolic constants */ 

#define TRUE                1
#define SUCCESS             1
#define LIST_EMPTY          2 
#define STACK_EMPTY         LIST_EMPTY 


/* typedefs */ 

typedef int data_t;
typedef int status_t;
typedef int bool;
typedef int len_t;
typedef struct node node_t;
typedef node_t list_t;
typedef list_t stack_t; 


/* node layout defination */

struct node{
	data_t data;
	node_t* prev;
	node_t* next;
};


/* Stack Interface Routines Declarations */

stack_t* create_stack(void); 
status_t empty(stack_t* p_stack); 
len_t size(stack_t* p_stack);
status_t top(stack_t* p_stack, data_t* p_top_data); 
status_t push(stack_t* p_stack, data_t new_data);  
status_t pop(stack_t* p_stack, data_t* p_pop_data); 
void show_stack(stack_t* p_stack, const char* msg);
status_t destroy_stack(stack_t** pp_stack); 



/* List Interface Routines Declarations */

list_t* create_list(void);
status_t insert_end(list_t* p_list, data_t new_data);
status_t get_end(list_t* p_list, data_t* p_data);
status_t pop_end(list_t* p_list, data_t* p_data);
len_t get_length(list_t* p_list);
bool is_list_empty(list_t* p_list);
void show_list(list_t* p_list, const char* msg);
status_t destroy_list(list_t** pp_list);


/* List Auxillary routines */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* get_list_node(data_t new_data);


/* Memory Alloation routine */
void* xmalloc(size_t nr_bytes);



int main(void){   

    data_t data; 
    
    stack_t* p_stack = NULL; 

    puts("\n\t\t\t STACK\n");

    p_stack = create_stack();
    show_stack(p_stack, "\n\t***** create_stack( ) operation *****");
    
	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Stack: %d\n", size(p_stack));
    
	
	assert(empty(p_stack) == STACK_EMPTY);
	assert(size(p_stack) == 0);
    assert(top(p_stack, &data) == STACK_EMPTY); 
    assert(pop(p_stack, &data) == STACK_EMPTY);


    puts("\n\n\t***** push( ) operations *****");
    for(data = 0; data < 5; ++data){
        assert(push(p_stack, data) == SUCCESS); 
        printf("push(%d)", data);
		show_stack(p_stack, "");
        puts("\n");
    }

	puts("\n\n\t***** size( ) operation *****");
	printf("Size of Stack: %d\n", size(p_stack));

    puts("\n\n\t***** top( ) operation *****");
    assert(top(p_stack, &data) == SUCCESS);
    printf("Top data: %d\n", data);

    puts("\n\n\t***** pop( ) operations *****");
    while(empty(p_stack) != STACK_EMPTY){
        assert(pop(p_stack, &data) == SUCCESS); 
        show_stack(p_stack, "pop(): "); 
        printf("\nPopped data: %d\n\n\n", data);
    }
    

	puts("\t***** size( ) operation *****");
	printf("Size of Stack: %d\n", size(p_stack));


    assert(destroy_stack(&p_stack) == SUCCESS && p_stack == NULL);

    return (EXIT_SUCCESS); 
}


stack_t* create_stack(){
    return(create_list()); 
}

status_t empty(stack_t* p_stack){
    if(is_list_empty(p_stack))
		return(STACK_EMPTY); 
}

len_t size(stack_t* p_stack){
	return(get_length(p_stack));
}

status_t top(stack_t* p_stack, data_t* p_top_data){
    return(get_end(p_stack, p_top_data)); 
}

status_t push(stack_t* p_stack, data_t new_data){
    return(insert_end(p_stack, new_data)); 
}

status_t pop(stack_t* p_stack, data_t* p_pop_data){
    return(pop_end(p_stack, p_pop_data)); 
}

void show_stack(stack_t* p_stack, const char* msg){
    return(show_list(p_stack, msg));
}

status_t destroy_stack(stack_t** pp_stack){
    return(destroy_list(pp_stack)); 
}


list_t* create_list(void){
	node_t* p_new_node = NULL;
	p_new_node = get_list_node(0);
	p_new_node->next = p_new_node;
	p_new_node->prev = p_new_node;
	return(p_new_node);
}

status_t insert_end(list_t* p_list, data_t new_data){
	generic_insert(p_list->prev, get_list_node(new_data), p_list);
	return(SUCCESS);
}

status_t get_end(list_t* p_list, data_t* p_data){
	if(is_list_empty(p_list))
		return(LIST_EMPTY);
	*p_data = p_list->prev->data;
	return(SUCCESS);
}

status_t pop_end(list_t* p_list, data_t* p_data){
	if(is_list_empty(p_list))
		return(LIST_EMPTY);
	*p_data = p_list->prev->data;
	generic_delete(p_list->prev);
	return(SUCCESS);
}

len_t get_length(list_t* p_list){
	len_t len;
	node_t* p_run = NULL;
	for(p_run = p_list->next, len = 0; p_run != p_list; p_run = p_run->next, ++len);
	return(len);
}

bool is_list_empty(list_t* p_list){
	return(p_list->next == p_list && p_list->prev == p_list);
}

void show_list(list_t* p_list, const char* msg){
	node_t* p_run = NULL;
	if(msg)
		puts(msg);
	
	printf("[TOP]\n");
    printf("________\n");

	for(p_run = p_list->prev; p_run != p_list; p_run = p_run->prev)
		printf("[%d]\n", p_run->data);
    
    printf("________\n");
	puts("[BOTTOM]");
}

status_t destroy_list(list_t** pp_list){
	list_t* p_list = *pp_list;
	node_t* p_run = NULL, * p_run_next = NULL;
	for(p_run = p_list->next; p_run != p_list; p_run = p_run_next){
		p_run_next = p_run->next;
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

node_t* get_list_node(data_t new_data){
	node_t* p_new_node = NULL;
	p_new_node = (node_t*)xmalloc(sizeof(node_t));
	p_new_node->data = new_data;
	return(p_new_node);
}

void* xmalloc(size_t nr_bytes){
	void* p = NULL;
	p = malloc(nr_bytes);
	if(p == NULL){
		fprintf(stderr, "Out of Memory.");
		exit(EXIT_FAILURE);
	}
	memset(p, 0, nr_bytes);
	return(p);
}
