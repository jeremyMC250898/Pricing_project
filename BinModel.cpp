//
//  BinModel.cpp
//  TD6
//
//  Created by Nicolas Lissak on 25/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include "BinModel.hpp"
#include "Option.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;
double BinModel :: RiskNeutProb() const
{
    return (R-D)/(U-D);
}
BinModel:: BinModel(double S0,double U,double D,double R)
{
    
    this->S0=S0;
    this->U=U;
    this->D=D;
    this->R=R;
    
    /*
     double dt,u,d,q;
     dt = T/n;
     u = exp(sigma*sqrt(dt));
     d = exp(-sigma*sqrt(dt));
     q = (exp(r*dt)-d)/(u-d);
     */
}


double BinModel:: S(int n, int i) const
{
    
    return S0*pow(1+U,i)*pow(1+D,n-i);
    
}


void BinModel::CheckData() const
{ /* Making sure that 0<S0, -1<D<U, -1<R */
    if (S0<=0.0 || U<=-1.0 || D<=-1.0 || U<=D || R<=-1.0)
    {
        cout<<"Illegal data ranges"<<endl;
        cout<<"Terminating program"<<endl;
        exit(1);
        
    }
    /* Checking for arbitrage*/
    if (R>=U || R<=D)
    {
        cout<<"Arbitrage exists "<<endl;
        cout<<"Terminating program "<<endl;
        exit(1);}
    
}
