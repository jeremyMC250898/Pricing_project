//
//  Asian_Option.hpp
//  TD6
//
//  Created by Nicolas Lissak on 09/12/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef Asian_Option_hpp
#define Asian_Option_hpp

#include <stdio.h>
#include "Option.hpp"

class Asian_Option : public Option
{
  

public:
    
    /* the payoff*/
    //Asian_Option(double K,int N,OptionType type);
    Asian_Option(int N,double S0,double K,double R,double v,double T,OptionType type);
    //double Payoff(double z) const override;
    
};
#endif /* Asian_Option_hpp */
