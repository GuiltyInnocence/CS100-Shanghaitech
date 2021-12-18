#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
struct cmd{//            1    2    3    4    5     6     7
    int type,l,r,dest;//add, sub, mul, div, let, print, bge
}c[1000];
int x[6],nc,pc;
char tmp[5];
int read(){
    char c=getchar();while(!isdigit(c))c=getchar();
    int ret=0;while(isdigit(c)){ret=ret*10+(c-'0');c=getchar();}
    return ret;
}
void execute(){
    switch(c[pc].type){
        case 1://add
            x[c[pc].dest]=x[c[pc].l]+x[c[pc].r];
            pc++;
            return;
        case 2:
            x[c[pc].dest]=x[c[pc].l]-x[c[pc].r];
            pc++;
            return;
        case 3:
            x[c[pc].dest]=x[c[pc].l]*x[c[pc].r];
            pc++;
            return;
        case 4:
            x[c[pc].dest]=x[c[pc].l]/x[c[pc].r];
            pc++;
            return;
        case 5://let
            x[c[pc].dest]=c[pc].l;
            pc++;
            return;
        case 6:
            printf("x%d = %d\n",c[pc].dest,x[c[pc].dest]);
            pc++;
            return;
        case 7:
            if(x[c[pc].l]>=x[c[pc].r])pc=c[pc].dest;
            else pc++;
            return;
        default:
            puts("FATAL ERROR in jweek!");
            scanf("%d",0);
    }
}
int main(){
    nc=read();
    for(int i=1;i<=nc;i++){
        scanf("%s",tmp);
        switch(tmp[0]){
            case 'a':
                c[i].type=1;
                c[i].dest=read();
                c[i].l=read();
                c[i].r=read();
                break;
            case 's':
                c[i].type=2;
                c[i].dest=read();
                c[i].l=read();
                c[i].r=read();
                break;
            case 'm':
                c[i].type=3;
                c[i].dest=read();
                c[i].l=read();
                c[i].r=read();
                break;
            case 'd':
                c[i].type=4;
                c[i].dest=read();
                c[i].l=read();
                c[i].r=read();
                break;
            case 'l':
                c[i].type=5;
                c[i].dest=read();
                c[i].l=read();
                break;
            case 'p':
                c[i].type=6;
                c[i].dest=read();
                break;
            case 'b':
                c[i].type=7;
                c[i].l=read();
                c[i].r=read();
                c[i].dest=read();
                break;
            default:
                puts("FATAL ERROR in input!");
                scanf("%d",0);
        }
    }
    for(pc=1;pc<=nc || c[pc].type==7;){
        execute();
    }
}
