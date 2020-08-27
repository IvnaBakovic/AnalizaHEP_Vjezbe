#include <Analyzer.h>
#include <TMath.h>
#include <TLine.h>


Analyzer::Analyzer()
{
}

// Destructor declaration
Analyzer::~Analyzer()
{
}

void Analyzer::ChiSquareFit()
{
   TCanvas *c = new TCanvas("c","c");
   c->Divide(2);
   TF1 *fitFunction = new TF1("fit","x/[0]",1.,5.5);
   fitFunction->SetParName(0,"mass");
   fitFunction->SetParameter(0,0.1);
 
   c->cd(1);
   double a[5]={9.8,21.2,34.5,39.9,48.5};
   double F[5]={1.,2.,3.,4.,5.};

   double sigma_a[5]={1.,1.9,3.1,3.9,5.1};
   double sigma_F[5]={0.,0.,0.,0.,0.};
   TGraphErrors *gr = new TGraphErrors(5,F,a,sigma_F,sigma_a);
   gr->SetTitle("TGraphErrors;F [N];a [m/s^{2}]");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Fit(fitFunction);
   gr->Draw("AP");


   double xy = (a[0]*F[0] + a[1]*F[1] + a[2]*F[2]+ a[3]*F[3] + a[4]*F[4])/5;
   double x2 = (F[0]*F[0] + F[1]*F[1] + F[2]*F[2]+ F[3]*F[3] + F[4]*F[4])/5;
   double y2 = (a[0]*a[0] + a[1]*a[1] + a[2]*a[2]+ a[3]*a[3] + a[4]*a[4])/5;
   double theta = xy/x2;
   double mass = 1 / theta;
   cout << mass <<endl;  
   
   c->cd(2);
   TF1 *chi_square = new TF1("chiSquare","TMath::Power(([0]-[1]*x),2)/TMath::Power([2],2)+TMath::Power(([3]-[4]*x),2)/TMath::Power([5],2)+TMath::Power(([6]-[7]*x),2)/TMath::Power([8],2)+TMath::Power(([9]-[10]*x),2)/TMath::Power([11],2)+TMath::Power(([12]-[13]*x),2)/TMath::Power([14],2)",9,11);


	chi_square->SetParameter(0,a[0]);
	chi_square->SetParameter(1,F[0]);
	chi_square->SetParameter(2,sigma_a[0]);
	chi_square->SetParameter(3,a[1]);
	chi_square->SetParameter(4,F[1]);
	chi_square->SetParameter(5,sigma_a[1]);
	chi_square->SetParameter(6,a[2]);
	chi_square->SetParameter(7,F[2]);
	chi_square->SetParameter(8,sigma_a[2]);
	chi_square->SetParameter(9,a[3]);
	chi_square->SetParameter(10,F[3]);
	chi_square->SetParameter(11,sigma_a[3]);
	chi_square->SetParameter(12,a[4]);
	chi_square->SetParameter(13,F[4]);
	chi_square->SetParameter(14,sigma_a[4]);

  chi_square -> SetTitle("Chi-Square;m^{-1} [kg^{-1}];#chi^{2}");

  chi_square -> Draw();


   double min = chi_square->GetMinimumX();
   double min_mass = 1/min;

   double sigma_m = min - chi_square->GetX(chi_square->GetMinimum() + 1.0,min - 5., min-0.01);
   double sigma_p = chi_square->GetX(chi_square->GetMinimum() + 1.0,min+0.01, min + 5.) - min;

  cout << "Parametar dobiven preko parametra Chi-Square metode: masa = " << min_mass << endl;
  cout << "Standardna devijacija preko Chi-Square metode: sigma_+ = " << sigma_p/TMath::Power(min_mass,2) << " sigma_- = " << sigma_m/TMath::Power(min_mass,2) << endl;

      cout << min_mass <<endl;  

  //analitički, dobijemo deriviranjem i izjednačimo s nulom
  float n1 = 2*a[0]*F[0]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n2 = 2*a[1]*F[1]*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n3 = 2*a[2]*F[2]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n4 = 2*a[3]*F[3]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[4],2);
  float n5 = 2*a[4]*F[4]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[0],2);

  float d1 = 2*F[0]*F[0]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d2 = 2*F[1]*F[1]*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d3 = 2*F[2]*F[2]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d4 = 2*F[3]*F[3]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[4],2);
  float d5 = 2*F[4]*F[4]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[0],2);

  float oneOverMass_hat = (n1+n2+n3+n4+n5)/(d1+d2+d3+d4+d5);

  float sigma_oneOverMass = (sigma_a[0]*sigma_a[1]*sigma_a[2]*sigma_a[3]*sigma_a[4])/(TMath::Sqrt((d1/2)+(d2/2)+(d3/2)+(d4/2)+(d5/2)));


  cout << "Analitički izračunat parametar preko Chi-Square metode: masa = " << 1/oneOverMass_hat << endl;
  cout << "Analitički izračunata standardna devijacija preko Chi-Square metode: sigma = " << sigma_oneOverMass/TMath::Power(oneOverMass_hat,2) << endl;


  chi_square->SetMinimum(1.0);

  TLine *line_h = new TLine(oneOverMass_hat-sigma_m,chi_square->GetMinimum() + 1.0,oneOverMass_hat+sigma_p,chi_square->GetMinimum() + 1.0);
  line_h->SetLineColor(kBlack);
  line_h->SetLineStyle(kDashed);
  line_h->Draw();

  TLine *line_v1 = new TLine(oneOverMass_hat-sigma_m,1.0,oneOverMass_hat-sigma_m,chi_square->GetMinimum() + 1.0);
  line_v1->SetLineColor(kBlack);
  line_v1->SetLineStyle(kDashed);
  line_v1->Draw();

  TLine *line_v2 = new TLine(oneOverMass_hat,1.0,oneOverMass_hat,chi_square->GetMinimum());
  line_v2->SetLineColor(kBlack);
  line_v2->SetLineStyle(kDashed);
  line_v2->Draw();

  TLine *line_v3 = new TLine(oneOverMass_hat+sigma_p,1.0,oneOverMass_hat+sigma_p,chi_square->GetMinimum() + 1.0);
  line_v3->SetLineColor(kBlack);
  line_v3->SetLineStyle(kDashed);
  line_v3->Draw();

  c->SaveAs("ChiSquare.pdf");

   
}
