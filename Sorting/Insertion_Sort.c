
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_ELEMENTS (10000000)

void input(int *pa,int n);
void output(int *pa,int n,const char* msg);
void sort(int* pa ,int n);
void insert_at_sorting_pos(int *pa,int n);
void insertion_sort(int *pa,int n);

int main(int argc,char* argv[])
{
    int *pa=NULL ;
    int n=0 ;

    if(argc!=2)
    {
        fprintf(stderr,"Usage Error %s no_element\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    n=atoi(argv[1]);

    if(n<=0)
    {
        fprintf(stderr,"Bad size of Array\n");
        exit(EXIT_FAILURE);
    }

    pa = (int*)malloc(n*(sizeof(int)));

    if(pa==NULL)
    {
        fprintf(stderr,"Out of Memory\n");
        exit(EXIT_FAILURE);
    }
    input(pa,n);

    if(n<=100)
    {
        output(pa,n,"Before Sort:\n");
    }
              
    time_t start_time = time(0);

    sort(pa,n);

    output(pa,n,"After Sort:\n");

   // printf("start_time - end_time = %lu\n",end_time-start_time);
    free(pa);
    pa=NULL;

    exit(EXIT_SUCCESS);
}

void input(int *pa,int n)
{
    int i;

    srand(time(0));

    for(i=0;i<n;++i)
    {
        pa[i]=rand() % MAX_ELEMENTS;
    }
}

void output(int *pa , int n , const char *msg)
{
    int i ;

    if(msg)
        puts(msg);

    for(i=0;i<n;++i)
    {
        printf("a[%d]=%d\n",i,pa[i]);
    }
}

void sort(int *pa , int n)
{
    insertion_sort(pa,n);
}

void insert_at_sorting_pos(int *pa , int n )
{
    int key , i ;

    key = pa[n-1];

    i = n-2 ;

    while(i > -1 && pa[i]>key)
    {
        pa[i+1]=pa[i];

        i=i-1 ;
    }

    pa[i+1]=key;
}

void insertion_sort(int *pa, int n)
{
    int i;

    if(n<2)
    {
        return;
    }
    for( i = 2 ; i<=n ; i++)
    {
        insert_at_sorting_pos(pa,i);
    }
}
