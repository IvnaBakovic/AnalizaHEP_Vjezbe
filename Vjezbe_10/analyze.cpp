#include <iostream>
#include <Analyzer.h>

using namespace std;

int main() {
    Analyzer *analyzer = new Analyzer();
    analyzer->ChiSquareFit();
    return 0;
}
