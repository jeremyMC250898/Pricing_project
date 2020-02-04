//
//  BinLattice.hpp
//  TD_5
//
//  Created by Nicolas Lissak on 24/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#ifndef BinLattice_hpp
#define BinLattice_hpp

#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cmath>


using namespace std;

template<typename Type> class BinLattice
{
private:
    int N;
    vector<vector<Type>> Lattice;
public:
    void SetN(int N)
    {
        this->N = N;
        Lattice.resize(N + 1);
        for (int n = 0; n <= N; n++) Lattice[n].resize(n + 1);
    }
    void SetNode(int n, int i, Type x)
    {
        Lattice[n][i] = x;
    }
    
    Type GetNode(int n, int i) const {
        return
        Lattice[n][i];
    }
    void Display() const
    {
        for (int n = 0; n <= N; n++)
        {
            for (int i = 0; i <= n; i++)
                cout << GetNode(n, i) << " ";
        }
        cout << endl;
    }
};

#endif /* BinLattice_hpp */
