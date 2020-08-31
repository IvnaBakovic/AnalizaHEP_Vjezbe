#include <Analyzer.h>
#include <TMath.h>
#include <math.h>  
#include <TCanvas.h>
#include <THStack.h>
#include <TH1F.h>


Analyzer::Analyzer()
{
}

// Destructor declaration
Analyzer::~Analyzer()
{
}

long int Analyzer::factorial(int N)
{
  if(N<1) return 1;
  long int result = 1;
  for(int i = 1; i <=N; i++)
  {
    result*=i;
  }
  return result;


}
double Analyzer::binomial(int r, double p, int N)
{
   return (factorial(N)/(factorial(N-r)*factorial(r)))*pow(p,r)*pow(1-p,N-r);
}

double Analyzer::ClopperPearsonUp(int r, int N, double C)
{ 
  double p;
  double binomialSum;
  for(int i = 0; i <= 1000; i++)
  {
  p=0.001*i;
  binomialSum = 0;
  for(int i=r+1; i<=N; i++)
    {
      binomialSum+=binomial(i,p,N);
    }
  if(r==N) return 1;
  if(binomialSum>= (1-(1-C)/2)) return p;
  }
}

double Analyzer::ClopperPearsonDown(int r, int N, double C)
{
  double p;
  double binomialSum;
  for(int i = 0; i <= 1000; i++)
  {
  p=1-0.001*i;
  binomialSum = 0;
  for(int i=0; i<=(r-1); i++)
    {
      binomialSum+=binomial(i,p,N);
    }
  if(r==0) return 0;
  if(binomialSum>= (1-(1-C)/2)) return p;
  }
}

void Analyzer::DisplayClopperPearsonInterval()
{
   for (int i=0; i<=10;i++)
      {
         cout<< i <<" uspjeha od 10 ["<<ClopperPearsonDown(i,10,0.6827)<<","<<ClopperPearsonUp(i,10,0.6827)<<"]"<<endl;
      }
}

void Analyzer::DrawClopperPearsonInterval(int N, double C)
{
   TCanvas *c = new TCanvas("c","c");
   THStack *CPInterval = new THStack("CPInterval","CPInterval");
   c->cd();

  TH1F *histo_lowerValue = new TH1F("lower_value", "lower_value", N+1, 0, N+1);
  TH1F *histo_upperValue = new TH1F("upper_value", "upper_value", N+1, 0, N+1);

  CPInterval->SetTitle("Clopper-Pearson");
  //gPad->SetLeftMargin(0.15);



  histo_upperValue->SetLineColor(kBlue);
  histo_upperValue->SetFillColor(kBlue);
  histo_lowerValue->SetLineColor(kBlue);

  for(int i = 0; i <= N ; i++)
  {
    histo_lowerValue->SetBinContent(i+1,Analyzer::ClopperPearsonDown(i,N,C));
    histo_upperValue->SetBinContent(i+1,Analyzer::ClopperPearsonUp(i,N,C));

  }

  CPInterval->Add(histo_lowerValue);
  histo_upperValue->Add(histo_lowerValue,-1);
  CPInterval->Add(histo_upperValue);

  CPInterval->Draw("HIST");
  histo_upperValue -> GetXaxis()->SetTitle("N");
  histo_upperValue -> GetYaxis()->SetTitle("p");
  c->SaveAs("ClopperPearson.pdf");
}

int Analyzer::throwDice()
{
  int i;

  i = (rand()%6)+1;

  return i;

}

