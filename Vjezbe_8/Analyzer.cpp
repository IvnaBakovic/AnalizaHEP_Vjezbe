
#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <THStack.h>
#include <TGraph.h>
#include <TF1.h>


void Analyzer::FitMass()
{
  	TCanvas *c3 = new TCanvas("c3","c3");
        TH1F *totalMass = new TH1F("totalMass","Reconstructed mass",50,70.,170.);
	totalMass->Add(massHiggsSignal);
	totalMass->Add(massHiggsBackground);
        
	c3->Divide(2);

	c3->cd(1);
	TF1 *BW = new TF1("Breit-Wigner","([0]*[1])/((x*x - [2]*[2])*(x*x - [2]*[2]) + 0.25*[1]*[1])",110,150);
	TF1 *Q = new TF1("Quadratic","([0] + [1]*x + [2]*x*x)",110,150);
        TF1 *total = new TF1("Total","(([0]*[1])/((x*x - [2]*[2])*(x*x - [2]*[2]) + 0.25*[1]*[1])+([3] + [4]*x + [5]*x*x))",110,150);

	
	BW->SetParameters(70,200, 125.0);
	Q->SetParameters(1,0.01,-0.0001);
	total->SetParameters(70,200, 125.0,1,0.01,-0.0001);
        total->SetParNames("D","#Gamma","M","A","B","C");

        BW->SetLineColor(kBlue);
        Q->SetLineColor(kYellow);
	total->SetLineColor(kRed);
        total->SetTitle("Fit function;Mass [GeV];Events");	
	total->Draw();
        BW->Draw("same");
	Q->Draw("same");
        TLegend *legF = new TLegend(0.7,0.7,0.9,0.9);
        legF->AddEntry(BW,"Breit-Wigner","l");
        legF->AddEntry(Q,"Quadratic function","l");
        legF->AddEntry(total,"Total function","l");
        legF->Draw();

	
	c3->cd(2);
	totalMass->GetXaxis()->SetRangeUser(110.0,150.0);
        gStyle->SetOptFit();
        totalMass->GetXaxis()->SetTitle("M/[GeV]");
        totalMass->GetYaxis()->SetTitle("Events");
	totalMass->Fit(total);
	totalMass->Draw("pe1x0");
        
   	c3->SaveAs("Fit.pdf");

}

void Analyzer::FitMassLikelihood()
{
  	TCanvas *c4 = new TCanvas("c4","c4");
        TH1F *totalMass = new TH1F("totalMass","Reconstructed mass",50,70.,170.);
	totalMass->Add(massHiggsSignal);
	totalMass->Add(massHiggsBackground);
        
	

        TF1 *total = new TF1("Total","([0]*[1])/(TMath::Power((x*x-[2]*[2]),2)+ 0.25*[1]*[1]) + ([3]*[4])/(TMath::Power((x*x-[5]*[5]),2) + 0.25*[4]*[4])+[6]+[7]*x+[8]*x*x",70,150);

	
        total->SetParNames("D_{1}","#Gamma_{1}","M_{1}","D_{2}","#Gamma_{2}","M_{2}","A","B","C");
	total->SetParameters(70,200, 125.0,70,200,90,1,0.01,-0.0001);


        totalMass->GetXaxis()->SetTitle("M/[GeV]");
        totalMass->GetYaxis()->SetTitle("Events/2 GeV");
	totalMass->Fit(total,"l");
	totalMass->Draw("pe1x0");
        
   	c4->SaveAs("FitLikelihood.pdf");

}


