#include <ElementaryParticle.h>


    ElementaryParticle::ElementaryParticle(string name, bool is, double mass){
        nameParticle=name;
        isBoson = is;
        massParticle = mass;
    }
  
    // Member Functions() 
    void ElementaryParticle::printInfo() 
    { 
        if(isBoson==true)
        {
    
       cout << "Name of particle is " << nameParticle << ",mass of the particle is " << massParticle<< "and the particle is boson";
        }
       else
       {
           cout << "Name of particle is " << nameParticle << ",mass of the particle is " << massParticle<< "and the particle isn't boson";

       }
        
    }
