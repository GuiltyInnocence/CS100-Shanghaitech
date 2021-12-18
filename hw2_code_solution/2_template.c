#include <stdio.h>
#include <math.h>
#define d() putchar('*')
#define nl() putchar('\n')
#define sp() putchar(' ')
void DrawSquare(int size)
{
    // YOUR CODE STARTS HERE
    for(int i=1;i<=size;i++)d();
    nl();
    for(int i=2;i<size;i++){
        d();
        for(int j=2;j<size;j++)sp();
        d();
        nl();
    }
    for(int i=1;i<=size;i++)d();
    nl();
    // YOUR CODE ENDS HERE
}

void DrawDiamond(int n)
{    
    // YOUR CODE STARTS HERE
    for(int j=1;j<n;j++)sp();
    d();
    nl();
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n-i;j++)sp();
        d();
        for(int j=1;j<i*2-2;j++)sp();
        d();
        nl();
    }
    for(int i=n-1;i>=2;i--){
        for(int j=1;j<=n-i;j++)sp();
        d();
        for(int j=1;j<i*2-2;j++)sp();
        d();
        nl();
    }
    for(int j=1;j<n;j++)sp();
    d();
    nl();
    // YOUR CODE ENDS HERE
}


void DrawHexagon(int n)
{
    // YOUR CODE STARTS HERE
    for(int j=1;j<n;j++)sp();
    for(int j=1;j<=n;j++)d();
    nl();
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n-i;j++)sp();
        d();
        for(int j=1;j<i*2+n-3;j++)sp();
        d();
        nl();
    }
    for(int i=n-1;i>=2;i--){
        for(int j=1;j<=n-i;j++)sp();
        d();
        for(int j=1;j<i*2+n-3;j++)sp();
        d();
        nl();
    }
    for(int j=1;j<n;j++)sp();
    for(int j=1;j<=n;j++)d();
    nl();
    // YOUR CODE ENDS HERE
}


int main()
{
    int shape, size;
    scanf("%d %d", &shape, &size);
    
    // 1 for square, 2 for diamond, 3 for hexagon.
    switch(shape){
    case 1:
        DrawSquare(size);
        break;
    case 2:
        DrawDiamond(size);
        break;
    case 3:
        DrawHexagon(size);
        break;
    default:
        return -1;
    }
    return 0;
}
