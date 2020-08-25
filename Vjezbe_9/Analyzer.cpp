#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>
#include <TF1.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   TH1F *histo = new TH1F("histo", "Lifetime measurement", 100, 0., 10.);
   TCanvas *c = new TCanvas("c","c");
   float sum=0;
   int n = 0;
   c->Divide(3);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
  
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histo->Fill(t);
      sum+=t;
      n++;
   }
   c->cd(1);
   TF1  *f1 = new TF1("f1","([0]/[1])*TMath::Exp(-x/[1])",0.,10.);
   f1->SetParNames("constNorm","tau");
   f1->SetParameters(100.,1.);
   histo->GetXaxis()->SetTitle("t/[s]");
   histo->GetYaxis()->SetTitle("Events");
   histo->Fit(f1);
   histo->Draw();

   c->cd(2);
   TF1 *likelihood = new TF1("Likelihood","(([0]/x)*TMath::Exp(-[1]/x))",0.,10.);
   likelihood->SetParameters(1.0,1.0);
   likelihood->SetTitle("Likelihood;#Tau;lnL");
   likelihood->Draw();

   //cout<<"Računanje maksimuma od likelihood "<<likelihood->GetMaximumX(0.5,2.)<<endl;
   cout << "Analitički izračunato preko ML: tau = " << sum/nentries << endl;
   cout << "Analitički izračunata standardna devijacija: sigma = " << sum/TMath::Sqrt(TMath::Power(n,3)) << endl;

   c->cd(3);
   gPad->SetLeftMargin(0.15);
   TF1 *log_likelihood = new TF1("Log_Likelihood","(-2.)*([0]*TMath::Log(1./x)-[1]*(1./x))",1.,2.);
   log_likelihood->SetTitle("Log-Likelihood;#Tau;-2lnL");
   log_likelihood->SetParameters(nentries,sum);
   log_likelihood->Draw();


   float tau = log_likelihood->GetMinimumX();
   float sigma_m = tau - log_likelihood->GetX(log_likelihood->GetMinimum()+1.,1.0,tau-0.01);
   float sigma_p = log_likelihood->GetX(log_likelihood->GetMinimum()+1.,tau, 10.0) - tau;

   cout<<"Dobiveno preko minimuma od -2lnL "<<  tau <<endl;
   cout << "Standardna devijacija određena kao 2lnL+1: sigma_+ = " << sigma_p << " sigma_- = " << sigma_m << endl;
 
   c->SaveAs("MaximumLikelihood.pdf");
}
