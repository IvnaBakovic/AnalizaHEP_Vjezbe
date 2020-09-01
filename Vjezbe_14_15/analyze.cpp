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
  analyzer->GenerateTestStatisticPDF(1000);
  analyzer->CalculatePValue();

  delete analyzer;

  return 0;
}
