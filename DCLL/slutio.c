#include <stdio.h>

void avg_even(int* arr, int ind);
void avg_odd(int* arr, int ind);
void avg(int* arr, int ind);

int main(void)
{
    int num ;
    int arr[50];
    int ind=0 , rem ;

    while(num!=0)
    {
        rem = num % 10 ;
        arr[ind] = rem ;
        ++ind ;
        num = num / 10 ;
    }
    int ch;
    printf("choose 1: for even avg | choose 2: for odd avg | choose 3: for avg\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
                avg_even(arr,ind);
                break;
        case 2:
                avg_odd(arr,ind);
                break;
        case 3:
                avg(arr,ind);
                break;
    }
    return 0;
}

void avg_even(int* arr, int ind)
{
    int sum = 0 , count = 0 ;

    for(int i=0 ; i<ind ; ++i)
    {
        if(arr[i]%2==0)
        {
            sum+=arr[i];
            ++count;
        }
    }
    float avg = sum/count ;
    printf("avg_even : %f\n",avg);
}
void avg_odd(int* arr, int ind)
{
    int sum = 0 , count = 0 ;

    for(int i=0 ; i<ind ; ++i)
    {
        if(arr[i]%2==1)
        {
            sum+=arr[i];
            ++count;
        }
    }
    float avg = sum/count;
    printf("avg_odd : %lf\n",avg);
}
void avg(int* arr, int ind)
{
   int sum = 0 ;

    for(int i=0 ; i<ind ; ++i)
    {
            sum+=arr[i];

    }
    float avg = sum/ind ;
    printf("avg : %lf\n",avg); 
}

