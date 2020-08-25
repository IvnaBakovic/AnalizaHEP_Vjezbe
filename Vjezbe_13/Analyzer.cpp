#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLine.h>

void Analyzer::Loop()
{
   TH1F *histo = new TH1F("histo", "",100,160,170);
   TH1F *testStatisticPDF = new TH1F("test","",100,160,170);
   double sum = 0;
   TCanvas *c = new TCanvas("c","c");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histo->Fill(height);
      sum+=height;
   }
  mediumHeight = sum / nentries;
  
  cout<< mediumHeight <<endl;

  c->cd();
  double sumHeight = 0.;
  for(int i = 0; i < 100000; i++)
  {
    sumHeight = 0.;
    for(int j = 0; j < 100; j++)
       {
         sumHeight+=(r3->Gaus(164.7,7.1));
       }
    testStatisticPDF->Fill(sumHeight/100);
  }
  testStatisticPDF->Scale(1./testStatisticPDF->Integral());
  double pValue = testStatisticPDF->Integral(testStatisticPDF->FindBin(mediumHeight),100); //100 broj binova
  cout<<"p-value je "<< pValue <<endl;
  double zScore = TMath::Sqrt(2)*TMath::ErfcInverse(2*pValue);
  cout<<"signifikasnost je "<< zScore <<endl;

  testStatisticPDF->Draw();
  //histo->SetLineColor(kRed);  //ovo nema gaussian oblik i ne treba crtati histogram
  //histo->Draw();
  c->SaveAs("height.pdf");
}
   
void Analyzer::CompareCountries(TString countryName, double mu, double sigma)
{

   TH1F *Spain = new TH1F("histo", "",150,160,175);
   TH1F *otherCountry = new TH1F("test","",150,160,175);
   TLegend *legend = new TLegend(0.7,0.8,0.9,0.9);
   TCanvas *c1 = new TCanvas("c1","c1");
   double sumHeightSpain = 0., sumHeightOtherCountry=0.;
  for(int i = 0; i < 100000; i++)
  {
    sumHeightSpain = 0.,sumHeightOtherCountry=0.;
    for(int j = 0; j < 100; j++)
       {
         sumHeightSpain+=(r3->Gaus(168.0,7.0)); //Spain
         sumHeightOtherCountry+=(r3->Gaus(mu,sigma)); //otherCountry
       }
    Spain->Fill(sumHeightSpain/100);
    otherCountry->Fill(sumHeightOtherCountry/100);
  }
  c1->cd();
  
  //Spain->Scale(1./Spain->Integral());
  Spain->SetLineColor(kBlue);
  Spain->SetFillColor(kBlue);
  Spain->Draw();
  Spain->SetTitle("Španjolska i " +countryName);
  otherCountry->SetLineColor(kRed);
  otherCountry->SetFillColor(kRed);
  //otherCountry->Scale(1./otherCountry->Integral());
  otherCountry->Draw("SAME");
  legend->AddEntry(Spain,"Španjolska","f");
  legend->AddEntry(otherCountry,countryName,"f");
  legend->SetTextSize(0.03);
  legend->Draw();
  TLine *line = new TLine(mediumHeight, 0. , mediumHeight, 5000);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->Draw();
  c1->SaveAs("usporedba"+countryName+".pdf");

  //Spain->Scale(1./Spain->Integral());
  //otherCountry->Scale(1./otherCountry->Integral());
  double pValueSpain = Spain->Integral(Spain->FindBin(mediumHeight),150); 
  double pValueCountry = otherCountry->Integral(otherCountry->FindBin(mediumHeight),150);
  cout << "pValue for Spain is "<<pValueSpain<< " and pValue for "<<countryName<< " is "<<pValueCountry<<endl;

  
   double pSpain = 0.;
   double pOtherCountry = 0.;

   if( mu < 168.0)
   {
     pSpain = Spain->Integral(0, Spain->FindBin(mediumHeight));
     pOtherCountry = otherCountry->Integral(otherCountry->FindBin(mediumHeight), 150);
     cout<<pSpain<<endl;
   }

   else
   {
     pSpain = Spain->Integral(Spain->FindBin(mediumHeight), 150);
     pOtherCountry = otherCountry->Integral(0, otherCountry->FindBin(mediumHeight));
   }

   cout << "We can exclude alternative hypothesis of " << countryName << " at " << (1-pOtherCountry/pSpain)*100 << "\% CL." << endl;


}
