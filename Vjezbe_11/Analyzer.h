#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

//ROOT headers
#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TString.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>

using namespace std;

// Declare class Analyzer
class Analyzer
{
  // public member declaration
  public:
    Analyzer( );
    ~Analyzer( );

    long int factorial(int);
    double binomial(int, double, int);
    double ClopperPearsonDown(int,int,double);
    double ClopperPearsonUp(int,int,double);
    void DisplayClopperPearsonInterval();
    void DrawClopperPearsonInterval(int, double);
    int throwDice();
};
