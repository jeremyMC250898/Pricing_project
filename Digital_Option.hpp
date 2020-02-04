//
//  Digital_Option.hpp
//  TD6
//
//  Created by Nicolas Lissak on 09/12/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef Digital_Option_hpp
#define Digital_Option_hpp

#include <stdio.h>
#include "Option.hpp"
#include "BinModel.hpp"

class Digital_Option : public Option
{
    /*Steps to expiry*/


public:
    
    /* the payoff*/
    Digital_Option(double K,int N,OptionType type);
    double Payoff(double z) const override;
    double PriceByCRR(BinModel&)const;

   
};

#endif /* Digital_Option_hpp */
