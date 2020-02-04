//
//  European_Option.hpp
//  TD_5
//
//  Created by Nicolas Lissak on 28/10/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef European_Option_hpp
#define European_Option_hpp

#include <stdio.h>
#include <cmath>
#include "BinModel.hpp"
#include "Option.hpp"



class European_Option : public Option
{
    /*Steps to expiry*/
private:
    //int N;

public:
    
    European_Option(double K,int N,OptionType type);
    European_Option(int N,double S0,double K,double R,double v,double T,OptionType type);
    
    //mc method
    double MCPricer();
    double Gaussian_Box_Muller();
    
    //virtual double Payoff(double z) const=0;
    double Payoff(double z) const override;
    /*Function PriceByCRR which returns the price at time 0 */
    //European_Option();
   
    //binomial methode
    double PriceByCRR(BinModel&)const;
    double PriceByCRRBS(const double& T,const int& N,const double &R,const double &v)const;
    //black-scholes
    double norm_pdf(const double& x);
    double norm_cdf(const double& x);
    double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T);
    double PriceBS();
    
    //virtual ~European_Option(){};
   
};




#endif /* European_Option_hpp */
