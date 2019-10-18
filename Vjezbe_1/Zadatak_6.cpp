#include <iostream>
using namespace std;

class ElementaryParticle {

  public:
    float mass;
    bool boson;
    string name;
    
    void printInfo ()
    {
	cout << "Enter a mass: "<< mass;
        
        cout << "Enter a name: "<< name;
    
        cout << "Enter a number: "<< boson;

	}
};



int main () {
  
  ElementaryParticle Higgs;

  Higgs.mass = 125;
  Higgs.boson = true;
  Higgs.name = "Higgs boson";
  Higgs.printInfo();
  return 0;
}

