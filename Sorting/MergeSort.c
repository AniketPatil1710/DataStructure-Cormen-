//MergeSort By Aniket Patil

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define TRUE 1
#define CAP  10000000

void input(int *pa,int n);
void output(int *pa , int n , const char* msg);
void merge(int *pa,int start , int mid , int end);
void merge_sort(int *pa , int start , int end);
void sort(int *pa , int n);

int main(int argc,char* argv[])
{
    int *pa = NULL;
    int size = 0;

    assert(argc == 2);
    
    size = atoi(argv[1]);
    assert(size > 0 );

    pa = (int*)malloc(size * sizeof(int));
    assert(pa);
    memset(pa,0,size *sizeof(int));

    input(pa,size);

    if(size<100)
        output(pa,size,"Befor Sort:");

    sort(pa,size);
    
    output(pa,size,"After Sort:");

    free(pa);
    pa=NULL;
    return(EXIT_SUCCESS);
}

void sort(int *pa,int n)
{
    merge_sort(pa,0,n-1);
}

void merge_sort(int *pa,int start,int end)
{
    int mid;

    if(start < end)
    {
        mid = (start+end)/2 ;
        merge_sort(pa,start,mid);
        merge_sort(pa,mid+1,end);
        merge(pa,start,mid,end);
    }
}

void merge(int *pa,int start,int mid,int end)
{
    int *pa1=NULL;
    int *pa2=NULL;

    int n1 ;
    int n2 ;
    int i;
    int j;
    int k;

    n1 = mid - start + 1;
    n2 = end - mid ;

    pa1 = (int*)malloc(n1 * sizeof(int));
    if(pa1==NULL)
    {
        fprintf(stderr,"Out Of Memory");
        exit(EXIT_FAILURE);
    }
    memset(pa1,0,n1 * sizeof(int));

    pa2 = (int*)malloc(n2 * sizeof(int));
    if(pa2==NULL)
    {
        fprintf(stderr,"Out Of Memory");
        exit(EXIT_FAILURE);
    }
    memset(pa2,0,n2*(sizeof(int)));

    for(cnt=0 ; cnt < n1 ; ++cnt)
    {
        pa1[cnt] = pa[start + cnt];
    }

    for(cnt=0 ; cnt < n2 ; ++cnt)
    {
        pa2[cnt] = pa[mid +1 +cnt];
    }

    i=0 ;
    j=0 ;
    k=0 ;

    while(TRUE)
    {
        if(pa1[i]<=pa2[j])
        {
            pa[start+k] = pa1[i];
            ++i;
            ++k;

            if(i==n1)
            {
                while(j<n2){

                    pa[start+k]=pa2[j];
                    ++j;
                    ++k;
                }
                break;
            }
        }
        else
        {
            pa[start+k]=pa2[j];
            ++j;
            ++k;

            if(j==n2)
            {
                while(i<n1)
                {
                    pa[start+k] = pa1[i];
                    ++i;
                    ++k;
                }
                break;
            }
        }
    }

    free(pa1);
    pa1=NULL;

    free(pa2);
    pa2=NULL;
}

void input(int *pa , int n)
{
    int i;
    
    srand(time(0));

    for(i=0 ; i< n ; ++i)
    {
        pa[i] = rand() % CAP ;
    }
}

void output(int* pa, int n, const char* msg)
{
    int i; 
    if(msg)
        puts(msg); 
    for(i = 0; i < n; ++i)
        printf("a[%d]:%d\n", i, pa[i]); 
}