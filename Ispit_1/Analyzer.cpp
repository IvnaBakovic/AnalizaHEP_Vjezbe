#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLorentzVector.h>

void Analyzer::Loop()
{
   TCanvas *c = new TCanvas("c","c");
   TH1F *histoPt1 = new TH1F("histoPt1","Transverse momentum",50,0.,250.); 
   TH1F *histoPt2 = new TH1F("histoPt2","Transverse momentum",50,0.,250.); 
   TH1F *recoMass = new TH1F("recoMass","Invariant mass",50,0,200);
   TF1 *function = new TF1("function","[0]*TMath::Exp(-x/[1])",0,200);
   function-> SetParameters(1.,100.);
   TLorentzVector particle1, particle2, newParticle;
   c->Divide(2);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histoPt1->Fill(TMath::Sqrt(particle1_px*particle1_px+particle1_py*particle1_py));
      histoPt2->Fill(TMath::Sqrt(particle2_px*particle2_px+particle2_py*particle2_py));
      particle1.SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
      particle2.SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);
      newParticle = particle1 + particle2;
      recoMass->Fill(newParticle.M());
   }
  c->cd(1);
  gPad->SetLeftMargin(0.15);
  histoPt1->SetStats(0);
  histoPt2->SetStats(0);
 
  histoPt2->GetXaxis()->SetTitle("p_{T} [GeV]");
  histoPt2->GetXaxis()->SetLabelSize(0.04);
  histoPt2->GetYaxis()->SetTitle("Events / 5 GeV");
  histoPt2->GetYaxis()->SetTitleOffset(1.8);
  histoPt2->GetYaxis()->SetLabelSize(0.04);
  histoPt2->SetLineColor(kBlue -2);
  histoPt1->SetLineColor(kRed);
  histoPt1->SetLineStyle(kDashed);
  histoPt2->Draw();
  histoPt1->Draw("SAME");
  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(histoPt1,"Particle 1", "f");
  leg->AddEntry(histoPt2,"Particle 2", "f");
  leg->Draw();

  c->cd(2);
  gPad->SetLeftMargin(0.15);
  recoMass->SetStats(0);
  recoMass->GetXaxis()->SetTitle("m_{2} [GeV]");
  recoMass->GetYaxis()->SetTitle("Events / 4 GeV");
  recoMass->GetYaxis()->SetTitleOffset(1.5);

  recoMass->SetMarkerColor(kBlack);
  recoMass->SetMarkerStyle(7);
  gStyle->SetOptFit();
  recoMass->Fit(function);
  //function->SetTitle("Invariant mass;m_{2} [GeV];Events / 4 GeV");
  //function->SetLineColor(kRed);
  recoMass->Draw("P");
  TLegend *leg1 = new TLegend(0.6,0.7,0.9,0.9);
  leg1->AddEntry(recoMass,"Data Invariant mass","p");
  leg1->AddEntry(function,"Exponential function","l");
  leg1->Draw();


  c->SaveAs("histogram2.pdf");
}
