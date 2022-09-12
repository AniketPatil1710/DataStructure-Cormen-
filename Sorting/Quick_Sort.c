/*Quick sort by Aniket*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define TRUE 1
#define CAP  10000000

void input(int *pa,int size);
void output(int *pa, int size , const char* msg);
int partition(int *pa , int start  , int end);
void quick_sort(int *pa,int start,int end);
void sort(int *pa,int size);

int main(int argc,char *argv[])
{

    int *pa = NULL ;
    int size = 0 ;

    assert(argc==2);

    size = atoi(argv[1]);
    assert(size>0);
    pa = (int*)malloc(size * sizeof(int));
    assert(pa);
    memset(pa,0,size * sizeof(int));

    input(pa,size);

    if(size<100)
        output(pa,size,"Before sort:");
    
    sort(pa,size);
    output(pa,size,"After sort:");

    free(pa);
    pa=NULL;
    return(EXIT_SUCCESS);
}

void sort(int *pa , int n)
{
    quick_sort(pa,0,n-1);
}

void quick_sort(int *pa, int start , int end)
{
    //loc is location
    int loc;
    if(start < end)
    {
        loc = partition(pa,start,end);
        quick_sort(pa,start,loc-1);
        quick_sort(pa,loc+1,end);

    }
}

int partition(int *pa , int start , int end)
{
    int i,j,tmp,pivot;

    pivot = pa[end];
    i = start-1;

    for(j = start ; j<end ;++j)
    {
        if(pa[j]<=pivot)
        {
            printf("pivot = %d , i = %d , j= %d\n",pivot,i,j);

            i=i+1;
            tmp = pa[i] ;
            pa[i] = pa[j] ;
            pa[j] = tmp ;

            printf("Swapped elements : [%d]  [%d]\n",pa[i],pa[j]);
        }
    }
    tmp = pa[i+1];
    pa[i+1] = pa[end] ;
    pa[end] = tmp ;

    return (i+1) ;
}
void input(int* pa, int size)
{
    int i; 
    srand(time(0)); 
    for(i = 0; i < size; ++i)
        pa[i] = rand() % CAP; 
}

void output(int* pa, int n, const char* msg)
{
    int i; 
    if(msg)
        puts(msg); 
    for(i = 0; i < n; ++i)
        printf("a[%d]:%d\n", i, pa[i]); 
}

