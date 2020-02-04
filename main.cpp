//
//  main.cpp
//  TD6
//
//  Created by Nicolas Lissak on 25/11/2019.
//  Copyright © 2019 Nicolas Lissak. All rights reserved.
//

#include <iostream>
#include "BinModel.hpp"
#include "Option.hpp"
#include "European_Option.hpp"
#include "American_Option.hpp"
#include "Digital_Option.hpp"
#include "BinLattice.hpp"

void menu()
{
    int choix;
    do
    {
        cout<<endl<<" ----------------------- MENU -----------------------"<<endl<<endl;
        
        cout<<" Which option do you want to work with? "<<endl;
        cout<<"1. European Option "<<endl;
        cout<<"2. American Option "<<endl;
        cout<<"3. Asian Option "<<endl;
        cout<<"4. Digital Option "<<endl;
        cout<<"0. Quitter"<<endl<<endl;
        
        cout<<"Choix : ";
           cin>>choix;
           cout<<endl;
    
           switch(choix)
           {
               case 0 : break;
                   
               case 1 :
                   cout<<" With which method do you want to evaluate your option ? "<<endl;
               break;
    
               case 2 :
               break;
    
               case 3 :
               break;
    
               case 4 :
               break;
    
               case 5 :
               break;
    
               case 6 :
               break;
    
               case 7 :
               break;
    
               case 8 :
               break;
    
               case 9 :
               break;
    
               case 10 :
               break;
    
               case 11 :
               break;
    
               case 12 :
    
               break;
           }
    
       }while (choix!=0);
    
    
    
}








using namespace std;
int main(int argc, const char * argv[])
{
    int num_sims = 4000;
    double S = 100.0;
    double K = 95;
    double r = 0.05;
    double v = 0.2;
    double T = 1;
    
    BinLattice<double> PriceTree;
    BinLattice<bool> StoppingTree;
    
    BinModel model(100, 0.03,-0.03, 0.02);
    model.CheckData();
    European_Option a(95,2, Call);
    European_Option b(95,2, Put);
    double res1,res2,res3,res4,res5,res6;
    res1 = a.PriceByCRR(model);
    res2= b.PriceByCRR(model);
    cout<<"Pour n = "<<a.GetN()<<" et K = "<<a.GetK()<<endl;
    
    cout<<"European_Option Call: H(n,i)= "<<res1<<endl;
    cout<<"European_Option Put: H(n,i)= "<<res2<<endl;

    
    American_Option c(95, 2, Call);
    American_Option d(95, 2, Put);
    
    double resbysnellbincall,resbysnellbinput;

    resbysnellbincall=c.PriceBySnellBin(model, PriceTree, StoppingTree);
    resbysnellbinput=d.PriceBySnellBin(model, PriceTree, StoppingTree);
    
    cout<<"American_Option Bin Lattice Call: H(n,i)= "<<resbysnellbincall<<endl;
    cout<<"American_Option Bin Lattice Put: H(n,i)= "<<resbysnellbinput<<endl;
    
    res3=c.PriceBySnell(model);
    res4=d.PriceBySnell(model);
    cout<<"American_Option Call: H(n,i)= "<<res3<<endl;
    cout<<"American_Option Put: H(n,i)= "<<res4<<endl;
    
    Digital_Option e(95, 2,Call);
    Digital_Option f(95, 2,Put);
    res5=e.PriceByCRR(model);
    res6=f.PriceByCRR(model);
    cout<<"Digital_Option Call: H(n,i)= "<<res5<<endl;
    cout<<"Digital_Option Put: H(n,i)= "<<res6<<endl;
    
    European_Option g(num_sims, S, K, r, v, T, Call);
    European_Option h(num_sims, S, K, r, v, T, Put);
   
    cout<<"Pour  num_sims = "<<num_sims<<", S = "<<S<<", K = "<<K<<", r = "<<r<<", v = "<<v<<", T = "<<T<<endl;
    
    cout << "MC European_Option Call Price : " << g.MCPricer() << std::endl;
    cout << "MC European_Option Put Price : " << h.MCPricer() << std::endl;
    
    American_Option i(num_sims, S, K, r, v, T, Call);
    American_Option j(num_sims, S, K, r, v, T, Put);
    cout << "MC American_Option Call Price : " << i.MCPricer() << std::endl;
    cout << "MC American_Option Put Price : " << j.MCPricer() << std::endl;
    
    European_Option k(num_sims, S, K, r, v, T, Call);
    European_Option l(num_sims, S, K, r, v, T, Put);
    cout<< "BS European_Option Call Price : "<< k.PriceBS()<<endl;
    cout<< "BS European_Option Put Price : "<< l.PriceBS()<<endl;
    
    American_Option test(num_sims, S, K, r, v, T, Call);
    American_Option test2(num_sims, S, K, r, v, T,Put);

    cout<<"American_Option BinomModelBS Call Price: "<< test.PriceBySnellBS(T, num_sims, r, v)<<endl;
    cout<<"American_Option BinomModelBS Put Price: "<< test2.PriceBySnellBS(T, num_sims, r, v)<<endl;
  
    cout<<"European_Option BinomModelBS Call Price: "<< k.PriceByCRRBS(T, num_sims, r, v)<<endl;
    cout<<"European_Option BinomModelBS Put Price: "<< l.PriceByCRRBS(T, num_sims, r, v)<<endl;
    
    cout<<"American_Option BinLatticeBS Call Price: "<< test.PriceBySnellBinBS(T, num_sims, r, v, PriceTree, StoppingTree)<<endl;
    cout<<"American_Option BinLatticeBS Put Price: "<< test2.PriceBySnellBinBS(T, num_sims, r, v, PriceTree, StoppingTree)<<endl;
       
    cout<<test.ComparPrice(0.5)<<endl;
    return 0;
}
