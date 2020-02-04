//
//  Option.hpp
//  TD6
//
//  Created by Nicolas Lissak on 29/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
enum OptionType {Call, Put};
class Option 
{
//private:
protected:
    double S0;
    double R;
    double v;
    double T;
    int N; //steps to expiry public:
    double K;  // Strike price
    OptionType type;
    
public:
    //Option();
    Option(double _K,double _N, OptionType _type);
    Option(int N,double S,double K,double R,double v,double T,OptionType type);
    virtual double Payoff(double z) const=0;
    //getter,setter
    double GetK() const{return K;};
    void SetK(double K){this->K=K;};
    void SetN(int N);//{this->N=N;};
    int GetN() const{return N;};
    double getR()const{return R;}
    void SetR(double R);
    double getS0()const{return S0;}
    void SetS0(double S0);
    double getv()const{return v;}
    void Setsigma(double sigma);
   
    //virtual ~Option(){};
};
 
#endif /* Option_hpp */

