#include <ElementaryParticle.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

int main() { 
  
    // Declare an object of class geeks 
    //ElementaryParticle particle1 = ElementaryParticle("Higgs boson", true, 125.18);
    //ElementaryParticle particle2 = ElementaryParticle("Top quark", true, 172.76);
    ElementaryParticle* Higgs;
    Higgs = new ElementaryParticle("Higgs boson", true, 125.6);
    ElementaryParticle *particle1 = new ElementaryParticle();
    ElementaryParticle *particle2 = new ElementaryParticle();
 
     ofstream myFile;
     myFile.open ("Analysis.txt");


    srand (time(NULL));
    int randomX,randomY,randomZ;
    double randX, randY, randZ;


    // accessing member function 
    //particle1.printInfo();
    //particle2.printInfo();
    //Higgs -> printInfo();

 myFile << "EventNumber DecayParticle1_Name DecayParticle1_isBoson DecayParticle1_mass DecayParticle1_px DecayParticle1_py DecayParticle1_pz DecayParticle1_E DecayParticle1_pt" <<
                       " DecayParticle2_Name DecayParticle2_isBoson DecayParticle2_mass DecayParticle2_px DecayParticle2_py DecayParticle2_pz DecayParticle2_E DecayParticle2_pt" << endl;


    for(int i = 0; i < 1000; i++)
    {

    randomX = 1000 - rand() % 2001; //imamo interval -1000,1000
    randomY = 1000 - rand() % 2001;
    randomZ = 1000 - rand() % 2001;

    randX = randomX/10.; //double brojevi -100.,100.
    randY = randomY/10.;
    randZ = randomZ/10.;

    Higgs->SetP(randX,randY,randZ);
    Higgs->bosonDecay(particle1, particle2);


    myFile << i << " "<< particle1->nameParticle <<" "<<particle1->isBoson <<" "<<particle1->massParticle <<" "<< particle1->px <<" "<<particle1->py<< " "<< particle1->pz << " "<< particle1->E << particle1 ->pt() << " "<< particle2->nameParticle <<" "<<particle2->isBoson <<" "<<particle2->massParticle <<" "<< particle2->px <<" "<<particle2->py<< " "<< particle2->pz << " "<< particle2->E << particle2->pt() <<endl;

    }
    myFile.close();
    return 0; 
} 
