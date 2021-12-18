#ifndef POLY_HPP_
#define POLY_HPP_

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cmath>

template<typename T>
class Poly {
public:

  /* Default constructor */
  Poly()=default;

  /* Constructor for a poly that's a constant number */
  Poly( T constant ){
      _coeffs.template emplace_back(constant);
  };

  /* Given a vector of coefficients */
  Poly( const std::vector<T> & coeffs ):_coeffs(coeffs){};

  /* Given an rvalue reference of a vector of coefficients */
  Poly( std::vector<T> && coeffs ):_coeffs(coeffs){};

  /* Given an array of coefficients with size of the array*/
  Poly( T * coeffs, size_t numberCoeffs ){
      for(int i=0;i<numberCoeffs;++i)
          _coeffs.template emplace_back(coeffs[i]);
  };

  /* Given an initializer_list */
  Poly( std::initializer_list<T> coeffs ):_coeffs(coeffs){};

  virtual ~Poly()=default;

  /* Copying constructor */
  Poly( const Poly<T> & poly ){
      _coeffs=poly._coeffs;
  };

  /* Copying constructor with rvalue reference */
  Poly( Poly<T> && poly ):_coeffs(poly._coeffs){};

  /* Assignment operator */
  Poly<T>& operator=( const Poly<T> & poly ){
      _coeffs=poly._coeffs;
      return *this;
  };
  
  /* Assignment operator with rvalue reference */
  Poly<T>& operator=( Poly<T> && poly ){
      _coeffs=poly._coeffs;
      return *this;
  };

  /*
   * Below are operations of polynomials.
   * They are quite self-explanatory.
   */

  Poly<T> operator+( const Poly<T> & rhs ) const{
      int nu=std::min(_coeffs.size(),rhs._coeffs.size());
      int nd=std::max(_coeffs.size(),rhs._coeffs.size());
      std::vector<T> tmp;
      for(int i=0;i<nu;i++)tmp.template emplace_back(_coeffs[i]+rhs._coeffs[i]);
      for(int i=nu;i<nd;i++)tmp.template emplace_back(_coeffs.size()>rhs._coeffs.size()?_coeffs[i]:rhs._coeffs[i]);
      return Poly<T>(std::move(tmp));
  };
  Poly<T> operator-( const Poly<T> & rhs ) const{
      int nu=std::min(_coeffs.size(),rhs._coeffs.size());
      int nd=std::max(_coeffs.size(),rhs._coeffs.size());
      std::vector<T> tmp;
      for(int i=0;i<nu;i++)tmp.template emplace_back(_coeffs[i]-rhs._coeffs[i]);
      for(int i=nu;i<nd;i++)tmp.template emplace_back(_coeffs.size()>rhs._coeffs.size()?_coeffs[i]:-rhs._coeffs[i]);
      return Poly<T>(std::move(tmp));
  };
  Poly<T> operator*( const Poly<T> & rhs ) const{
      if(_coeffs.empty() || rhs._coeffs.empty())return Poly<T>();
      int nu=_coeffs.size()+rhs._coeffs.size()-1;
      std::vector<T> tmp(nu,0);//todo: default value 0 not suitable for T
      for(int i=0;i<_coeffs.size();++i)
          for(int j=0;j<rhs._coeffs.size();j++)
              tmp[i+j]+=_coeffs[i]*rhs._coeffs[j];
      return Poly<T>(std::move(tmp));
  };

  Poly<T> & operator+=( const Poly<T> & rhs ){
      int nd=std::max(_coeffs.size(),rhs._coeffs.size());
      for(int i=0;i<nd;i++)
          i<_coeffs.size()?_coeffs[i]+=rhs._coeffs[i]:_coeffs.template emplace_back(rhs._coeffs[i]);
      return *this;
  };
  Poly<T> & operator-=( const Poly<T> & rhs ){
      int nd=std::max(_coeffs.size(),rhs._coeffs.size());
      for(int i=0;i<nd;i++)
          i<_coeffs.size()?_coeffs[i]-=rhs._coeffs[i]:_coeffs.template emplace_back(-rhs._coeffs[i]);
      return *this;
  };
  Poly<T> & operator*=( const Poly<T> & rhs ){
      if(rhs._coeffs.empty()){
          _coeffs=std::vector<T>({0});
          return *this;
      }
      int nu=_coeffs.size()+rhs._coeffs.size()-1;
      std::vector<T> tmp(nu,0);//todo: default value 0 not suitable for T
      for(int i=0;i<_coeffs.size();++i)
          for(int j=0;j<rhs._coeffs.size();j++)
              tmp[i+j]+=_coeffs[i]*rhs._coeffs[j];
      _coeffs=tmp;
      return *this;
  };

  /* 
   * This function evaluates the polynomial at "param",
   * and returns the value of evaluation.
   * For example, evaluating x+3 at param=7 gives 10. 
   */
  T eval( T param ) const{
      T res=0;
      for(int i=0;i<_coeffs.size();++i)
          res+=_coeffs[i]*pow(param,i);
      return res;
  };

  /* 
   * This function takes the derivative of the polynomial,
   * and returns a new polynomial of its derivative.
   * For example, calling this function for x^2
   * will return a polynomial 2x.
   */
  Poly<T> der() const{
      if(_coeffs.size()<2)return Poly<T>();
      std::vector<T> tmp;
      for(int i=0;i<_coeffs.size()-1;++i)
          tmp.template emplace_back(_coeffs[i+1] *(i+1));
      return Poly<T>(std::move(tmp));
  };

  /*
  * This function returns a pair of:
  * 1. the value (evaluation) of the polynomial at "param".
  * 2. the value of the first-order derivative of the polynomial at "param".
  * For example, calling this operator for x^2-2x at "param"=4
  * will return (8, 6).
  */
  std::pair<T,T> operator()( T param ) const{
      return std::make_pair(eval(param),der().eval(param));
  };

private:
  std::vector<T> _coeffs;
};


#endif