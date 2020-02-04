//
//  BinModel.hpp
//  TD6
//
//  Created by Nicolas Lissak on 25/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef BinModel_hpp
#define BinModel_hpp

#include <stdio.h>
#include "Option.hpp"

class BinModel
{
    private:
    double S0;
    double U;
    double D;
    double R;

    public:
    BinModel(double S0,double U,double D,double R);
    double RiskNeutProb() const;
    double S(int n, int i) const;
    double getR()const{return R;}
    int getU()const{return U;}
    int getD()const{return D;}
    void SetU(double U);
    void SetD(double D);
    void SetR(double R);
    
    
    /* Checking model data*/
    void CheckData() const;
    
    
};

#endif /* BinModel_hpp */
