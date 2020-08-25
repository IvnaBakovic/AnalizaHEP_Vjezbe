#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>

using namespace std;

// Declare class Analyzer.h
class Analyzer
{

public:

Analyzer();

~Analyzer();

void ReadFile();
void ConvertTxtToRootFile();

int EventNumber; 
string DecayParticle1_Name, DecayParticle2_Name; 
bool DecayParticle1_isBoson, DecayParticle2_isBoson; 
float DecayParticle1_mass, DecayParticle1_px, DecayParticle1_py, DecayParticle1_pz, DecayParticle1_E, DecayParticle1_pt, DecayParticle2_mass, DecayParticle2_px, DecayParticle2_py, DecayParticle2_pz, DecayParticle2_E, DecayParticle2_pt;
};
