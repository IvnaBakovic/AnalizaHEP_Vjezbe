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
  analyzer->Loop("ggH125");
  analyzer->Loop("qqZZ");
  analyzer->PlotMassDkin();
  analyzer->FitMassLikelihood();
  analyzer->FitMass();

  delete analyzer;

  return 0;
}
