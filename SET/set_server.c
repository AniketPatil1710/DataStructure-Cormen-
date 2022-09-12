#include "set.h"

set_t* create_set(void)
{
    return create_list(); 
}

set_t* set_union(set_t* p_set_1, set_t* p_set_2)
{
    set_t* union_set = NULL; 
    node_t* p_run; 

    union_set = create_set(); 
    for(p_run = p_set_1->next; p_run != p_set_1; p_run = p_run->next)
        add_element(union_set, p_run->data); 
    for(p_run = p_set_2->next; p_run != p_set_2; p_run = p_run->next) 
        if(!is_member(union_set, p_run->data))
            add_element(union_set, p_run->data); 

    return (union_set); 
}

set_t* set_intersection(set_t* p_set_1, set_t* p_set_2)
{
    set_t* p_intersection_set = NULL; 
    node_t* p_run; 

    p_intersection_set = create_set(); 
    for(p_run = p_set_1->next; p_run != p_set_1; p_run = p_run->next)
        if(is_member(p_set_2, p_run->data))
            add_element(p_intersection_set, p_run->data); 

    return (p_intersection_set); 
}

set_t* set_difference(set_t* p_set_1, set_t* p_set_2)
{
    set_t* p_diff_set = NULL; 
    node_t* p_run; 

    p_diff_set = create_set(); 
    for(p_run = p_set_1->next; p_run != p_set_1; p_run = p_run->next)
        if(!is_member(p_set_2, p_run->data))
            add_element(p_diff_set, p_run->data); 

    return (p_diff_set); 
}

set_t* set_symmetric_difference(set_t* p_set_1, set_t* p_set_2)
{
    set_t* p_diff_1 = NULL; 
    set_t* p_diff_2 = NULL; 
    set_t* p_symmetric_diff = NULL; 

    p_diff_1 = set_difference(p_set_1, p_set_2); 
    p_diff_2 = set_difference(p_set_2, p_set_1); 
    p_symmetric_diff = set_union(p_diff_1, p_diff_2); 
    destroy_set(&p_diff_1); 
    destroy_set(&p_diff_2); 

    return (p_symmetric_diff); 
}

status_t is_subset(set_t* p_set_1, set_t* p_set_2)
{
    node_t* p_run; 
    for(p_run = p_set_1->next; p_run != p_set_1; p_run = p_run->next)
        if(!is_member(p_set_2, p_run->data))
            return (FALSE); 
    return (TRUE); 
}

status_t is_superset(set_t* p_set_1, set_t* p_set_2)
{
    return is_subset(p_set_2, p_set_1); 
}

status_t add_element(set_t* p_set, data_t element)
{
    if(!is_member(p_set, element))
        return insert_end(p_set, element); 
    return (SET_ELEMENT_EXISTS); 
}

status_t remove_element(set_t* p_set, data_t element)
{
    return remove_data(p_set, element); 
}

status_t is_member(set_t* p_set, data_t data)
{
    return contains(p_set, data); 
}

status_t is_set_empty(set_t* p_set)
{
    return is_list_empty(p_set); 
}

status_t is_disjoint(set_t* p_set_1, set_t* p_set_2)
{
    node_t* p_run = NULL; 
    for(p_run = p_set_1->next; p_run != p_set_1; p_run = p_run->next)
        if(is_member(p_set_2, p_run->data))
            return (FALSE); 
    return (TRUE); 
}

int modset(set_t* p_set)
{
    return get_length(p_set); 
}

void show_set(set_t* p_set, const char* msg)
{
    show_list(p_set, msg); 
}

status_t destroy_set(set_t** pp_set)
{
    return destroy_list(pp_set); 
}