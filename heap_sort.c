#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define LEFT(i)		(2*i+1)
#define RIGHT(i)	(2*(i+1))
#define PARENT(i) 	((i-1)/2)

struct heap{
	int* a; 
	size_t arr_size; 
	size_t heap_size; 
}; 

struct heap* get_heap(size_t heap_size)
{
	struct heap* p_heap = (struct heap*)malloc(sizeof(struct heap)); 
	assert(p_heap != NULL); 
	p_heap->arr_size = heap_size; 
	p_heap->heap_size = heap_size; 
	p_heap->a = (int*)malloc(heap_size*sizeof(int)); 
	assert(p_heap->a != NULL); 
	memset(p_heap->a, 0, heap_size*sizeof(int)); 
	return (p_heap); 
}

void input(struct heap* p_heap)
{
	int i; 
	srand(time(0)); 
	for(i = 0; i < p_heap->arr_size; ++i)
		p_heap->a[i] = rand(); 
}

void output(struct heap* p_heap)
{
	int i; 
	for(i = 0; i < p_heap->arr_size; ++i)
		printf("p_heap->arr[%d]:%d\n", i, p_heap->a[i]); 	
}

/* 
Precondition: 
	LST rooted at i is max_heap 
	RST rooted at i is max_heap 
Postcondition: 
	Subtree rooted at i is max_heap
*/ 	

void max_heapify(struct heap* p_heap, int i)
{
	int left_index, right_index, largest_index; 
	int tmp; 

	left_index = LEFT(i); 
	right_index = RIGHT(i); 

	largest_index = i; 

	if(left_index < p_heap->heap_size && p_heap->a[left_index] > p_heap->a[largest_index])
		largest_index = left_index; 

	if(right_index < p_heap->heap_size && p_heap->a[right_index] > p_heap->a[largest_index])
		largest_index = right_index; 

	if(largest_index != i)
	{
		tmp = p_heap->a[largest_index]; 
		p_heap->a[largest_index] = p_heap->a[i]; 
		p_heap->a[i] = tmp; 
		max_heapify(p_heap, largest_index); 
	}
}

/* 	
Precondition: 
	p_heap->a : of size p_heap->arr_size 
	is completely filled with random content 
	
Postcondition: 
	Convert this array into max_heap
Hint: 
	You have to use max_heapify()
	approx. half number of times as that of 
	size of an array
*/ 
void build_max_heap(struct heap* p_heap)
{
	int k; 
	for(k = PARENT(p_heap->arr_size-1); k >= 0; k--)
		max_heapify(p_heap, k); 
}

void heap_sort(struct heap* p_heap)
{
	int k, tmp; 

	build_max_heap(p_heap); 

	for(k = p_heap->heap_size-1; k > 0; k--)
	{
		tmp = p_heap->a[k]; 
		p_heap->a[k] = p_heap->a[0]; 
		p_heap->a[0] = tmp; 
		p_heap->heap_size--; 
		max_heapify(p_heap, 0); 
	}

	p_heap->heap_size = p_heap->arr_size; 
}

void put_heap(struct heap* p_heap)
{
	free(p_heap->a); 
	free(p_heap); 
}

void show(struct heap* p_heap, char* msg)
{
	int i; 

	if(msg)
		puts(msg); 

	for(i = 0; i < p_heap->heap_size; i++)
		printf("p_heap->a[%d]:%d\n", i, p_heap->a[i]); 
}

int main(int argc, char* argv[]){
	
	if(argc == 1){
		fprintf(stderr, "%s nr_elements\n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	struct heap* p_heap = get_heap(atoi(argv[1])); 
	input(p_heap); 
	show(p_heap, "before sort:"); 
	heap_sort(p_heap); 
	show(p_heap, "after sort:"); 
	put_heap(p_heap); 
	p_heap = NULL; 
	return (EXIT_SUCCESS); 
}

/* 
n*lg(n)
No adversary 
In place
*/ 