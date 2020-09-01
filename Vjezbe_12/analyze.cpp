#include <iostream>
#include <Analyzer.h>

using namespace std;

int main() {
    Analyzer *analyzer = new Analyzer();
    analyzer->Loop();
    analyzer->MVATraining("BDTG");
    return 0;
}
