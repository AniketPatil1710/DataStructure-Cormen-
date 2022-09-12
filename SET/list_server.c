#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#include "list.h"

list_t *create_list(void)
{
    node_t *p_new_node = NULL; 
    p_new_node = get_list_node(0); 
    p_new_node->next = p_new_node; 
    p_new_node->prev = p_new_node; 
    return (p_new_node); 
}

status_t insert_beg(list_t *p_list, data_t new_data)
{
    generic_insert(p_list, get_list_node(new_data), p_list->next); 
    return (SUCCESS); 
}

status_t insert_end(list_t *p_list, data_t new_data)
{
    generic_insert(p_list->prev, get_list_node(new_data), p_list); 
    return (SUCCESS); 
}

status_t insert_after(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *pe_node = locate_node(p_list, e_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_insert(pe_node, get_list_node(new_data), pe_node->next); 
    return (SUCCESS); 
}

status_t insert_before(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *pe_node = locate_node(p_list, e_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_insert(pe_node->prev, get_list_node(new_data), pe_node); 
    return (SUCCESS); 
}

status_t get_beg(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *p_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *p_data = p_list->prev->data; 
    return (SUCCESS); 
}

status_t pop_beg(list_t *p_list, data_t *pp_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *pp_data = p_list->next->data; 
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t pop_end(list_t *p_list, data_t *pp_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *pp_data = p_list->prev->data; 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

status_t remove_beg(list_t *p_list)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY); 
    }
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t remove_end(list_t *p_list)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY); 
    }
    generic_delete(p_list->prev); 
    return (SUCCESS);
}

status_t remove_data(list_t *p_list, data_t r_data)
{
    node_t *pe_node = locate_node(p_list, r_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_delete(pe_node); 
    return (SUCCESS); 
}

len_t get_length(list_t *p_list)
{
    node_t *p_run; 
    len_t len; 
    for(p_run = p_list->next, len = 0; p_run != p_list; p_run = p_run->next, ++len)
    {
    }
    return (len); 
}

bool contains(list_t *p_list, data_t search_data)
{
    return (locate_node(p_list, search_data) != NULL);
}

bool is_list_empty(list_t *p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list); 
}

int get_repeat_count(list_t *p_list, data_t search_data)
{
    int count = 0; 
    list_t *p_run; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        if(p_run->data == search_data)
        {
            ++count; 
        } 
    }
    return (count); 
}

void show_list(list_t *p_list, const char *msg)
{
    node_t *p_run; 
    if(msg)
    {
        puts(msg); 
    }
    printf("[BEG]<->"); 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        printf("[%d]<->", p_run->data); 
    }
    puts("[END]"); 
}


list_t *concat_lists(list_t *p_list1, list_t *p_list2)
{
    list_t *p_new_list = create_list(); 
    node_t *p_run; 
    for(p_run = p_list1->next; p_run != p_list1; p_run = p_run->next)
    {
        insert_end(p_new_list, p_run->data); 
    }
    for(p_run = p_list2->next; p_run != p_list2; p_run = p_run->next)
    {
        insert_end(p_new_list, p_run->data); 
    }
    return (p_new_list); 
}

list_t *merge_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_merge_list = create_list(); 
    node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next; 
    
    while(TRUE)
    {
        if(p_run1 == p_list1)
        {
            while(p_run2 != p_list2)
            {
                insert_end(p_merge_list, p_run2->data); 
                p_run2 = p_run2->next; 
            }
            break; 
        }
        if(p_run2 == p_list2)
        {
            while(p_run1 != p_list1)
            {
                insert_end(p_merge_list, p_run1->data); 
                p_run1 = p_run1->next; 
            }
            break; 
        }
        if(p_run1->data <= p_run2->data)
        {
            insert_end(p_merge_list, p_run1->data); 
            p_run1 = p_run1->next; 
        }
        else
        {
            insert_end(p_merge_list, p_run2->data); 
            p_run2 = p_run2->next; 
        }
    }
    return (p_merge_list); 
}

list_t *get_reversed_list(list_t *p_list)
{
    list_t *p_reversed_list = create_list(); 
    node_t *p_run; 
    p_run = p_list->prev; 
    while(p_run != p_list)
    {
        insert_end(p_reversed_list, p_run->data); 
        p_run = p_run->prev; 
    }
    return (p_reversed_list); 
}

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size){
    data_t *p_array = NULL; 
    len_t list_len = 0; 
    node_t *p_run; 
    int i; 
    list_len = get_length(p_list); 

    p_array = (data_t*)xmalloc(list_len * sizeof(data_t)); 
    for(p_run = p_list->next, i = 0; p_run != p_list; p_run = p_run->next, ++i)
    {
        p_array[i] = p_run->data; 
    }

    if(list_len != 0)
    {
        *pp_array = p_array; 
        *p_size = list_len; 
    }

    return (SUCCESS); 
}

list_t *array_to_list(data_t *p_array, size_t size)
{
    list_t *p_new_list = create_list(); 
    int i; 
    for(i = 0; i < size; ++i)
    {
        insert_end(p_new_list, p_array[i]); 
    }
    return (p_new_list); 
}

status_t append_list(list_t *p_list1, list_t **pp_list2)
{
    list_t* p_list2 = *pp_list2; 
    if(is_list_empty(p_list2) == TRUE)
        goto out; 
    p_list1->prev->next = p_list2->next; 
    p_list2->next->prev = p_list1->prev;
    p_list1->prev = p_list2->prev; 
    p_list2->prev->next = p_list1; 
out: 
    free(p_list2);  
    *pp_list2 = NULL; 
    return (SUCCESS); 
}

status_t reverse_list(list_t *p_list)
{
    node_t *p_run, *p_run_prev, *p_prev_orig;
    p_prev_orig = p_list->prev;  
    for(p_run = p_list->prev->prev; p_run != p_list; p_run = p_run_prev)
    {
        p_run_prev = p_run->prev; 
        generic_insert(p_list->prev, p_run, p_list); 
    }
    p_prev_orig->prev = p_list; 
    p_list->next = p_prev_orig; 
    return (SUCCESS); 
}

status_t destroy_list(list_t **pp_list)
{
    list_t *p_list = *pp_list; 
    node_t *p_run, *p_run_next; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next; 
        free(p_run); 
    }
    free(p_list); 
    *pp_list = NULL; 
    return (SUCCESS); 
}

static void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

static void generic_delete(node_t *p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev; 
    p_delete_node->prev->next = p_delete_node->next; 
    free(p_delete_node); 
}

static node_t *locate_node(list_t *p_list, data_t search_data)
{
    node_t *p_run; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        if(p_run->data == search_data)
        {
            return (p_run); 
        }
    }
    return (NULL); 
}

static node_t *get_list_node(data_t new_data)
{
    node_t *p_new_node = NULL; 
    p_new_node = (node_t*)xmalloc(sizeof(node_t)); 
    p_new_node->data = new_data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 
    return (p_new_node); 
}

static void *xmalloc(size_t size_in_bytes)
{
    void *p = NULL; 
    p = malloc(size_in_bytes); 
    assert(p != NULL); 
    return (p); 
}