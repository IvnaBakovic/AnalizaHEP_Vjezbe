#include <iostream>
#include <math.h>


using namespace std;

class ElementaryParticle 
{ 
    // Access specifier 
    public: 
  
    // Data Members 
    string nameParticle;
    bool isBoson;
    double massParticle; 
    ElementaryParticle(string name, bool is, double mass);


    void printInfo(); 
   
   
}; 
