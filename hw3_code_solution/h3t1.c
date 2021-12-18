#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define pas "This car is allowed to drive."
#define ban "This car is not allowed to drive."
#define err "This number is invalid."
char c[7];
int mon,day,week,le,new;
int read(){
    char c=getchar();while(!isdigit(c))c=getchar();
    int ret=0;while(isdigit(c)){ret=ret*10+(c-'0');c=getchar();}
    return ret;
}
int jweek(){//return T/F, 1=weekend
    char c=getchar();while(!isalpha(c))c=getchar();getchar();getchar();
    switch(c) {
        case 'M':
        case 'W':
        case 'T':
        case 'F':
            return 0;
        case 'S':
            return 1;
        default:
            puts("FATAL ERROR in jweek!");
            scanf("%d",0);
    }
}
int valid(){
    if(le==6){
        int strc=0;
        for(int i=0;i<le;i++)
            if(isalpha(c[i]))strc++;
        if(strc!=1)return 0;
        for(int i=0;i<le;i++)
            if(isalpha(c[i]))strc=i;
        if(strc!=0 && strc!=5)return 0;
        if(c[strc]!='D' && c[strc]!='F')return 0;
        new=1;
        return 1;
    }//finished!Dont change
    else if(le==5){
        int strc=0,spos=-1;
        for(int i=0;i<le;i++)
            if(isalpha(c[i]))strc++,spos=i;
        if(strc>2)return 0;
        for(int i=0;i<le;i++)
            if(c[i]=='O' || c[i]=='I')return 0;
        //basic ends here
        //classify goes here
        if(strc==0)return 1;
        if(strc==1&&((isalpha(c[0])&& isdigit(c[4]))||(isdigit(c[0])&&isalpha(c[4])))){//Auto-generated numbers
            return 1;
        }
        if(strc==2 || (strc==1 && (spos==1 || spos==2))){//Self-designed numbers
            for(int i=0;i<=le-3;i++)if(c[i]==c[i+1] && c[i]==c[i+2])return 0;
            if(strc==2){
                if(spos==4 && isalpha(c[0]))return 1;
                if(isalpha(c[spos-1]))return 1;
                return 0;
            }
            else{
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
int judge(){
    for(int i=le-1;i>=0;i--)
        if(isdigit(c[i])){
            if((int)(c[i]-'0')%2==0 && day%2==0)return 1;
            if((int)(c[i]-'0')%2==1 && day%2==1)return 1;
            return 0;
        }
}
int istaxi(){
    int strc=0;
    for(int i=0;i<le;i++)
        if(isalpha(c[i]))strc++;
    if(strc!=1)return 0;
    if(c[0]=='X' || c[0]=='T')return 1;
    return 0;
}
int main(){
    for(int ii=1;ii<=3;ii++){
        memset(c,0x00,sizeof(c));
        new=0;
        scanf("%s",c);
        mon=read();day=read();
        week=jweek();
        le=strlen(c);
        if(valid()){
            if(week) {
                puts(pas);
                continue;
            }
            else if(istaxi()){
                puts(pas);
                continue;
            }
            else if(new){
                puts(pas);
                continue;
            }
            else if(judge()){
                puts(pas);
                continue;
            }
            else puts(ban);
        }
        else puts(err);
    }
    return 0;
}