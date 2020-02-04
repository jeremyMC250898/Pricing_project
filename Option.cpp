//
//  Option.cpp
//  TD6
//
//  Created by Nicolas Lissak on 29/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include "Option.hpp"

Option:: Option(double _K, double _N, OptionType _type) : K(_K), N(_N), type(_type)
{
  
}
Option :: Option(int N,double S0,double K,double R,double v,double T,OptionType type) : N(N),S0(S0),K(K),R(R),v(v),T(T),type(type)
{
    
}

