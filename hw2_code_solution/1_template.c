#include <stdio.h>
#define ll long long
int ColorMap(float minv, float maxv, int mvcolor, float v)
{
    // YOUR CODE STARTS HERE
//    printf("%d\n",((mvcolor&((1<<24)-(1<<16)))>>16));
//    printf("%d %d\n",((mvcolor&((1<<12)-(1<<8)))>>8),((1<<12)-(1<<8)));
    return (((int)((v-minv)*((mvcolor&((1<<24)-(1<<16)))>>16)/(maxv-minv)))<<16)
    +(((int)((v-minv)*((mvcolor&((1<<16)-(1<<8)))>>8)/(maxv-minv)))<<8)
    +(int)((v-minv)*(mvcolor&((1<<8)-1))/(maxv-minv));
    // YOUR CODE ENDS HERE
}

int main()
{
    float minVal, maxVal, val;
    int maxValColor;
    scanf("%f %f %x %f", &minVal, &maxVal, &maxValColor, &val);
    int color = ColorMap(minVal, maxVal, maxValColor, val);
    printf ("0x%x\n", color);
    return 0;
}
