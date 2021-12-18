#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MSEC 10000000
int n,sh,sm,eh,em;
double mood=100.0;
int sth,stm,edh=8,edm=0;
int read(){
    char c=getchar();while(!isdigit(c))c=getchar();
    int ret=0;while(isdigit(c)){ret=ret*10+(c-'0');c=getchar();}
    return ret;
}
double sleep(int fsh,int fsm,int feh,int fem){
    return (fem-fsm<0?(60-fsm+fem+(feh-fsh-1)*60):fem-fsm+(feh-fsh)*60)*0.5;
}
double lecture(int fsh,int fsm,int feh,int fem) {
    int times=fem-fsm<0?(60-fsm+fem+(feh-fsh-1)*60):fem-fsm+(feh-fsh)*60;
    return times>60?24.0+(times-60)*0.8:times*0.4;
}
int main(){
//    printf("%d",read());
    printf("How many lectures today?\n");
//    printf("%0.1f",lecture(8,0,10,0));
//    scanf("%d",&n);
    n=read();
    for(int i=1;i<=n;i++){
//        scanf("%d %d",&sth,&stm);
        sth=read();stm=read();
        mood+=sleep(edh,edm,sth,stm);
        if(mood>100.0)mood=100.0;
//        scanf("%d %d",&edh,&edm);
        edh=read();edm=read();
//        printf("%d %d %d %d",sth,stm,edh,edm);
        mood-=lecture(sth,stm,edh,edm);
        if(mood<0) {
            printf("Gezi Wang has been sent to hospital.\n");
            exit(0);
        }
    }
    mood+=sleep(edh,edm,22,0);
    if(mood>100.0)mood=100.0;
    printf("His mood level is %0.1f at the end of the day.\n",mood);
    return 0;
}