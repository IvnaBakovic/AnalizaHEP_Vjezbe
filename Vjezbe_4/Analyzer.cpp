
// My own class
#include <Analyzer.h>

Analyzer::Analyzer()
{
}


Analyzer::~Analyzer()
{
}

void Analyzer::ReadFile()
{
string line;
bool _skipFirstLine=true;
ifstream myReadFile;
myReadFile.open("Analysis.txt");

if(myReadFile.is_open()){
while (getline(myReadFile,line))
{

stringstream linestream(line);

if(_skipFirstLine)
{
_skipFirstLine = false;
continue;
}

linestream >> EventNumber >> DecayParticle1_Name >> DecayParticle1_isBoson >> DecayParticle1_mass >> DecayParticle1_px >> DecayParticle1_py >> DecayParticle1_pz >> DecayParticle1_E >> DecayParticle1_pt >> DecayParticle2_Name >> DecayParticle2_isBoson >> DecayParticle2_mass >> DecayParticle2_px >> DecayParticle2_py >> DecayParticle2_pz >> DecayParticle2_E >> DecayParticle2_pt;
}
}
}
void Analyzer::ConvertTxtToRootFile()
{
   TFile *hfile;
   hfile = TFile::Open("Analyzer.root","RECREATE");

   TTree *tree = new TTree("T","podaci o cesticama");
   tree->Branch("EventNumber",&EventNumber,"EventNumber/I");
   tree->Branch("DecayParticle1_Name",&DecayParticle1_Name);
   tree->Branch("DecayParticle1_isBoson",&DecayParticle1_isBoson,"DecayParticle1_isBoson/I");
   tree->Branch("DecayParticle1_mass",&DecayParticle1_mass,"DecayParticle1_mass/F");
   tree->Branch("DecayParticle1_px",&DecayParticle1_px,"DecayParticle1_px/F");
   tree->Branch("DecayParticle1_py",&DecayParticle1_py,"DecayParticle1_py/F");
   tree->Branch("DecayParticle1_pz",&DecayParticle1_pz,"DecayParticle1_pz/F");
   tree->Branch("DecayParticle1_E",&DecayParticle1_E,"DecayParticle1_E/F");
   tree->Branch("DecayParticle1_pt",&DecayParticle1_pt,"DecayParticle1_pt/F");
   tree->Branch("DecayParticle2_Name",&DecayParticle2_Name);
   tree->Branch("DecayParticle2_isBoson",&DecayParticle2_isBoson,"DecayParticle2_isBoson/F");
   tree->Branch("DecayParticle2_mass",&DecayParticle2_mass,"DecayParticle2_mass/F");
   tree->Branch("DecayParticle2_px",&DecayParticle2_px,"DecayParticle2_px/F");
   tree->Branch("DecayParticle2_py",&DecayParticle2_py,"DecayParticle2_py/F");
   tree->Branch("DecayParticle2_pz",&DecayParticle2_pz,"DecayParticle2_pz/F");
   tree->Branch("DecayParticle2_E",&DecayParticle2_E,"DecayParticle2_E/F");
   tree->Branch("DecayParticle2_pt",&DecayParticle2_pt,"DecayParticle2_pt/F");
string line;
bool _skipFirstLine=true;
ifstream myReadFile;
myReadFile.open("Analysis.txt");

if(myReadFile.is_open()){
while (getline(myReadFile,line))
{

stringstream linestream(line);

if(_skipFirstLine)
{
_skipFirstLine = false;
continue;
}

linestream >> EventNumber >> DecayParticle1_Name >> DecayParticle1_isBoson >> DecayParticle1_mass >> DecayParticle1_px >> DecayParticle1_py >> DecayParticle1_pz >> DecayParticle1_E >> DecayParticle1_pt >> DecayParticle2_Name >> DecayParticle2_isBoson >> DecayParticle2_mass >> DecayParticle2_px >> DecayParticle2_py >> DecayParticle2_pz >> DecayParticle2_E >> DecayParticle2_pt;
tree->Fill();
}
}
   tree->Write();
 
   delete hfile;
   
}
