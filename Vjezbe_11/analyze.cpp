#include <iostream>
#include <Analyzer.h>

using namespace std;

int main() {
    Analyzer *analyzer = new Analyzer();

    analyzer->DisplayClopperPearsonInterval();
    analyzer->DrawClopperPearsonInterval(10, 0.68);

    cout<<"Donja granica Clopper-Pearson za p = 1/4 " <<analyzer->ClopperPearsonDown(1,4,0.68) << endl;
    cout<<"Gornja granica Clopper-Pearson za p = 1/4 " << analyzer->ClopperPearsonUp(1,4,0.68) << endl; 

    return 0;
}
