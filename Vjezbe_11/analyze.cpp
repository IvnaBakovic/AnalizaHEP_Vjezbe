#include <iostream>
#include <Analyzer.h>

using namespace std;

    int main() {
    srand((unsigned)time(0));
    Analyzer *analyzer = new Analyzer();

    analyzer->DisplayClopperPearsonInterval();
    analyzer->DrawClopperPearsonInterval(10, 0.68);

    cout<<"Donja granica Clopper-Pearson za p = 1/4 " <<analyzer->ClopperPearsonDown(1,4,0.68) << endl;
    cout<<"Gornja granica Clopper-Pearson za p = 1/4 " << analyzer->ClopperPearsonUp(1,4,0.68) << endl; 

    double CL = 0.6827;
    double p_minus[10];
    double p_plus[10];
    int numberSix = 0;
    int covered = 0;


  for(int i = 0; i < 10 ; i++)
  {
    p_minus[i]=analyzer->ClopperPearsonDown(i,10,CL);
    p_plus[i] =analyzer->ClopperPearsonUp(i,10,CL);
  }


  for(int i = 0; i < 1000; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (analyzer->throwDice() == 6) numberSix++;
    }

    if( p_minus[numberSix] <= 1./6. && p_plus[numberSix] >= 1./6.) covered++;

    numberSix = 0;
  }

  cout << "True value vas covered by The ClopperPearson interval " << covered/10. << "\% of times." << endl;

    return 0;
}
