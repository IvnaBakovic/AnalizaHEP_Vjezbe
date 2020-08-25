//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 24 07:16:46 2020 by ROOT version 6.22/00
// from TTree T/podaci o cesticama
// found on file: Analyzer.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "string"
#include <iostream>

using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventNumber;
   string          *DecayParticle1_Name;
   Int_t           DecayParticle1_isBoson;
   Float_t         DecayParticle1_mass;
   Float_t         DecayParticle1_px;
   Float_t         DecayParticle1_py;
   Float_t         DecayParticle1_pz;
   Float_t         DecayParticle1_E;
   Float_t         DecayParticle1_pt;
   string          *DecayParticle2_Name;
   Float_t         DecayParticle2_isBoson;
   Float_t         DecayParticle2_mass;
   Float_t         DecayParticle2_px;
   Float_t         DecayParticle2_py;
   Float_t         DecayParticle2_pz;
   Float_t         DecayParticle2_E;
   Float_t         DecayParticle2_pt;

   // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_DecayParticle1_Name;   //!
   TBranch        *b_DecayParticle1_isBoson;   //!
   TBranch        *b_DecayParticle1_mass;   //!
   TBranch        *b_DecayParticle1_px;   //!
   TBranch        *b_DecayParticle1_py;   //!
   TBranch        *b_DecayParticle1_pz;   //!
   TBranch        *b_DecayParticle1_E;   //!
   TBranch        *b_DecayParticle1_pt;   //!
   TBranch        *b_DecayParticle2_Name;   //!
   TBranch        *b_DecayParticle2_isBoson;   //!
   TBranch        *b_DecayParticle2_mass;   //!
   TBranch        *b_DecayParticle2_px;   //!
   TBranch        *b_DecayParticle2_py;   //!
   TBranch        *b_DecayParticle2_pz;   //!
   TBranch        *b_DecayParticle2_E;   //!
   TBranch        *b_DecayParticle2_pt;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analyzer.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analyzer.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   DecayParticle1_Name = 0;
   DecayParticle2_Name = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("DecayParticle1_Name", &DecayParticle1_Name, &b_DecayParticle1_Name);
   fChain->SetBranchAddress("DecayParticle1_isBoson", &DecayParticle1_isBoson, &b_DecayParticle1_isBoson);
   fChain->SetBranchAddress("DecayParticle1_mass", &DecayParticle1_mass, &b_DecayParticle1_mass);
   fChain->SetBranchAddress("DecayParticle1_px", &DecayParticle1_px, &b_DecayParticle1_px);
   fChain->SetBranchAddress("DecayParticle1_py", &DecayParticle1_py, &b_DecayParticle1_py);
   fChain->SetBranchAddress("DecayParticle1_pz", &DecayParticle1_pz, &b_DecayParticle1_pz);
   fChain->SetBranchAddress("DecayParticle1_E", &DecayParticle1_E, &b_DecayParticle1_E);
   fChain->SetBranchAddress("DecayParticle1_pt", &DecayParticle1_pt, &b_DecayParticle1_pt);
   fChain->SetBranchAddress("DecayParticle2_Name", &DecayParticle2_Name, &b_DecayParticle2_Name);
   fChain->SetBranchAddress("DecayParticle2_isBoson", &DecayParticle2_isBoson, &b_DecayParticle2_isBoson);
   fChain->SetBranchAddress("DecayParticle2_mass", &DecayParticle2_mass, &b_DecayParticle2_mass);
   fChain->SetBranchAddress("DecayParticle2_px", &DecayParticle2_px, &b_DecayParticle2_px);
   fChain->SetBranchAddress("DecayParticle2_py", &DecayParticle2_py, &b_DecayParticle2_py);
   fChain->SetBranchAddress("DecayParticle2_pz", &DecayParticle2_pz, &b_DecayParticle2_pz);
   fChain->SetBranchAddress("DecayParticle2_E", &DecayParticle2_E, &b_DecayParticle2_E);
   fChain->SetBranchAddress("DecayParticle2_pt", &DecayParticle2_pt, &b_DecayParticle2_pt);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
