
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct point{

    double a;
    double b;
    double c;
};

void built_in_data_type(void);
void Array_of_Built_In_Data_Type(void);
void Array_Of_Pointers_Built_in_Data_Type(void);

void User_Defined_Datatypes(void);
void Array_of_User_Defined_Datatype(void);
void Array_of_pointers_of_User_Defined_Dataypes(void);

int main(void)
{
    built_in_data_type();
    Array_of_Built_In_Data_Type() ;
    Array_Of_Pointers_Built_in_Data_Type();

    User_Defined_Datatypes();
    Array_of_User_Defined_Datatype();
    Array_of_pointers_of_User_Defined_Dataypes();
    return 0 ;
}

void built_in_data_type()
{
    int *ptr = NULL ; // declaring Pointer of integer type
    puts("Built in Data Type:");

    ptr = (int*)malloc(sizeof(int)); // Allocation Of Memory
    assert(ptr!=NULL);               //Check If Dynamic Memory Allocation Is failed
    memset(ptr,0,sizeof(int));       //Assigning Value to zero
    *ptr = 20 ;                      //Storing Value
    printf("*ptr= %d \n",*ptr);      //Write
    free(ptr);                       //release
    ptr=NULL ;                       //Making Pointer NULL

}

void Array_of_Built_In_Data_Type(void)
{
    int *ptr = NULL ;
    puts("Array_Of_Built_In_Data_Type:");

    int a_size = 5 ;

    ptr = (int*)malloc(a_size*(sizeof(int)));
    assert(ptr!=NULL) ;
    memset(ptr , 0 , a_size*(sizeof(int)));

    for(int i =0 ; i<a_size ; ++i)
    {
        *(ptr+i)= i*10 ;
    }
    for(int i=0 ; i<a_size ; ++i)
    {
        printf("a[%d] = %d\n",i ,ptr[i]);
    }

    free(ptr);
    ptr = NULL ;

}

void Array_Of_Pointers_Built_in_Data_Type(void)
{
    int** ptr = NULL ;
    puts("Array of pointers:");

    int a_size = 5 ;
    int i=0;

    ptr = (int**)malloc(a_size*sizeof(int*));
    assert(ptr!=NULL);
    memset(ptr,0,a_size*(sizeof(int*)));

    for(i=0;i<a_size;i++)
    {
        *(ptr+i) = (int*)malloc(sizeof(int));
        assert(ptr[i]!=NULL);
        *(*(ptr+i))=i*10; //*ptr[i]=i*10;
    }
    for(i=0; i<a_size ; i++)
    {
        printf("*ptr[i]=%d\n",*ptr[i]);
    }
//All memory is freeing
    for(i=0;i<a_size;i++)
    {
        free(ptr[i]);
        ptr[i]=NULL;
    }

    free(ptr);
    ptr=NULL;
}

void User_Defined_Datatypes(void)
{
    struct point *ptr = NULL;
    puts("User defined Datatypes:");

    ptr = (struct point*)malloc(sizeof(struct point));
    assert(ptr!=NULL);
    memset(ptr,0,sizeof(struct point));

    ptr->a=10.5;
    ptr->b=20.5;
    ptr->c=30.5;
    
    printf("ptr->a=%lf ptr->b =%lf ptr->c=%lf\n",ptr->a,ptr->b,ptr->c);

    free(ptr);
    ptr=NULL;

}

void Array_of_User_Defined_Datatype(void)
{
   struct point *ptr = NULL ;
    puts("Array of User Defined Datatypes:");

    int a_size =5 ;
    int i=0;

    ptr = (struct point*)malloc(a_size*sizeof(struct point));

    assert(ptr!=NULL);
    memset(ptr,0,a_size*sizeof(int));

    for(i=0 ; i<a_size; i++)
    {
        ptr[i].a=i+1.1;
        ptr[i].b=i+2.2;
        ptr[i].c=i+3.3;
    }
    for(i=0 ; i<a_size ; i++)
    {
        printf("ptr[%d].a=%lf ptr[%d].b=%lf ptr[%d].c=%lf\n",i,ptr[i].a,i,ptr[i].b,i,ptr[i].c);
    }

    free(ptr);
    ptr=NULL;
    
}

void Array_of_pointers_of_User_Defined_Dataypes(void)
{
    struct point** ptr =NULL;
    puts("Array of Pointers of UserDefined Datatypes:");

    int a_size=5;
    int i=0 ;

    ptr = (struct point**)malloc(a_size*sizeof(struct point*));
    assert(ptr!=NULL);
    memset(ptr,0,a_size*sizeof(struct point*));

    for(i=0 ; i<a_size ; ++i)
    {
        ptr[i]=(struct point*)malloc(sizeof(struct point));
        assert(ptr!=NULL);

        (ptr[i])->a=1.1*i;
        (ptr[i])->b=2.2*i;
        (ptr[i])->c=3.3*i;
    }

    for(i=0 ; i<a_size ;++i)
    {
        printf("ptr[%d]->a=%lf ptr[%d]->b=%lf ptr[%d]->c=%lf\n",i,ptr[i]->a,i,ptr[i]->b,i,ptr[i]->c);
    }

    for(i=0 ; i<a_size ; ++i)
    {
        free(ptr[i]);
        ptr[i]=NULL;
    }
    free(ptr);
    ptr=NULL;
}

