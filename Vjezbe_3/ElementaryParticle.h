#include <iostream>
#include <math.h>
#include <stdlib.h>     /* srand, rand */

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
    ElementaryParticle();
    double px, py, pz, E;
    int randomNumber;

    int random_number_x, random_number_y, random_number_z;

    void SetP(double _px, double _py, double _pz);
    void SetInfo(string name, bool is, double mass);
    void bosonDecay(ElementaryParticle*,ElementaryParticle*);
    void printPt();
    double pt();
    void printInfo(); 
   
   
}; 
