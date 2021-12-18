#include <stdio.h>
#include <math.h>
#define ll unsigned long long
ll n,fra,expo;
const ll nfra=(1<<24)-1;
int main() {
    scanf("%xu", &n);
    fra = n & nfra;
    expo = (n & ((1u << 31) - 1 - nfra)) >> 24;
    double output=(double) (fra + (1ull << 24)) / pow(2, (63 - expo + 24));
    if (n & (1u << 31)) {
        printf("The number converts to %lf\n", -output);
    } else {
    printf("The number converts to %lf\n", output);
    }
    return 0;
}