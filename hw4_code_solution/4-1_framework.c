#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************Functions******************************/
/* You need to check whether the given `mahjongHand` is win.
 * If wins, return 1, otherwise, return 0
 * The length of `mahjongHand` is guaranteed to be 14.
 * All tiles are guaranteed to be legal.
 */
int checkp(int mianzi,int quetou,int sp[],int cp){
    if(quetou>1)return 0;
    if(cp==0) {
        if(mianzi==4 && quetou==1)return 1;
        return 0;
    }
    for(int i=1;i<=9;i++) {
        if(sp[i]>=3){
            sp[i]-=3;
            if(checkp(mianzi+1,quetou,sp,cp-3))return 1;
            sp[i]+=3;
        }
        if(sp[i]>=2){
            sp[i]-=2;
            if(checkp(mianzi,quetou+1,sp,cp-2))return 1;
            sp[i]+=2;
        }
        if(i<=7 && sp[i] && sp[i+1] && sp[i+2]) {
            sp[i]--;
            sp[i + 1]--;
            sp[i + 2]--;
            if (checkp(mianzi+1,quetou,sp,cp-3))return 1;
            sp[i]++;
            sp[i + 1]++;
            sp[i + 2]++;
        }
    }
    return 0;
}
int checks(int mianzi,int quetou,int ss[],int sp[],int cp,int cs){
    if(quetou>1)return 0;
    if(cs==0) {
        if(mianzi==4 && quetou==1)return 1;
        if(checkp(mianzi,quetou,sp,cp))return 1;
        return 0;
    }
    for(int i=1;i<=9;i++) {
        if(ss[i]>=3){
            ss[i]-=3;
            if(checks(mianzi+1,quetou,ss,sp,cp,cs-3))return 1;
            ss[i]+=3;
        }
        if(ss[i]>=2){
            ss[i]-=2;
            if(checks(mianzi,quetou+1,ss,sp,cp,cs-2))return 1;
            ss[i]+=2;
        }
        if(i<=7 && ss[i] && ss[i+1] && ss[i+2]) {
            ss[i]--;
            ss[i + 1]--;
            ss[i + 2]--;
            if (checks(mianzi+1,quetou,ss,sp,cp,cs-3))return 1;
            ss[i]++;
            ss[i + 1]++;
            ss[i + 2]++;
        }
    }
    return 0;
}
int checkm(int mianzi,int quetou,int ss[],int sp[],int sm[],int cs,int cp,int cm){
    if(quetou>1)return 0;
    if(cm==0) {
        if(mianzi==4 && quetou==1)return 1;
        if(checks(mianzi,quetou,ss,sp,cp,cs))return 1;
        return 0;
    }
    for(int i=1;i<=9;i++) {
        if(sm[i]>=3){
            sm[i]-=3;
            if(checkm(mianzi+1,quetou,ss,sp,sm,cs,cp,cm-3))return 1;
            sm[i]+=3;
        }
        if(sm[i]>=2){
            sm[i]-=2;
            if(checkm(mianzi,quetou+1,ss,sp,sm,cs,cp,cm-2))return 1;
            sm[i]+=2;
        }
        if(i<=7 && sm[i] && sm[i+1] && sm[i+2]) {
            sm[i]--;
            sm[i + 1]--;
            sm[i + 2]--;
            if (checkm(mianzi + 1, quetou, ss, sp, sm, cs, cp, cm-3))return 1;
            sm[i]++;
            sm[i + 1]++;
            sm[i + 2]++;
        }
    }
    return 0;
}

int checkz(int mianzi,int quetou,int ss[],int sp[],int sm[],int sz[],int cs,int cp,int cm,int cz){
//    printf("%d %d %d %d\n",mianzi,quetou,cz,sz[1]);
    if(quetou>1)return 0;
    if(cz==0) {
        if(mianzi==4 && quetou==1)return 1;
        if(checkm(mianzi, quetou, ss, sp, sm, cs, cp, cm))return 1;
        return 0;
    }
    for(int i=1;i<=7;i++) {
        if(sz[i]>=3){
            sz[i]-=3;
            if(checkz(mianzi+1,quetou,ss,sp,sm,sz,cs,cp,cm,cz-3))return 1;
            sz[i]+=3;
        }
        if(!quetou && sz[i]>=2){
            sz[i]-=2;
            if(checkz(mianzi,quetou+1,ss,sp,sm,sz,cs,cp,cm,cz-2))return 1;
            sz[i]+=2;
        }
    }
    return 0;
}
int CheckWin(char* mahjongHand[]){
    // YOUR CODE HERE
    int ps[10],ss[10],ms[10],zs[10];
    int cp=0,  cs=0,  cm=0,  cz=0;
    memset(ps,0x00,sizeof ps);
    memset(ss,0x00,sizeof ss);
    memset(ms,0x00,sizeof ms);
    memset(zs,0x00,sizeof zs);
    for(int i=0;i<14;i++)
        switch (mahjongHand[i][1]) {
            case 'p':
                ps[mahjongHand[i][0]-'0']++;
                cp++;
                break;
            case 's':
                ss[mahjongHand[i][0]-'0']++;
                cs++;
                break;
            case 'm':
                ms[mahjongHand[i][0]-'0']++;
                cm++;
                break;
            case 'z':
                zs[mahjongHand[i][0]-'0']++;
                cz++;
                break;
            default:
                puts("fatal error!");
                exit(1);
        }
    return checkz(0,0,ss,ps,ms,zs,cs,cp,cm,cz);
}

