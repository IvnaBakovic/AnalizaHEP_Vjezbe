#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
   TLegend *legend;
   TCanvas *c = new TCanvas("c", "c", 900, 900);
   histoSignal[0] = new TH1F("0","",50,0,100.);
   histoSignal[1] = new TH1F("1","",50,-1.5,3);
   histoSignal[2] = new TH1F("3","",50,0.,0.1);
   histoSignal[3] = new TH1F("3","",50,0.,5.);   
   histoSignal[4] = new TH1F("4","",50,0.,1.);
   histoSignal[5] = new TH1F("5","",50,0.,5.);   
   histoSignal[6] = new TH1F("6","",50,0.,5.);
   histoSignal[7] = new TH1F("7","",100,0,10);

   histoBackground[0] = new TH1F("8","",50,0.,100.);
   histoBackground[1] = new TH1F("9","",50,-1.5,3);
   histoBackground[2] = new TH1F("10","",50,0,0.5);
   histoBackground[3] = new TH1F("11","",50,0.,1.);
   histoBackground[4] = new TH1F("12","",50,0.,1.);
   histoBackground[5] = new TH1F("13","",50,0.,5.);
   histoBackground[6] = new TH1F("14","",50,0.,5.);
   histoBackground[7] = new TH1F("15","",100,0,10);

  //ele_pt, scl_eta, ele_hadronicOverEm, ele_gsfchi2, ele_fbrem, ele_ep, ele_eelepout i ele_pfChargedHadIso

   Init(signal);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      histoSignal[0]->Fill(ele_pt);
      histoSignal[1]->Fill(scl_eta);
      histoSignal[2]->Fill(ele_hadronicOverEm);
      histoSignal[3]->Fill(ele_gsfchi2);
      histoSignal[4]->Fill(ele_fbrem);
      histoSignal[5]->Fill(ele_ep);
      histoSignal[6]->Fill(ele_eelepout);
      histoSignal[7]->Fill(ele_pfChargedHadIso);
   }

   Init(background);

   nentries = fChain->GetEntriesFast();

   nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histoBackground[0]->Fill(ele_pt);
      histoBackground[1]->Fill(scl_eta);
      histoBackground[2]->Fill(ele_hadronicOverEm);
      histoBackground[3]->Fill(ele_gsfchi2);
      histoBackground[4]->Fill(ele_fbrem);
      histoBackground[5]->Fill(ele_ep);
      histoBackground[6]->Fill(ele_eelepout);
      histoBackground[7]->Fill(ele_pfChargedHadIso);
   }
   for(int i = 0; i < 8; i++)
{
   histoSignal[i]->SetStats(0);
   histoBackground[i]->SetStats(0);
}
   c->Divide(2,4);
   c->cd(1);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[0]->SetLineColor(kRed);
   histoSignal[0]->GetXaxis()->SetTitle("ele_pt");
   histoSignal[0]->GetYaxis()->SetTitle("Events");
   histoSignal[0]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[0]->GetMaximum() > histoSignal[0]->GetMaximum()) histoSignal[0]->SetMaximum(1.3*histoBackground[0]->GetMaximum());
   histoSignal[0]->Draw();
   histoBackground[0]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(2);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[1]->SetLineColor(kRed);
   histoSignal[1]->GetXaxis()->SetTitle("scl_eta");
   histoSignal[1]->GetYaxis()->SetTitle("Events");
   histoSignal[1]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[1]->GetMaximum() > histoSignal[1]->GetMaximum()) histoSignal[1]->SetMaximum(1.3*histoBackground[1]->GetMaximum());
   histoSignal[1]->Draw();
   histoBackground[1]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(3);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[2]->SetLineColor(kRed);
   histoSignal[2]->GetXaxis()->SetTitle("ele_hadronicOverEm");
   histoSignal[2]->GetYaxis()->SetTitle("Events");
   histoSignal[2]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[2]->GetMaximum() > histoSignal[2]->GetMaximum()) histoSignal[2]->SetMaximum(1.3*histoBackground[2]->GetMaximum());
   histoSignal[2]->Draw();
   histoBackground[2]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(4);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[3]->SetLineColor(kRed);
   histoSignal[3]->GetXaxis()->SetTitle("ele_gsfchi2)");
   histoSignal[3]->GetYaxis()->SetTitle("Events");
   histoSignal[3]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[3]->GetMaximum() > histoSignal[3]->GetMaximum()) histoSignal[3]->SetMaximum(1.3*histoBackground[3]->GetMaximum());
   histoSignal[3]->Draw();
   histoBackground[3]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(5);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[4]->SetLineColor(kRed);
   histoSignal[4]->GetXaxis()->SetTitle("ele_fbrem");
   histoSignal[4]->GetYaxis()->SetTitle("Events");
   histoSignal[4]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[4]->GetMaximum() > histoSignal[4]->GetMaximum()) histoSignal[4]->SetMaximum(1.3*histoBackground[4]->GetMaximum());
   histoSignal[4]->Draw();
   histoBackground[4]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(6);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[5]->SetLineColor(kRed);
   histoSignal[5]->GetXaxis()->SetTitle("ele_ep");
   histoSignal[5]->GetYaxis()->SetTitle("Events");
   histoSignal[5]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[5]->GetMaximum() > histoSignal[5]->GetMaximum()) histoSignal[5]->SetMaximum(1.3*histoBackground[5]->GetMaximum());
   histoSignal[5]->Draw();
   histoBackground[5]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(7);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[6]->SetLineColor(kRed);
   histoSignal[6]->GetXaxis()->SetTitle("ele_eelepout");
   histoSignal[6]->GetYaxis()->SetTitle("Events");
   histoSignal[6]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[6]->GetMaximum() > histoSignal[6]->GetMaximum()) histoSignal[6]->SetMaximum(1.3*histoBackground[6]->GetMaximum());
   histoSignal[6]->Draw();
   histoBackground[6]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();

   c->cd(8);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histoBackground[7]->SetLineColor(kRed);
   histoSignal[7]->GetXaxis()->SetTitle("ele_pfChargedHadIso");
   histoSignal[7]->GetYaxis()->SetTitle("Events");
   histoSignal[7]->GetYaxis()->SetTitleOffset(1.8);
   if ( histoBackground[7]->GetMaximum() > histoSignal[7]->GetMaximum()) histoSignal[7]->SetMaximum(1.3*histoBackground[7]->GetMaximum());
   histoSignal[7]->Draw();
   histoBackground[7]->Draw("SAME");
   legend = CreateLegend(histoSignal[0],histoBackground[0]);
   legend->Draw();
   c->SaveAs("elektronskeVarijable.pdf");
}

TLegend* Analyzer::CreateLegend(TH1F *histo1, TH1F *histo2)
{
  TLegend *leg;

  leg = new TLegend(0.7,0.7,0.9,0.9);

  leg->AddEntry(histo1, "Signal", "f");
  leg->AddEntry(histo2, "Background", "f");

  leg->SetTextSize(0.03);

  return leg;
}

