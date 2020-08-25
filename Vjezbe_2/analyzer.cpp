#include <ElementaryParticle.h>


int main() { 
  
    // Declare an object of class geeks 
    ElementaryParticle particle1 = ElementaryParticle("Higgs boson", true, 125.18);
    ElementaryParticle particle2 = ElementaryParticle("Top quark", true, 172.76);
    ElementaryParticle* part3_pok;
    part3_pok = new ElementaryParticle("Higgs boson", true, 91.18);


    // accessing member function 
    particle1.printInfo();
    particle2.printInfo();
    part3_pok -> printInfo();
    return 0; 
} 