/* You need to count the number of different tiles that
 * lead him to win. 
 * The length of `currentTiles` is guaranteed to be 13,
 * all tiles are guaranteed to be legal. You should ignore 
 * the tiles that are used up (already 4 in his hand). 
 * Return the number of different tiles that leads him to win.
 */
int isvalid(char* mahjongHand[]){
    int ps[10],ss[10],ms[10],zs[10];
    memset(ps,0x00,sizeof ps);
    memset(ss,0x00,sizeof ss);
    memset(ms,0x00,sizeof ms);
    memset(zs,0x00,sizeof zs);
    for(int i=0;i<14;i++)
        switch (mahjongHand[i][1]) {
            case 'p':
                ps[mahjongHand[i][0]-'0']++;
                if(ps[mahjongHand[i][0]-'0']>4)return 0;
                break;
            case 's':
                ss[mahjongHand[i][0]-'0']++;
                if(ss[mahjongHand[i][0]-'0']>4)return 0;
                break;
            case 'm':
                ms[mahjongHand[i][0]-'0']++;
                if(ms[mahjongHand[i][0]-'0']>4)return 0;
                break;
            case 'z':
                zs[mahjongHand[i][0]-'0']++;
                if(zs[mahjongHand[i][0]-'0']>4)return 0;
                break;
            default:
                puts("fatal error!");
                exit(1);
        }
    return 1;
}
int CountWaitingTiles(char* currentTiles[]){
    // YOUR CODE HERE
    int cnt=0;
    char* try[14];
    for(int i=0;i<13;i++)try[i]=currentTiles[i];
    char* tp[10]={"\0","1p","2p","3p","4p","5p","6p","7p","8p","9p"};
    char* ts[10]={"\0","1s","2s","3s","4s","5s","6s","7s","8s","9s"};
    char* tm[10]={"\0","1m","2m","3m","4m","5m","6m","7m","8m","9m"};
    char* tz[10]={"\0","1z","2z","3z","4z","5z","6z","7z"};
    for(int i=1;i<=9;i++){
        try[13]=tp[i];//This will cause one card of more than 5!!!
        if(isvalid(try)&& CheckWin(try))cnt++;
        try[13]=ts[i];
        if(isvalid(try)&& CheckWin(try))cnt++;
        try[13]=tm[i];
        if(isvalid(try)&& CheckWin(try))cnt++;
    }
    for(int i=1;i<=7;i++){
        try[13]=tz[i];
        if(isvalid(try)&& CheckWin(try))cnt++;
    }
    return cnt;
}

/*****************************Your Main Function*************************************/
// DO NOT submit main function to OJ, or compile error may happen!
int main(){
    /*************** Part1 ***************/
//    char* hand[14] = {"1s", "2z", "3m", "5p", "6s", "5p", "3z", "5z", \
//                      "4z", "7m", "9s", "9p", "3z", "4s"};
//    char* hand[14] = {"1m", "1m", "1m", "2m", "2m", "2m", "3z", "3z", \
//                      "4z", "3z", "5z", "4z", "5z", "4z"};
     char* hand[14] = {"1s", "1s", "1s", "2p", "2p", "2p", "5p", "6p", \
                       "7p", "3z", "3z", "9s", "3z", "9s"};
    int result = CheckWin(hand);
    printf ("Gezi Wang %s the game.\n", result == 1 ? "wins" : "does not win");

    /*************** Part2 ***************/
     char* hand2[13] = {"1s", "1s", "1s", "2s", "3s", "4s", "5s", "6s", \
                          "7s", "8s", "9s", "9s", "9s"};
     printf ("The number of different tiles he is waiting for is: %d\n", CountWaitingTiles(hand2));
    
    return 0;
}