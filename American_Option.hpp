//
//  American_Option.hpp
//  TD6
//
//  Created by Nicolas Lissak on 29/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef American_Option_hpp
#define American_Option_hpp

#include <stdio.h>
#include "Option.hpp"
#include "BinModel.hpp"
#include "BinLattice.hpp"

class American_Option : public Option
{
private:
    //int N;
    
public:
    //void SetN(double N);
    //int getN()const{return N;}
    
    // pricing American option
    American_Option(double K,int N,OptionType type);
    American_Option(int N,double S0,double K,double R,double v,double T,OptionType type);
    bool ComparPrice (const double&t);
    double MCPricer();
    double Gaussian_Box_Muller();
    double PriceBySnell(const BinModel& Model)const;
    double PriceBySnellBS(const double& T,const int& N,const double &R,const double &v) const;
    double PriceBySnellBin(const BinModel& Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree);
    double PriceBySnellBinBS (const double& T,const int& N,const double &R,const double &v, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree);
    double Payoff(double z) const override;
    //virtual double Payoff(double z) const=0;
    //virtual ~American_Option(){};
    
};

#endif /* American_Option_hpp */

