//
//  American_Option.cpp
//  TD6
//
//  Created by Nicolas Lissak on 29/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include "American_Option.hpp"
#include "BinModel.hpp"
#include "Option.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;

American_Option::American_Option(double K, int N, OptionType type) : Option(K, N, type)
{
    
}
American_Option:: American_Option (int N,double S0,double K,double R,double v,double T,OptionType type) : Option(N, S0, K, R, v, T, type)
{
    
}

double American_Option :: Payoff(double z)const
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
double American_Option:: Gaussian_Box_Muller()
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


double American_Option :: MCPricer()
{
    double S_adjust = S0 * exp(R-0.5*v*v);
    double S_cur = 0.0;
    double payoff_sum = 0.0;
    
    for (int i=0; i<N; i++)
    {
        double gauss_bm = Gaussian_Box_Muller();
        S_cur = S_adjust * exp(sqrt(v*v)*gauss_bm);
        if(type == Call)
        {
            payoff_sum += max(S_cur - K, 0.0);
        }
        else if (type == Put)
        {
            payoff_sum += max(K - S_cur, 0.0);
        }
    }
    
    return (payoff_sum / static_cast<double>(N)) * exp(-R);
}

//Methode PriceBySNell sans BinLattice Template

bool American_Option:: ComparPrice (const double&T)
{
    double a,b;
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
    a = (payoff_sum / static_cast<double>(N)) * exp(-R*T);

    double S_adjust2 = S0 * exp(R-0.5*v*v);
    double S_cur2 = 0.0;
    double payoff_sum2 = 0.0;
        
    for (int i=0; i<N; i++)
        {
            double gauss_bm2 = Gaussian_Box_Muller();
            S_cur2 = S_adjust2 * exp(sqrt(v*v)*gauss_bm2);
            if(type == Call)
            {
                payoff_sum2 += max(S_cur2 - K, 0.0);
            }
            else if (type == Put)
            {
                payoff_sum2 += max(K - S_cur2, 0.0);
            }
        }
        
    b =(payoff_sum2/ static_cast<double>(N)) * exp(-R);
    
    if(a>b)
    {
        cout<<"It's convenient to exercice the american option at the time : "<<T<<endl;
        return true;
    }
    else
    {
        cout<<"It's not convenient to exercice the american option at the time : "<<T<<endl;
        return false;
    }
}

double American_Option::PriceBySnellBS (const double& T,const int& N,const double &R,const double &v)const
{
    double h,u,d,r;
    
    h = T/N;
    u = exp( ((v*v)+R/2) *h+v*sqrt(h))-1;
    d = exp( ((v*v)+R/2) *h-v*sqrt(h))-1;
    r=exp(R*h)-1;
    BinModel Model(100, u, d, r);
    double q=Model.RiskNeutProb();
    vector<double>Price(N+1);
    double ContVal;
    
    for (int i=0;i<N;i++)
    {
        Price[i]=Payoff(Model.S(N,i));
        
    }
    for (int n=N-1; n>=0;n--)
    {
        for (int i=0;i<=N;i++)
        {
            ContVal=(q*Price[i+1]+(1-q)*Price[i])/(1+Model.getR());
            Price[i]=Payoff(Model.S(n,i));
            if (ContVal>Price[i])
            {
                Price[i]=ContVal;
            }
        }
    }
    return Price[0];
}


double American_Option::PriceBySnell (const BinModel& Model) const
{
    double q=Model.RiskNeutProb();
    vector<double>Price(GetN()+1);
    double ContVal;
    
    for (int i=0;i<GetN();i++)
    {
        Price[i]=Payoff(Model.S(GetN(),i));
        
    }
    for (int n=GetN()-1; n>=0;n--)
    {
        for (int i=0;i<=n;i++)
        {
            ContVal=(q*Price[i+1]+(1-q)*Price[i])/(1+Model.getR());
            Price[i]=Payoff(Model.S(n,i));
            if (ContVal>Price[i])
            {
                Price[i]=ContVal;
            }
        }
    }
    return Price[0];
}



double American_Option::PriceBySnellBin (const BinModel& Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree)
{
    double q=Model.RiskNeutProb();
    PriceTree.SetN(GetN());
    StoppingTree.SetN(GetN());
    double ContVal;
    
    for (int i=0;i<=GetN();i++)
    { PriceTree.SetNode(GetN(),i,Payoff(Model.S(GetN(),i))); StoppingTree.SetNode(GetN(),i,1);
    }
    for (int n=GetN()-1;n>=0;n--)
    {
        for (int i=0;i<=n;i++)
        {
            ContVal=(q*PriceTree.GetNode(n+1,i+1)+(1-q)*PriceTree.GetNode(n+1,i)/(1+Model.getR()));
            PriceTree.SetNode(n,i,Payoff(Model.S(n,i)));
            StoppingTree.SetNode(n,i,1);
            if (ContVal>PriceTree.GetNode(n,i))
            {
                PriceTree.SetNode(n,i,ContVal);
                StoppingTree.SetNode(n,i,0);
                
            }
            else if (PriceTree.GetNode(n,i)==0.0)
            {
                StoppingTree.SetNode(n,i,0);
                
            }
            
        }
        
    }
    
    return PriceTree.GetNode(0,0);
}
double American_Option::PriceBySnellBinBS (const double& T,const int& N,const double &R,const double &v, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree)
{

    double h,u,d,r;
    h = T/N;
    u = exp( ((v*v)+R/2) *h+v*sqrt(h))-1;
    d = exp( ((v*v)+R/2) *h-v*sqrt(h))-1;
    r=exp(R*h)-1;
    BinModel Model(100, u, d, r);
    double q=Model.RiskNeutProb();
    PriceTree.SetN(N);
    StoppingTree.SetN(N);
    double ContVal;
    
    for (int i=0;i<=N;i++)
    { PriceTree.SetNode(N,i,Payoff(Model.S(N,i))); StoppingTree.SetNode(N,i,1);
    }
    for (int n=N-1;n>=0;n--)
    {
        for (int i=0;i<=n;i++)
        {
            ContVal=(q*PriceTree.GetNode(n+1,i+1)+(1-q)*PriceTree.GetNode(n+1,i)/(1+Model.getR()));
            PriceTree.SetNode(n,i,Payoff(Model.S(n,i)));
            StoppingTree.SetNode(n,i,1);
            if (ContVal>PriceTree.GetNode(n,i))
            {
                PriceTree.SetNode(n,i,ContVal);
                StoppingTree.SetNode(n,i,0);
                
            }
            else if (PriceTree.GetNode(n,i)==0.0)
            {
                StoppingTree.SetNode(n,i,0);
                
            }
            
        }
        
    }
    
    return PriceTree.GetNode(0,0);
}