void Analyzer::Loop(TString fileName)
{

   TTree *tree;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/"+fileName+"/ZZ4lAnalysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/"+fileName+"/ZZ4lAnalysis.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+fileName+"/ZZ4lAnalysis.root:/ZZTree");
      dir->GetObject("candTree",tree);

   
   Init(tree);

   TFile* inputFile = new TFile("/home/public/data/"+fileName+"/ZZ4lAnalysis.root");
   float genSumWeights, eventWeight;
   TH1F *hCounters;


   hCounters = (TH1F*)inputFile->Get("ZZTree/Counters");
   genSumWeights = (Long64_t)hCounters->GetBinContent(40);

   TString name;
   TLorentzVector lep1, lep2, lep3, lep4, bos1, bos2, Higgs;

   for(int i = 0; i < 4; i++)
   {
      name = "Pt"+to_string(i);
      leptonPt[i] = new TH1F(name,"",50,0.,150.);
      name = "Phi"+to_string(i);
      leptonPhi[i] = new TH1F(name,"",50,0.,2.);
      name = "Eta"+to_string(i);
      leptonEta[i] = new TH1F(name,"",50,0.,2.);
      name = "BDT"+to_string(i);
      leptonBDT[i] = new TH1F(name,"",50,0.,5.);
   }

   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry > 10000 ) break;
      // if (Cut(ientry) < 0) continue;
     //( LepPt ), pseudorapiditet ( LepEta ), azimutalni kut ( LepPhi ) i BDT rezultat ( LepBDT ).
     eventWeight = (137.*1000.0*xsec*overallEventWeight/genSumWeights);
      for(int i = 0; i < 4; i++)
       {
        leptonPt[i] -> Fill(LepPt->at(i));
        leptonPhi[i] -> Fill(LepPhi->at(i));
        leptonEta[i] -> Fill(LepEta->at(i));
        leptonBDT[i] -> Fill(LepBDT->at(i));
       }
       lep1.SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0),0.);
       lep2.SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1),0.);
       lep3.SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2),0.);
       lep4.SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3),0.);
       bos1=lep1+lep2;
       bos2=lep3+lep4;
       Higgs=bos1+bos2;
       //gdje je signalna vjerojatnost spremljena pod nazivom p_GG_SIG_ghg2_1_ghz1_1_JHUGen , pozadinska pod nazivom p_QQB_BKG_MCFM ,
        Dkin = 1/(1+p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen); 
       if(fileName=="ggH125")
        {
         massHiggsSignal->Fill(Higgs.M(),eventWeight);
         DkinSignal->Fill(Dkin,eventWeight);
         massDkinSignal->Fill(Higgs.M(),Dkin,eventWeight);
        }
       if(fileName=="qqZZ")
        {
        massHiggsBackground->Fill(Higgs.M(),eventWeight);
        DkinBackground->Fill(1/(1+70*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen),eventWeight);
        massDkinBackground->Fill(Higgs.M(),Dkin,eventWeight);
        }

   }

   TLegend *leg;
   c = new TCanvas("c","c");
   c->Divide(2,2);
  
   c->cd(1);
   gPad->SetLeftMargin(0.15);
   leptonPt[0]->Draw();
   leptonPt[0]->SetTitle("Transverse momentum");
   leptonPt[0]->GetXaxis()->SetTitle("p_{t}");
   leptonPt[0]->GetYaxis()->SetTitle("Events");
   leptonPt[0]->SetMaximum(1.6*leptonPt[3]->GetMaximum());
   leptonPt[1]->SetLineColor(kRed);
   leptonPt[1]->Draw("SAME");
   leptonPt[2]->SetLineColor(kGreen);
   leptonPt[2]->Draw("SAME");
   leptonPt[3]->SetLineColor(kBlack);
   leptonPt[3]->Draw("SAME");

   leg = CreateLegend(leptonPt[0], leptonPt[1],leptonPt[2],leptonPt[3]);
   leg->Draw();

   c->cd(2);
   gPad->SetLeftMargin(0.15);
   leptonPhi[0]->SetMaximum(1.6*leptonPhi[3]->GetMaximum());
   leptonPhi[0]->Draw();
   leptonPhi[0]->SetTitle("Azimuthal angle");
   leptonPhi[0]->GetXaxis()->SetTitle("#Phi");
   leptonPhi[0]->GetYaxis()->SetTitle("Events");
   leptonPhi[1]->SetLineColor(kRed);
   leptonPhi[1]->Draw("SAME");
   leptonPhi[2]->SetLineColor(kGreen);
   leptonPhi[2]->Draw("SAME");
   leptonPhi[3]->SetLineColor(kBlack);
   leptonPhi[3]->Draw("SAME");
   leg = CreateLegend(leptonPhi[0], leptonPhi[1],leptonPhi[2],leptonPhi[3]);
   leg->Draw();

   c->cd(3);
   gPad->SetLeftMargin(0.15);
   leptonEta[0]->Draw();
   leptonEta[0]->SetTitle("Pseudorapadity");
   leptonEta[0]->GetXaxis()->SetTitle("#eta");
   leptonEta[0]->GetYaxis()->SetTitle("Events");
   leptonEta[1]->SetLineColor(kRed);
   leptonEta[1]->Draw("SAME");
   leptonEta[2]->SetLineColor(kGreen);
   leptonEta[2]->Draw("SAME");
   leptonEta[3]->SetLineColor(kBlack);
   leptonEta[3]->Draw("SAME");
   leg = CreateLegend(leptonEta[0], leptonEta[1],leptonEta[2],leptonEta[3]);
   leg->Draw();

   c->cd(4);
   gPad->SetLeftMargin(0.15);
   leptonBDT[0]->Draw();
   leptonBDT[0]->SetTitle("BDT");
   leptonBDT[0]->GetXaxis()->SetTitle("BDT result");
   leptonBDT[0]->GetYaxis()->SetTitle("Events");
   leptonBDT[1]->SetLineColor(kRed);
   leptonBDT[1]->Draw("SAME");
   leptonBDT[2]->SetLineColor(kGreen);
   leptonBDT[2]->Draw("SAME");
   leptonBDT[3]->SetLineColor(kBlack);
   leptonBDT[3]->Draw("SAME");
   leg = CreateLegend(leptonBDT[0], leptonBDT[1],leptonBDT[2],leptonBDT[3]);
   leg->Draw();
   
   
   

   for(int i = 0; i < 4; i++)
   {
      leptonPt[i] -> SetStats(0);
      leptonPhi[i] -> SetStats(0);
      leptonEta[i] -> SetStats(0);
      leptonBDT[i] -> SetStats(0);
   }
   if(fileName=="qqZZ"){c->SaveAs("leptoni"+fileName+".pdf");}
   if(fileName=="ggH125"){c->SaveAs("leptoni"+fileName+".pdf");}
   
}
void Analyzer::PlotMassDkin()
{
    //razmatranje THStack i hist same;
   /*TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   gPad->SetLeftMargin(0.15);
   massHiggsBackground->SetTitle("Reconstructed Higgs mass");
   //massHiggsBackground->Scale(1/massHiggsBackground->Integral());
   massHiggsBackground->GetXaxis()->SetTitle("M");
   massHiggsBackground->GetYaxis()->SetTitle("Events/2 GeV");
   massHiggsBackground->SetLineColor(kRed);
  massHiggsBackground->SetFillColor(kRed);
   massHiggsBackground->Draw("hist");
   //massHiggsSignal->Scale(1/massHiggsSignal->Integral());
  massHiggsSignal-> SetFillColor(kBlue);

   massHiggsSignal->Draw("hist same");
   c2->SaveAs("recoMass.pdf");*/

  /*TCanvas *c1= new TCanvas("c1","c1");
  THStack *hs = new THStack("hs","Reconstructed mass");
  massHiggsSignal-> SetLineColor(kBlue);
  massHiggsSignal-> SetFillColor(kBlue);
  massHiggsBackground->SetLineColor(kRed);
  massHiggsBackground->SetFillColor(kRed);
  massHiggsBackground->GetXaxis()->SetTitle("M/GeV");
  massHiggsBackground->GetYaxis()->SetTitle("Events");
  hs->Add(massHiggsSignal);
  hs->Add(massHiggsBackground);
  c1->cd();
  hs->Draw("hist");
   TLegend *leg2 = new TLegend(0.7,0.7,0.9,0.9);
   leg2->AddEntry(massHiggsSignal, "Signal", "f");
   leg2->AddEntry(massHiggsBackground, "Background", "f");
   leg2->Draw();
  c1->SaveAs("recoMass.pdf");*/

   TCanvas *c3 = new TCanvas("c3","c3");
   c3->Divide(2,2);
   c3->cd(1);
   gPad->SetLeftMargin(0.15);
   DkinBackground->SetStats(0);
   DkinSignal->SetStats(0);
   DkinBackground->SetTitle("Kinematic discriminant");
   DkinBackground->Scale(1/DkinBackground->Integral());
   DkinBackground->GetXaxis()->SetTitle("D_{kin}");
   DkinBackground->GetYaxis()->SetTitle("Events/2 GeV");
   DkinBackground->SetLineColor(kRed);
   DkinBackground->Draw("hist");
   DkinSignal->Scale(1/DkinSignal->Integral());
   DkinSignal->Draw("hist same");
   TLegend *leg1 = new TLegend(0.7,0.7,0.9,0.9);
   leg1->AddEntry(DkinSignal, "Signal", "f");
   leg1->AddEntry(DkinBackground, "Background", "f");
   leg1->Draw();

   c3->cd(2);


  gPad->SetLeftMargin(0.15);

  TGraph *ROC = new TGraph();

  for(int i=0; i < 1000; i++)
  {
      float x = 1. - DkinBackground->Integral(1, i+1);
      float y = 1. - DkinSignal->Integral(1,i+1);
      if ( x > 0.001 && y > 0.001 && x < 1.0 && y < 1.0) ROC->SetPoint(int(i),x,y);
  }
  ROC->SetMinimum(0.95);
  ROC->SetMaximum(1.0);

  ROC->SetMarkerStyle(20);
  ROC->SetMarkerSize(0.4);

  ROC->Draw("ap");

  ROC->GetXaxis()->SetLimits(0.00,0.05);
  ROC->GetXaxis()->SetTitle("Background efficiency");
  ROC->GetXaxis()->SetTitleFont(61);
  ROC->GetYaxis()->SetTitle("Signal efficiency");
  ROC->GetYaxis()->SetTitleFont(61);
  ROC->SetTitle("ROC curve");
  ROC->Draw("ap");
  c3->Update();

   c3->cd(3);
   gPad->SetRightMargin(0.15);
   massDkinSignal->SetStats(0);
   massDkinSignal->SetTitle("Signal");
   massDkinSignal->GetXaxis()->SetTitle("M/GeV");
   massDkinSignal->GetYaxis()->SetTitle("D_{kin}");
   massDkinSignal->Draw("COLZ");
   c3->cd(4);
   gPad->SetRightMargin(0.15);
   massDkinBackground->SetStats(0);
   massDkinBackground->SetTitle("Background");
   massDkinBackground->GetXaxis()->SetTitle("M/GeV");
   massDkinBackground->GetYaxis()->SetTitle("D_{kin}");
   massDkinBackground->Draw("COLZ");
   c3->SaveAs("massDkin.pdf");

}

TLegend* Analyzer::CreateLegend(TH1F *lepton_1, TH1F *lepton_2, TH1F *lepton_3, TH1F *lepton_4)
{
  TLegend *leg;

  leg = new TLegend(0.7,0.75,0.9,0.9);

  leg->AddEntry(lepton_1, "1.lepton", "f");
  leg->AddEntry(lepton_2, "2.lepton", "f");
  leg->AddEntry(lepton_3, "3.lepton", "f");
  leg->AddEntry(lepton_4, "4.lepton", "f");

  leg->SetTextSize(0.03);

  return leg;
}
