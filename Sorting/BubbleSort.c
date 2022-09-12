
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define CAP  10000000

void input(int *pa,int n);
void output(int *pa , int n , const char* msg);
void sort(int *pa , int n);
void bubble_sort(int *pa , int n);

int main(int argc,char* argv[])
{
    int *pa = NULL ;
    int size = 0 ;

    assert(argc==2);

    size = atoi(argv[1]);
    assert(size>0);

    pa = (int*)malloc(size * sizeof(int));
    assert(pa);
    memset(pa,0,size*sizeof(int));

    input(pa,size);

    if(size<100)
        output(pa,size,"Before sort:");

    sort(pa,size);

    output(pa,size,"After Sort:");

    free(pa);
    pa = NULL ;

    return(EXIT_SUCCESS);

}

void sort(int *pa,int n)
{
    bubble_sort(pa,n);
}

void bubble_sort(int *pa,int n)
{
    int i;
    int j=0;

    for(i=0 ; i<n ; ++i)
    {
        for(j=i+1 ; j< n ; ++j)
        {
            if(pa[i]>pa[j])
            {
                pa[i]= pa[i] + pa[j] - (pa[j]=pa[i]);
                /*int temp;
                temp=pa[i];
                pa[i]=pa[j];
                pa[j]=temp;*/
            }
        }
    }
}

void input(int *pa , int n)
{
    int i;

    srand(time(0));
    for(i=0 ; i<n ; ++i)
    {
        pa[i] = rand() % CAP ;
    }
}

void output(int *pa , int n ,const char* msg)
{
    int i;

    if(msg)
        puts(msg);

    for(i=0 ; i<n ; ++i)
    {
        printf("a[%d]=%d\n",i,pa[i]);
    }

}