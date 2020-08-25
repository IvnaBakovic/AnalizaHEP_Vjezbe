// C++
#include <iostream>
#include <fstream>

// My own class
#include <Analyzer.h>

using namespace std;

int main()
{
Analyzer *analyzer = new Analyzer();

analyzer->ReadFile();
analyzer->ConvertTxtToRootFile();
return 0;
}
