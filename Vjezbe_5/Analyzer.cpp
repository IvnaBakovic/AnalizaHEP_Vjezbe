#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TMath.h>

using namespace std;
void Analyzer::Loop()
{
   TH1F *histo1 = new TH1F("histo1","",50,0.,100.);
   TH1F *histo2 = new TH1F("histo2","",50,0.,100.);
   TH1F *histoHiggs = new TH1F("histo3","",50,0.,150.);
   TCanvas *c = new TCanvas("c","c");
   c->Divide(2);
   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   TLorentzVector particle1, particle2, Higgs;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      histo1->Fill(DecayParticle1_pt);
      histo2->Fill(DecayParticle2_pt);

      particle1.SetPxPyPzE(DecayParticle1_px,DecayParticle1_py,DecayParticle1_pz,DecayParticle1_E);
      particle2.SetPxPyPzE(DecayParticle2_px,DecayParticle2_py,DecayParticle2_pz,DecayParticle2_E);
      Higgs = particle1 + particle2;
      //histoHiggs -> Fill(TMath::Sqrt(TMath::Power(Higgs.Px(),2)+TMath::Power(Higgs.Py(),2))); direktno računanje
      histoHiggs -> Fill(Higgs.Pt());
   }
  c->cd(1);
  gPad->SetLeftMargin(0.15);
  histo1->SetStats(0);
  histo1->SetFillColor(kBlue);
  histo1->GetXaxis()->SetTitle("p_{t}");
  histo1->GetYaxis()->SetTitle("Events/2 Gev");
  histo1->SetTitle("Transverse momentum");
  histo1->Draw();  
  histo2->SetStats(0);
  histo2->SetLineColor(kRed);
  histo2->Draw("SAME");
  leg->AddEntry(histo1, "Particle 1","f"); 
  leg->AddEntry(histo2, "Particle 2","f"); 
  leg->Draw();

  c->cd(2);
  histoHiggs->SetStats(0);
  histoHiggs->SetFillColor(kBlue);
  histoHiggs->GetXaxis()->SetTitle("p_{t}");
  histoHiggs->GetYaxis()->SetTitle("Events/3 GeV");
  histoHiggs->SetTitle("Higgs transverse momentum");
  histoHiggs->Draw();
  c->SaveAs("transverseMomentum.pdf");

  
}
