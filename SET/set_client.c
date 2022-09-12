#include "set.h"

int main(void)
{
    int set_1_data[] = {10, 20, 30, 40, 50, 60}; 
    int set_2_data[] = {50, 60, 70, 80, 90, 100}; 
    set_t* p_set_1 = NULL; 
    set_t* p_set_2 = NULL; 
    set_t* p_union_set = NULL; 
    set_t* p_intersection_set = NULL; 
    set_t* p_diff_set_1 = NULL;
    set_t* p_diff_set_2 = NULL; 
    set_t* p_symmetridc_diff_set = NULL; 
    int i; 
    status_t s; 

    p_set_1 = create_set(); 
    p_set_2 = create_set(); 

    for(i = 0; i < sizeof(set_1_data)/sizeof(set_1_data[0]); ++i)
    {
        s = add_element(p_set_1, set_1_data[i]); 
        assert(s == SUCCESS); 
    } 

    for(i = 0; i < sizeof(set_2_data)/sizeof(set_2_data[0]); ++i)
    {
        s = add_element(p_set_2, set_2_data[i]); 
        assert(s == SUCCESS); 
    } 

    show_set(p_set_1, "Set 1:"); 
    show_set(p_set_2, "Set 2:"); 

    p_union_set = set_union(p_set_1, p_set_2); 
    show_set(p_union_set, "Union of Set 1 and Set 2:"); 

    p_intersection_set = set_intersection(p_set_1, p_set_2); 
    show_set(p_intersection_set, "Intersection of Set 1 and Set 2:"); 

    p_diff_set_1 = set_difference(p_set_1, p_set_2); 
    show_set(p_diff_set_1, "Set 1 - Set 2:"); 

    p_diff_set_2 = set_difference(p_set_2, p_set_1); 
    show_set(p_diff_set_2, "Set 2 - Set 1:"); 

    p_symmetridc_diff_set = set_symmetric_difference(p_set_1, p_set_2); 
    show_set(p_symmetridc_diff_set, "Set 1 SYMMETRIC DIFFERENCE Set 2:"); 
    
    if(!is_disjoint(p_set_1, p_set_2))
        puts("Set 1 and Set 2 are NOT disjoint with each other"); 

    s = remove_element(p_set_1, 50); 
    assert(s == SUCCESS);
    s = remove_element(p_set_1, 60); 
    assert(s == SUCCESS);
    s = remove_element(p_set_2, 50);
    assert(s == SUCCESS);
    s = remove_element(p_set_2, 60); 
    assert(s == SUCCESS);

    if(is_disjoint(p_set_1, p_set_2))
        puts("Set 1 and Set 2 are disjoint with each other");    

    s = destroy_set(&p_set_1); 
    assert(s == SUCCESS); 
    s = destroy_set(&p_set_2);
    assert(s == SUCCESS);  
    s = destroy_set(&p_union_set); 
    assert(s == SUCCESS); 
    s = destroy_set(&p_intersection_set); 
    assert(s == SUCCESS); 
    s = destroy_set(&p_diff_set_1); 
    assert(s == SUCCESS); 
    s = destroy_set(&p_diff_set_2); 
    assert(s == SUCCESS); 
    s = destroy_set(&p_symmetridc_diff_set); 
    assert(s == SUCCESS); 

    p_set_1 = create_set(); 
    p_set_2 = create_set(); 

    for(i = 0; i < sizeof(set_1_data)/sizeof(set_1_data[0]); ++i)
    {
        add_element(p_set_1, set_1_data[i]); 
        add_element(p_set_2, set_1_data[i]); 
    }

    assert(add_element(p_set_2, 100)); 

    if(is_subset(p_set_1, p_set_1))
        puts("Every set is a subset of itself"); 

    if(is_superset(p_set_1, p_set_1))
        puts("Every set is a superset of itself"); 

    if(is_subset(p_set_1, p_set_2))
        puts("Set 1 is a subset of Set 2"); 

    if(is_superset(p_set_2, p_set_1))
        puts("Set 2 is a superset is Set 1"); 

    if(!is_subset(p_set_2, p_set_1))
        puts("Set 2 is not a subset of Set 1"); 

    if(!is_superset(p_set_1, p_set_2))
        puts("Set 1 is not a superset of Set 2"); 
    
    s = destroy_set(&p_set_1); 
    assert(s == SUCCESS); 
    
    s = destroy_set(&p_set_2);
    assert(s == SUCCESS);  
    
    return (EXIT_SUCCESS); 
}