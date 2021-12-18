#ifndef CS100_hw7_matrix_hpp
#define CS100_hw7_matrix_hpp
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Matrix{
public:
    Matrix()=default;
    Matrix(unsigned int rows, unsigned int cols, const T& value = T()){
			for(int i=0;i<rows;i++)
					v.emplace_back(std::vector<T>(cols,value));
		}
    T& operator()(unsigned int r, unsigned int c){
			return v[r][c];
		}
    
    void Print(){
			for(auto &i : v){
				for(auto &j: i)
					std::cout<<j<<' ';
				std::cout<<std::endl;
			}
		}

    void GaussJordan(){
			int h=0,k=0;
			int m=v.size(),n=v.empty()?0:v[0].size();
			while(h<m && k<n){
				T mx(-2147483647),mn(2147483647);
				int imax=h,imin=h;
				for(int i=h;i<m;i++){
					if(mx<v[i][k])mx=v[i][k],imax=i;
					if(v[i][k]<mn)mn=v[i][k],imin=i;
				}
				if(v[imax][k]==T(0))imax=imin;
				if(v[imax][k]==T(0))k++;
				else{
					std::vector<T> tmp=v[h];
					v[h]=v[imax];
					v[imax]=tmp;
					for(int i=h+1;i<m;i++){
						T f=v[i][k]/v[h][k];
						v[i][k]=0;
						for(int j=k+1;j<n;j++)
							v[i][j]-=v[h][j]*f;
					}
					h++;
					k++;
				}
			}
		}

private:
    // Your implementation here.
		std::vector<std::vector<T>>v;
};
#endif
