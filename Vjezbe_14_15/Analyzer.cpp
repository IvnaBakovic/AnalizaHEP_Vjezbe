#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TGraph.h>

void Analyzer::Loop()
{
   recoMass = new TH1F("recoMass","",50,0.,700.); 
   TLorentzVector Higgs;
   theoryFunction = new TF1("theoryFunction","[0]*TMath::Exp(-x/[1])",0.,700.);
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

void Analyzer::GenerateTestStatisticPDF(int nsteps)
{
  TCanvas *c1= new TCanvas("c1","c1",700,700);

  TestStatistic_PDF = new TH1F("TestStatistic_PDF","TestStatistic_PDF",300,0,30);

  TF1 *theoreticalPDF = new TF1("theoreticalPDF","[0]/TMath::Exp(x/[1])",0,700);
  theoreticalPDF->SetParameter(0,1000.);
  theoreticalPDF->SetParameter(1,100.);

  TH1F *toy_histo;

  float chi2;
  float m_H = 0.;

  for(int i = 0; i < nsteps; i++)
  {
    TString name = "toy_histo_" + std::to_string(i);
    toy_histo = new TH1F(name,"toy_histo",200,0.,700.);

    for(int j = 0; j < 100000; j++) toy_histo->Fill(r3->Exp(100));

    theoreticalPDF->FixParameter(1,100.); //fix the parameter to theoretical value

    for(int i = 10; i < 690; i+=5) // do the fit doing 5 GeV steps in 10-690 GeV region
    {
      m_H = i/1.0;

      toy_histo->Fit(theoreticalPDF,"Q","",m_H-10,m_H+10); // perform the fit in the 20 GeV window
      chi2 = theoreticalPDF->GetChisquare();
      TestStatistic_PDF->Fill(chi2);
    }
  }

  TestStatistic_PDF->SetStats(0);
  gPad->SetBottomMargin(0.2);
  TestStatistic_PDF->SetTitle("Test statistic PDF");
  TestStatistic_PDF->GetXaxis()->SetTitle("#chi^{2}(N,#zeta_{SM})");
  TestStatistic_PDF->GetXaxis()->SetTitleOffset(1.5);
  TestStatistic_PDF->Scale(1./TestStatistic_PDF->Integral());
  TestStatistic_PDF->Draw("HIST");

  c1->SaveAs("TestStatisticPDF.pdf");

  
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

    TCanvas *c2= new TCanvas("c2","c2",700,700);

    TGraph *expected_scan = new TGraph();
    TGraph *observed_scan = new TGraph();
   int k = 0;

  theoryFunction = new TF1("1theoreticalPDF","[0]/TMath::Exp(x/[1])",0,700);
  theoryFunction->SetParameter(0,1000.);
  theoryFunction->SetParameter(1,100.);
   for(int i = 10; i <= 690; i+=5)
   { 
      mH = i/1.0;
      predictedHiggs = new TH1F("Higgs","",200,0.,700.);
      for(int i = 0; i < 10000; i++)
      {
        if(r3->Rndm()>a*(mH-b)+c)predictedHiggs->Fill(r3->Exp(100));
        else predictedHiggs->Fill(r3->Gaus(mH,0.0236*mH));
      }
      theoryFunction->FixParameter(1,100.);
      predictedHiggs->Fit(theoryFunction,"Q","",mH-10.,mH+10);
      chi2Expected = theoryFunction -> GetChisquare();

      expectedPValue = TestStatistic_PDF->Integral(TestStatistic_PDF->FindBin(chi2Expected),TestStatistic_PDF->GetNbinsX())/TestStatistic_PDF->Integral();
      
      expected_scan->SetPoint(k,mH,expectedPValue);

    theoryFunction->FixParameter(1,100.);
    recoMass->Fit(theoreticalPDF,"Q","",mH-10.,mH+10.);
    chi2Observed = theoryFunction->GetChisquare();

    observedPValue = TestStatistic_PDF->Integral(TestStatistic_PDF->FindBin(chi2Observed),TestStatistic_PDF->GetNbinsX())/TestStatistic_PDF->Integral();

    observed_scan->SetPoint(k,mH,observedPValue);
    k++;

   }
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLeftMargin(0.1);

  expected_scan->SetLineColor(kBlack);
  expected_scan->SetLineStyle(kDashed);
  expected_scan->SetLineWidth(2);
  expected_scan->SetMarkerColor(kBlack);
  expected_scan->SetMarkerStyle(20);
  expected_scan->SetMarkerSize(0.6);

  observed_scan->SetLineColor(kRed);
  observed_scan->SetLineWidth(2);
  observed_scan->SetMarkerColor(kRed);
  observed_scan->SetMarkerStyle(20);
  observed_scan->SetMarkerSize(0.6);


  TMultiGraph *mg = new TMultiGraph();
  mg->Add(expected_scan);
  mg->Add(observed_scan);
  mg->SetTitle("Observed p-value scan");
  mg->SetMinimum(0.00001);
  mg->Draw("ALP");
  mg->GetXaxis()->SetRangeUser(0,700);
  mg->GetXaxis()->SetTitle("m_{H}");
  mg->GetYaxis()->SetTitle("p-value");
  mg->GetYaxis()->SetTitleOffset(0.7);


  c2->SaveAs("ObservedPValueScan.pdf");

  
}
