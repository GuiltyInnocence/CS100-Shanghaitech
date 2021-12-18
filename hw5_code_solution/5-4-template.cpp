#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctype.h>
using namespace std;
int read(){
    char c=getchar();while(!isdigit(c))c=getchar();
    int ret=0;while(isdigit(c)){ret=ret*10+(c-'0');c=getchar();}
    return ret;
}
class Alarm//abstract base class
{
public:
    // constructors and destructor
    Alarm(const int a,const int b,string ss):h(a),m(b),name(ss){};
    ~Alarm()=default;
    // other functions
    virtual void Trigger() = 0;
    virtual void reset()=0;
    int h,m;
protected:
    // member variables are protected to let child classes access them.

    std::string name;
};

class RepeatableAlarm:public Alarm{
public:
    RepeatableAlarm(const int hh,const int mm,string ss):Alarm(hh,mm,ss){};
    void Trigger(){
        cout<<"Alarm "<<name<<" has triggered at "<<setw(2)<<setfill('0')<<h<<':'<<setw(2)<<setfill('0')<<m<<".\n";
    }
    void reset(){};
};

class SnoozeableAlarm:public Alarm{
public:
    SnoozeableAlarm(const int hh,const int mm,string ss):Alarm(hh,mm,ss){};
    void Trigger(){
        cout<<"Alarm "<<name<<" has triggered at "<<setw(2)<<setfill('0')<<h<<':'<<setw(2)<<setfill('0')<<m<<". Snooze? (Y/N)\n";
        char cmd=getchar();
        while(cmd!='Y' && cmd!='N')cmd=getchar();
        if(cmd=='Y'){
            h=(h+(m+10)/60)%24;
            m=(m+10)%60;
        }
    }
    void reset(){
        h=2333;
    }
};

class AlarmClock
{
public:
    // constructors and destructor
    AlarmClock():nowh(0),nowm(0){};
    // other functions
    void AddAlarm(Alarm* alarm);
    void TimeElapse();
    
private:
    // a container of Alarm*
    std::vector<Alarm*> v;
    // other member variables
    int nowh,nowm;
};

/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm)
{
    v.push_back(alarm);
}

void AlarmClock::TimeElapse()
{
    for(auto &i : v){
        if(nowh==i->h && nowm==i->m)
            i->Trigger();
    }
    nowh=nowh+(nowm+1)/60;
    if(nowh>=24){
        for(auto &i:v){
            i->reset();
        }
        nowh=nowh%24;
    }
    nowm=(nowm+1)%60;
}

/**************** Input function ******************/
void Input(AlarmClock& clock)
{
    int n,a,b;
    cin>>n;
    string namae;
    for(int i=0;i<n;i++){
        char c=getchar();
        while(c!='R' && c!='S')c=getchar();
        a=read();b=read();
        cin>>namae;
        switch(c){
            case 'R':
                clock.AddAlarm(new RepeatableAlarm(a,b,namae));
                break;
            case 'S':
                clock.AddAlarm(new SnoozeableAlarm(a,b,namae));
                break;
        }
    }
}

int main()
{
    AlarmClock clock;
    for(int days = 0; days < 3; days++)
    {
        cout << "Do you want to add any alarms?" << endl;
        Input(clock);
        for(int minute = 0; minute < 24*60; minute++)
        {
            clock.TimeElapse();
        }
        cout << "A day has elapsed." << endl;
    }
}
