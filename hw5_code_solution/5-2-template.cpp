#include <iostream>
#include <string>
#include <vector>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace  std;
class ReportParser
{
public:
    ReportParser(int numStudents, int numProblems):_n(numStudents),_m(numProblems){};
    ~ReportParser()=default;
    void readReport();
    void writeStructuredReport();
private:
    // Your additional declarations here
    int _n,_m;
    vector<vector<string> >v;
};
void ReportParser::readReport() {
    for(int i=0;i<_n;i++){
        vector<string> tmp;
        string s;
        for(int j=0;j<_m;j++){
            cin>>s;
            tmp.push_back(s);
        }
        v.push_back(tmp);
    }
}
void ReportParser::writeStructuredReport() {
    uint64_t st[_m];
    memset(st,0x00,sizeof(st));
    for(int i=0;i<_n;i++){
        for(int j=0;j<_m;j++) {
//            puts("666");
            st[j]=max(st[j],v[i][j].size());
        }
    }
    int len=1;
    for(int i=0;i<_m;i++)len+=st[i]+3;
    putchar('/');
    for(int i=1;i<=len-2;i++)putchar('-');
    putchar('\\');
    putchar('\n');
    for(int i=0;i<_n;i++){
        for(int j=0;j<_m;j++){
            printf("| ");
            cout<<v[i][j];
            for(int k=0;k<st[j]-v[i][j].size();k++)putchar(' ');
            putchar(' ');
        }
        printf("|\n");
        (i==_n-1)?putchar('\\'):putchar('|');
        for(int k=0;k<_m;k++){
            for(int j=0;j<st[k]+2;j++)putchar('-');
            (k==_m-1)?:(i==_n-1)?putchar('-'):putchar('|');
        }
        (i==_n-1)?putchar('/'):putchar('|');
        putchar('\n');
    }
}
// DO NOT modify the main function
int main()
{
    int n, m;
    std::cin >> n >> m;
    getchar();
    ReportParser a(n, m);
    a.readReport();
    a.writeStructuredReport();
    return 0;
}
