#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "rbtree.h"

int main(void)
{
    rbtree_t* p_rb = NULL; 
    status_t status; 
    p_rb = create_rbtree(); 

    inorder_walk(p_rb); 
    preorder_walk(p_rb); 
    postorder_walk(p_rb); 

    status = destroy_rbtree(&p_rb); 
    assert(status == SUCCESS && p_rb == NULL); 

    exit(EXIT_SUCCESS);
}