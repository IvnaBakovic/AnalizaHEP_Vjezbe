#include <iostream>
#include <fstream>

// My own class
#include <Analyzer.h>

using namespace std;

int main()
{
  // Declare Analyzer
  Analyzer *analyzer;

  analyzer = new Analyzer();

  analyzer->Loop();
  //analyzer->CompareCountries("Francuska", 164.7, 7.1);
  analyzer->CompareCountries("Italija", 166.1, 6.5);
  //analyzer->CompareCountries("Nizozemska", 170.3, 7.5);



  return 0;
}
