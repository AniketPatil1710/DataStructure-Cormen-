#ifndef _SET_H 
#define _SET_H 

#include "list.h"

#define SET_ELEMENT_EXISTS  4 
#define SET_DATA_NOT_FOUND LIST_DATA_NOT_FOUND 
#define SET_EMPTY LIST_EMPTY 

typedef list_t set_t; 

set_t* create_set(void); 
set_t* set_union(set_t* p_set_1, set_t* p_set_2); 
set_t* set_intersection(set_t* p_set_1, set_t* p_set_2); 
set_t* set_difference(set_t* p_set_1, set_t* p_set_2); 
set_t* set_symmetric_difference(set_t* p_set_1, set_t* p_set_2); 
status_t is_subset(set_t* p_set_1, set_t* p_set_2); 
status_t is_superset(set_t* p_set_1, set_t* p_set_2); 
status_t add_element(set_t* p_set, data_t element); 
status_t remove_element(set_t* p_set, data_t element);  
status_t is_member(set_t* p_set, data_t data); 
status_t is_set_empty(set_t* p_set); 
status_t is_disjoint(set_t* p_set_1, set_t* p_set_2); 
int modset(set_t* p_set); 
void show_set(set_t* p_set, const char* msg); 
status_t destroy_set(set_t** pp_set); 

#endif /* _SET_H */ 