//
//  Digital_Option.cpp
//  TD6
//
//  Created by Nicolas Lissak on 09/12/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include "Digital_Option.hpp"
#include "BinModel.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

Digital_Option :: Digital_Option(double K, int N, OptionType type) : Option(K, N, type)
{
  

}
double Digital_Option :: Payoff(double z)const
{

    switch(type)
    {
        case Call: if(z>GetK()) return 1;
            return 0.0;
            break;

        case Put:  if (z<GetK()) return 1;
            return 0.0;
            break;
    }
    
}

double Digital_Option :: PriceByCRR(BinModel& Model)const
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
        { Price[i]=(q*Price[i+1]+(1-q)*Price[i])
            /(1+Model.getR()); }
    }
    return Price[0];
    
}

