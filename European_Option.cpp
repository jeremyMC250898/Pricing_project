//
//  European_Option.cpp
//  TD_5
//
//  Created by Nicolas Lissak on 28/10/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include "European_Option.hpp"
#include "BinModel.hpp"
#include "Option.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;


European_Option::European_Option(double K, int N, OptionType type) : Option(K, N, type)
{
    
    
}
European_Option:: European_Option (int N,double S0,double K,double R,double v,double T,OptionType type) : Option(N, S0, K, R, v, T, type)
{
    
}
double European_Option :: Payoff(double z)const
{
    
    switch(type)
    {
        case Call: if(z>GetK()) return z-GetK();
            return 0.0;
            break;
            
        case Put:  if (z<GetK()) return GetK()-z;
            return 0.0;
            break;
    }
    
}

double European_Option:: Gaussian_Box_Muller()
{
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;
    
    // Continue generating two uniform random variables
    // until the square of their "euclidean distance"
    // is less than unity
    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        euclid_sq = x*x + y*y;
    } while (euclid_sq >= 1.0);
    
    return x*sqrt(-2*log(euclid_sq)/euclid_sq);
    
}


double European_Option:: MCPricer()
{
    double S_adjust = S0 * exp(T*(R-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;
    
    for (int i=0; i<N; i++)
    {
        double gauss_bm = Gaussian_Box_Muller();
        S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
        if(type == Call)
        {
            payoff_sum += max(S_cur - K, 0.0);
        }
        else if (type == Put)
        {
            payoff_sum += max(K - S_cur, 0.0);
        }
    }
    
    return (payoff_sum / static_cast<double>(N)) * exp(-R*T);
}


double European_Option:: PriceByCRR(BinModel& Model)const
{
    double q= Model.RiskNeutProb();
    vector<double> Price(GetN()+1);
    /*Fix the terminal condition*/
    for (int i=0;i<=GetN();i++)
    {
        Price[i]=Payoff(Model.S(GetN(),i));
        
        
    }    /*For each period n we compute in all the
          nodes*/
    for (int n=GetN()-1; n>=0; n--) {
        for (int i=0;i<=n; i++)
        {
            Price[i]=(q*Price[i+1]+(1-q)*Price[i])/(1+Model.getR());
            
        }
    }
    return Price[0];
    
}
double European_Option:: PriceByCRRBS(const double& T,const int& N,const double &R,const double &v)const

{
    double h,u,d,r;
    h = T/N;
    u = exp( ((v*v)+R/2) *h+v*sqrt(h))-1;
    d = exp( ((v*v)+R/2) *h-v*sqrt(h))-1;
    r=exp(R*h)-1;
    BinModel Model(100, u, d, r);
    double q= Model.RiskNeutProb();
    
    vector<double> Price(N+1);
    /*Fix the terminal condition*/
    for (int i=0;i<=N;i++)
    {
        Price[i]=Payoff(Model.S(N,i));
        
        
    }    /*For each period n we compute in all the
          nodes*/
    for (int n=N-1; n>=0; n--)
    {
        for (int i=0;i<=n; i++)
        {
            Price[i]=(q*Price[i+1]+(1-q)*Price[i])/(1+Model.getR());
            
        }
    }
    return Price[0];
    
}

// Standard normal probability density function

double European_Option :: norm_pdf(const double& x)
{
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function

double European_Option :: norm_cdf(const double& x)
{
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0)
    {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    }
    else
    {
        return 1.0 - norm_cdf(-x);
    }
}

// This calculates d_j, for j in {1,2}. This term appears in the closed
// form solution for the European call or put price

double European_Option :: d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T)
{
    return (log(S0/K) + (R + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

// Calculate the European call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T

double European_Option :: PriceBS()
{
    if(type == Call)
    {
    return S0 * norm_cdf(d_j(1, S0, K, R, v, T))-K*exp(-R*T) * norm_cdf(d_j(2, S0, K, R, v, T));
    }
    else if(type == Put)
    {
    return -S0*norm_cdf(-d_j(1, S0, K, R, v, T))+K*exp(-R*T) * norm_cdf(-d_j(2, S0, K, R, v, T));
    }
    return 0;
}


