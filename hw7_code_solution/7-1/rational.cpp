#include "rational.hpp"

int gcd(int a,int b){
    if(b<0)b=-b;
    while(b){
        int tmp=a%b;
        a=b;
        b=tmp;
    }
    return a;
}

Rational::Rational():m_numerator(0),m_denominator(1u){}
Rational::Rational(int value):m_numerator(value),m_denominator(1u){}
Rational::Rational(int p, unsigned int q){
    if(q){
        int n=gcd(std::max(p,(int)q),std::min(p,(int)q));
        m_numerator=p/n;
        m_denominator=q/n;
    }
    else{
        puts("ERROR: initializing with a denominator of 0!");
        m_denominator=1u;
        m_numerator=0;
    }
}

// Assignment operator
Rational& Rational::operator=(const Rational& that){
    m_denominator=that.m_denominator;
    m_numerator=that.m_numerator;
    return *this;
}

// Arithmetic operators
Rational  Rational::operator+(Rational that) const {
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_denominator+m_denominator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    return Rational(newp/n,newq/n);
}
Rational& Rational::operator+=(Rational that) {
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_denominator+m_denominator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    m_numerator=newp/n;
    m_denominator=newq/n;
    return *this;
}
Rational  Rational::operator-(Rational that) const {
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_denominator-m_denominator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    return Rational(newp/n,newq/n);
}
Rational& Rational::operator-=(Rational that){
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_denominator-m_denominator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    m_numerator=newp/n;
    m_denominator=newq/n;
    return *this;
}
Rational  Rational::operator*(Rational that) const{
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    return Rational(newp/n,newq/n);
}
Rational& Rational::operator*=(Rational that){
    unsigned int newq=that.m_denominator*m_denominator;
    int newp=m_numerator*that.m_numerator;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    m_numerator=newp/n;
    m_denominator=newq/n;
    return *this;
}
Rational  Rational::operator/(Rational that) const{
    if(!that.m_numerator){
        puts("ERROR: dividing by 0!");
        return Rational(19260817,1u);
    }
    int flag=1;
    if(that.m_numerator<0){
        that.m_numerator=-that.m_numerator;
        flag=-1;
    }
    unsigned int newq=that.m_numerator*m_denominator;
    int newp=m_numerator*that.m_denominator*flag;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    return Rational(newp/n,newq/n);
}
Rational& Rational::operator/=(Rational that){
    if(!that.m_numerator){
        puts("ERROR: dividing by 0!");
        return *this;
    }
    int flag=1;
    if(that.m_numerator<0){
        that.m_numerator=-that.m_numerator;
        flag=-1;
    }
    unsigned int newq=that.m_numerator*m_denominator;
    int newp=m_numerator*that.m_denominator*flag;
    int n=gcd(std::max(newp,(int)newq),std::min(newp,(int)newq));
    m_numerator=newp/n;
    m_denominator=newq/n;
    return *this;
}

// Comparison operators: equal and less than
bool Rational::operator==(Rational that) const{
    if(m_numerator==0 && that.m_numerator==0)return true;
    if(m_numerator==that.m_numerator && m_denominator==that.m_denominator)return true;
    return false;
}
bool Rational::operator<(Rational that) const{
    if((double)m_numerator/m_denominator < (double)that.m_numerator/that.m_denominator)return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Rational& number){
    if(number.m_denominator==1)os<<number.m_numerator;
    else os<<number.m_numerator<<'/'<<number.m_denominator;
    return os;
}