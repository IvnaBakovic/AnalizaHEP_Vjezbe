#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>

void Analyzer::Loop()
{
   TH1F *recoMass = new TH1F("recoMass","",50,0.,700.); 
   TLorentzVector Higgs;
   TF1 *theoryFunction = new TF1("theoryFunction","[0]*TMath::Exp(-x/[1])",0.,700.);
   theoryFunction->SetParameters(1000.,100.);
   TCanvas *c = new TCanvas("c","c");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     Higgs.SetPxPyPzE(particle1_px+particle2_px,particle1_py+particle2_py,particle1_pz+particle2_pz,particle1_E+particle2_E);
     recoMass->Fill(Higgs.M());
   }
  recoMass->SetStats(0);
  recoMass->Fit(theoryFunction);
  recoMass->SetMarkerStyle(20);
  recoMass->SetMarkerColor(kBlack);
  recoMass->SetMarkerSize(0.6);
  recoMass->Draw("EP");
  TLegend *leg = new TLegend(0.65,0.7,0.9,0.9);
  leg->AddEntry(recoMass,"Rekontruirana masa","f");
  leg->AddEntry(theoryFunction,"N_{SM}EXP(-x/Z_{SM})","f");
  leg->Draw();
  c->SaveAs("recoMass.pdf");
}

void Analyzer::CalculatePValue()
{
   double a = -1.;
   double b = 190.;
   double c = 0.02;
   double mH;
   float chi2Expected, chi2Observed;
   float expectedPValue, observedPValue;
   TH1F *predictedHiggs;
   for(int i = 10; i <= 690, i+=5)
   { 
      mH = i/1.0;
      predictedHiggs = new TH1F("noHiggs","",200,0.,700.);
      for(int i = 0; i < 10000; i++)
      {
        if(r3->Rndm()>a*(mH-b)+c)predictedHiggs->Fill(r3->Exp(100));
        else predictedHiggs->Fill(r3->Gaus(mH,0.0236*mH));
      }
      theoryFunction->FixParameter(1,100.);
      predictedHiggs->Fit(theoryFunction,"Q","",mH-10.,mH+10);
      chi2Expected = theoryFunction -> GetChisquare();

      expectedPValue = 
   }

  
}
