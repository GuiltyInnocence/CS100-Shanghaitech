#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
int main(){
    std::string s;
    std::cin>>s;
    int h=0,l=s.size();
    for(int i=0;i<l;h=++i){
        while(i<l && s[i]!=',')i++;
        std::string ss=s.substr(h,i-h);
        int flag=1;
        for(int j=0;j<=ss.size()/2+1;j++){
            if(ss[j]!=ss[ss.size()-j-1])flag=0;
        }
        if(flag)std::cout<<ss<<std::endl;
    }
    return 0;
}