#include <stdio.h>
#include <stdlib.h>
#define NA 2333
int read(){
    char c=getchar();while(!isdigit(c))c=getchar();
    int ret=0;while(isdigit(c)){ret=ret*10+(c-'0');c=getchar();}
    return ret;
}
void FindSecondMaxAndMin(int* secondMax, int* secondMin)
{
    // YOUR CODE STARTS HERE
    int n,mx=-2147483647,smx=-2147483646,mn=2147483647,smn=2147483646;
    n=read();
    for(int i=1;i<=n;i++){
        int tmp=read();
        if(tmp>mx)smx=mx,mx=tmp;
        else if(tmp>smx)smx=tmp;
        if(tmp<mn)smn=mn,mn=tmp;
        else if(tmp<smn)smn=tmp;
    }
    *secondMax=smx;
    *secondMin=smn;
    // YOUR CODE ENDS HERE
}

int main()
{
    int secondMax, secondMin;
    FindSecondMaxAndMin(&secondMax, &secondMin);
    printf ("%d %d\n", secondMax, secondMin);
    return 0;
}